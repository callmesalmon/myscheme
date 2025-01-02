#include <parse.hpp>

#define DEBUG(...)                   \
       do  {                         \
           if (debug==1) {           \
            fprintf(stderr, __VA_ARGS__);     \
           }                         \
       } while(0)

extern int debug;

char peek(FILE *in) {
    char c;
    c=getc(in);
    ungetc(c,in);
    return c;
}

void skip_space(FILE *in) {
    char c;
    

    while ( (c = getc(in))!= EOF) {
        
        if (isspace(c)) {
            continue;
        }
        else if (c == ';') { /* comments are whitespace also */
            while (((c = getc(in)) != EOF) && (c != '\n'));
            continue;
        }
        ungetc(c, in);
        break;
    }
}

int is_ex_al(char c) {
    if ( c=='!' || c=='$' || c=='%' || c=='&' || c=='*'
        || c=='+' || c=='-' || c=='.' || c=='/' ||
        c==':' || c=='<' || c=='=' || c=='>' ||
        c=='?' || c=='@' || c=='^' || c=='_' ||
        c=='~' ) {
        return 1;
    }
    return 0;
}

//int is_delimiter(int c) {
//    return isspace(c) || c == EOF ||
//    c == '('   || c == ')' ||
//    c == '"'   || c == ';';
//}

int get_expected_string(FILE *in, const char * expect) {
    char c;
    
    while( *expect!='\0' ) {
        c=getc(in);
        if ( c != *expect ) {
            // fprintf(stderr, "unexpected character!\nExit!\n");
            // exit(1);
            return 0;
        }
        expect++;
    }
    return 1;
}

int peek_expected_delimiter(FILE *in, const char *expect) {
    char c;
    c=peek(in);
    while ( c != '\0' ) {
        if (c==*expect) {
            return 1;
        }
        expect++;
    }
    // fprintf(stderr,"no expected dilimiter followed!\nExit!\n");
    return 0;
}

object* get_symbol(FILE *in) {
    char c;
    c=getc(in);
    char buffer[256];
    int offset=0;
    
    while( is_ex_al(c) || isalpha(c) || isdigit(c)  ) {
        if (offset<256-1) {
            buffer[offset++]=c;
        }
        else {
            // fprintf(stderr,"Symbol name is too long!\nExit!\n");
            // exit(1);
            return make_warn("Symbol name is too long!");
        }
        c=getc(in);
    }
    if ( isspace(c) || c==')' || c=='(' ) {
        buffer[offset]='\0';
        ungetc(c,in);
        return make_symbol(buffer);
    }
    else {
        // fprintf(stderr,"Symbol is not followed by a valid delimiter!\nExit!\n");
        // exit(1);
        return make_warn("Symbol is not followed by a valid delimiter!");
    }
}

object* get_pair(FILE *in) {
    char c;
    object *car;
    object *cdr;
    
    
    skip_space(in);

    if (peek(in)==')') {
        getc(in);
        return empty_list;
    }
    
    car=read(in);
    
    skip_space(in);
    
    c=getc(in);
    if ( c=='.' ) {
        // printf("start to get improper list!\n");
        peek_expected_delimiter(in," \n");
        cdr=read(in);
        skip_space(in);
        c=getc(in);
        if ( c!=')' ) {
            DEBUG("Parentheses don't match!\nExit!\n");
            return make_warn("Parentheses don't match!");
        }
        return cons(car,cdr);
    }
    else {
        ungetc(c,in);
        cdr=get_pair(in);
        return cons(car,cdr);
    }
}

object* get_number(FILE *in) {
    short int sign=1;
    short int d_sign=0;
    char buffer[21];
    int offset=0;
    char c;
    
    c=getc(in);
    
    if (c=='-' ) {
        sign=-1;
    }
    else {
        ungetc(c,in);
    }
    while ( isdigit((c=getc(in))) || c=='.' ) {
        if (c=='.') {
            d_sign++;
        }
        buffer[offset++]=c;
    }
    ungetc(c,in);
    if (d_sign>1) {
        DEBUG("Invalid float number!\nExit!\n");
        // exit(1);
        return make_warn("Invalid float number!");
    }
    else if (d_sign==0) {
        int loop=0;
        long num=0;
        while( loop<offset ) {
            num=num*10+(buffer[loop]-'0');
            loop++;
        }
        num*=sign;
        DEBUG("Get integer: %ld\n",num);
        return make_integer(num);
    }
    else if (d_sign==1) {
        int loop=0;
        long f_part=0;
        long s_part=0;
        while( loop<offset && buffer[loop]!='.' ) {
            f_part=f_part*10+(buffer[loop]-'0');
            loop++;
        }
        f_part*=sign;
        loop++;
        while ( loop<offset ) {
            s_part=s_part*10+(buffer[loop]-'0');
            loop++;
        }
        DEBUG("Get real: %ld.%ld\n",f_part,s_part);
        return make_real(f_part,s_part);
    }
    return new_object();
}

object* get_character(FILE *in) {
    char c;
    c=getc(in);   
    switch(c) {
        case 's':
            if ( peek(in)=='p' ) {
                if ( !get_expected_string(in,"pace") ) {
                    return make_warn("unexpected character!");
                }
                peek_expected_delimiter(in," \n");
                return make_character(' ');
            }
            break;
        case 'n':
            if ( peek(in)=='e' ) {
                if ( !get_expected_string(in,"ewline") ) {
                    return make_warn("unexpected character!");
                }
                peek_expected_delimiter(in," \n");
                return make_character('\n');
            }
            break;
        case '(':
                if ( !peek_expected_delimiter(in," \n") ) {
                    return make_warn("no expected dilimiter followed!");
                }
                return make_character('(');
                break;        
    }
    if ( !peek_expected_delimiter(in," \n") ) {
        return make_warn("no expected dilimiter followed!");
    }
    return make_character(c);
}


/*********************************
 *                               *
 *                               *
 *                               *
 *  PART:  Dealing with char     *
 *                               *
 *                               *
 *                               *
 *********************************/

void get_comment(FILE *in)  {
    char c;
    c=getc(in);
    while ( c!='\n' ) {
        c=getc(in);
    }
}

object* read(FILE *in) {
    char c;
    char temp;

    DEBUG("reading\n");
    
    skip_space(in);
    c=getc(in);

    while ( c==';' ) {
        get_comment(in);
        c=getc(in);
    }

    if ( c=='#'  ) { // get character
    
        c = getc(in);
        switch (c) {
            case 'T':
                
            case 't':
                return True;
            case 'F':
                
            case 'f':
                return False;
            case '\\':
                return get_character(in);
            default:
            return make_warn("unknown boolean literal");
        }
    }
    else if ( isdigit(c) ||  ( c=='-' && isdigit(peek(in)) )    ) { //try to get number: integer & double
        
        
        ungetc(c,in);
        return get_number(in);
    }
    else if ( c=='"' ) { // try to get string
        
        int i=0;
        char buffer[256];
        while( (c=getc(in))!='"' ) {
            if (c == '\\') {
                temp = peek(in);
                if (temp=='n') {
                    c='\n';
                    getc(in);
                }
                if (temp == '"') {
                    c = '"';
                    getc(in);
                }
            }
            if (c == EOF) {
                return make_warn("non-terminated string literal");
            }
            if (i < 256 - 1) {
                buffer[i++] = c;
            }
            else {
                return make_warn( "string too long");
            }
        }
        buffer[i]='\0';
        
        return make_string(buffer);
    }
    else if (c=='(') {  // try to get pair
        return get_pair(in);
    }
    else if ( is_ex_al(c) || isalpha(c) ) { //try to get symbol
        ungetc(c,in);
        return get_symbol(in);
    }
    else if (c=='\'') {
        return cons(quote_symbol,cons(read(in),empty_list));
    }
    else if (c!=EOF) {
        return make_warn("Read: invalid grammar!");
    }
    else {
        exit(1);
        // return make_warn("Read: invalid grammar!");
    }
    return new_object();


    
}
