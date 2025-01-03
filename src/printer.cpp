#include <printer.hpp>

#define DEBUG(...)                   \
       do  {                         \
           if (debug==1) {           \
            fprintf(stderr, __VA_ARGS__);     \
           }                         \
       } while(0)

extern int debug;

void print_pair(object* obj) {
    printer(obj->data.pair.car);
    
    if (obj->data.pair.cdr->type==PAIR) {
        fprintf(stdout," ");
        print_pair(obj->data.pair.cdr);
    }
    else if (obj->data.pair.cdr->type==EMPTY_LIST){
        return ;
    }
    else {
        fprintf(stdout," . ");
        printer(obj->data.pair.cdr);
    }
}


void printer(object *obj) {
    char *str=NULL;
    DEBUG("object type: %d\n",obj->type);
    DEBUG("start to print!\n");

    switch(obj->type) {
        case INTEGER:
            fprintf(stdout,"%ld",obj->data.integer.value);
            break;
        case REAL:
            fprintf(stdout,"%ld",obj->data.real.f_part);
            fprintf(stdout,".");
            fprintf(stdout,"%ld",obj->data.real.s_part);
            break;
        case BOOLEAN:
            fprintf(stdout,"#%c",obj->data.boolean.value);
            break;
        case CHARACTER:
            if (  isalpha(obj->data.character.value)  ) {
                fprintf(stdout,"#\\%c",obj->data.character.value);
            }
            else if ( obj->data.character.value=='\n' ) {
                fprintf(stdout,"#\\newline");
            }
            else if (obj->data.character.value==' ' ) {
                fprintf(stdout,"#\\space");
            }
            break;
        case STRING:
            str=obj->data.string.value;
            fprintf(stdout,"\"");
            while( *str!='\0' ) {
                if (*str=='\n') {
                    fprintf(stdout,"\\n");
                }
                else if ( *str=='\\') {
                    fprintf(stdout,"\\");
                }
                else if (*str=='"'){
                    fprintf(stdout, "\\\"");
                }
                else {
                    fprintf(stdout,"%c",*str);
                }
                str++;
            }
            fprintf(stdout,"\"");
            break;
        case PAIR:
            fprintf(stdout,"(");
            print_pair(obj);
            fprintf(stdout,")");
            break;
        case SYMBOL:
            fprintf(stdout,"%s",obj->data.symbol.value);
            break;
        case BUITLIN_PROC:
        case COMPOUND_PROC:
            fprintf(stdout,"#<procedure>");
            break;
        case EMPTY_LIST:
            break;
        case WARN:
            fprintf(stdout,"**%s**",obj->data.warn.value);
            break;
        default:
            fprintf(stderr,"Unknown type!\nExit!\n");
            break;
    }
}
