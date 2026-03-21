#include "scheme.h"

#define VERSION "MyScheme 1.0.0"

#define DEBUG(...)                   \
       do  {                         \
           if (debug==1) {           \
            fprintf(stderr, __VA_ARGS__);     \
           }                         \
       } while(0)

int debug=0;

int globl_argc;
int globl_argc_offset;
char **globl_argv;

#define can_load     (argc > 1 && debug == 0)
#define not_end(i, l) ((l - 1) > i)
#define flagzone for (int i = 0; i < argc; i++)
#define flag(x, y)   if (!strcmp(argv[i], x) || !strcmp(argv[i], y))

#define add_function(s_name,f_name)   \
        def_var_val(make_symbol(s_name), make_builtin_procedure(f_name), global_environment);

void init() {

    init_symbol();

    global_environment=setup_env();

    add_function("+",add_procedure);
    add_function("-",sub_procedure);
    add_function("*",mul_procedure);
    add_function("/",div_procedure);
    add_function("mod",mod_procedure);
    add_function("=",num_equal_procedure);
    add_function(">",greater_than_procedure);
    add_function("<",less_than_procedure);

    add_function("and",and_procedure);
    add_function("or",or_procedure);

    add_function("null?",null_procedure);
    add_function("boolean?",boolean_procedure);
    add_function("symbol?",symbol_procedure);
    add_function("integer?",integer_procedure);
    add_function("char?",char_procedure);
    add_function("string?",string_procedure);
    add_function("pair?",pair_procedure);
    add_function("procedure?",procedure_procedure);
    add_function("eq?",eq_procedure);

    add_function("typeof"        ,typeof_procedure);
    add_function("char->integer" ,char_to_integer_procedure);
    add_function("integer->char" ,integer_to_char_procedure);
    add_function("number->string",number_to_string_procedure);
    add_function("string->number",string_to_number_procedure);
    add_function("symbol->string",symbol_to_string_procedure);
    add_function("string->symbol",string_to_symbol_procedure);

    add_function("cons",cons_procedure);
    add_function("car",car_procedure);
    add_function("cdr",cdr_procedure);
    add_function("set-car!",set_car_procedure);
    add_function("set-cdr!",set_cdr_procedure);
    add_function("list",list_procedure);

    add_function("load"             , load_procedure);
    add_function("open-input-port"  , open_input_port_procedure);
    add_function("close-input-port" , close_input_port_procedure);
    add_function("input-port?"      , is_input_port_procedure);
 // add_function("read"             , read_procedure);
 // add_function("peek-char"        , peek_char_procedure);
 // add_function("eof-object?"      , is_eof_object_procedure);
    add_function("open-output-port" , open_output_port_procedure);
    add_function("close-output-port", close_output_port_procedure);
    add_function("output-port?"     , is_output_port_procedure);
    add_function("write"            , write_procedure);
    add_function("string-append"    , string_append_procedure);

    add_function("get-arg"          , get_arg_procedure);
    add_function("__builtin_argc"   , get_argc_procedure);
    add_function("exit"             , exit_procedure);
    add_function("system"           , system_procedure)
}

void loadstd() {
    FILE *in=NULL;
    object* exp;

    in=fopen("/usr/local/share/scheme/myscheme-stdlib.scm","r");
    if (in==NULL) {
        fprintf(stdout, "Exception in load: Cannot load the stdlib (/usr/local/share/scheme/myscheme-stdlib.scm).\n");
        exit(-1);
    }


    static int i = 1;
    while( (exp=read(in))!=NULL ) {
        eval(exp,global_environment);
    }
    fclose(in);
}

void loadsrc(char *source) {
    FILE *in=NULL;
    object* exp;

    in=fopen(source,"r");
    if (in==NULL) {
        fprintf(stdout, "Exception in load: Cannot load '%s'.\n", source);
        exit(-1);
    }

    while( (exp=read(in))!=NULL ) {
        eval(exp,global_environment);
    }
    fclose(in);
}

void sighandler(int signum)
{
    printf("\n> ");
}

int main(int argc, char** argv) {
    int have_stdlib = 1;

    globl_argc = argc;
    globl_argv = argv;

    globl_argc_offset = 1;
    flagzone {
        flag("-d", "--debug") {
            globl_argc_offset++;
            printf("Debug mode!\n");
            
            debug = 1;
            DEBUG("ARGC: %d\nARGC_OFFSET: %d\n", globl_argc, globl_argc_offset);
            if not_end(i, argc) {
                loadsrc(argv[i + 1]);
                return 1;
            }
            break;
        }
        flag("-v", "--version") {
            printf("Version: %s\n", VERSION);
            return 2;
        }
        flag("-n", "--nostdlib") {
            globl_argc_offset++;
            have_stdlib = 0;
            if not_end(i, argc) {
                loadsrc(argv[i + 1]);
                return 1;
            }
            break;
        }
    }

    init();

    if (have_stdlib)
        loadstd();

    if can_load {
        loadsrc(argv[1]);
        return 1;
    }

    printf("\n"
        "********************************\n\n\n"
        "             MyScheme              \n\n\n"
        "          ctrl-d to exit.          \n\n\n"
        "********************************\n");

    while (true) {
        printf("\nrepl> ");
        printer(eval(read(stdin), global_environment));
    }

    return 0;
}
