#include <object.hpp>

#define DEBUG(...)                   \
       do  {                         \
           if (debug==1) {           \
            fprintf(stderr, __VA_ARGS__);     \
           }                         \
       } while(0)

extern int debug;

object* empty_list;
object* False;
object* True;
object* symbol_table;
object* quote_symbol;
object* define_symbol;
object* set_symbol;
object* ok_symbol;
object* if_symbol;
object* lambda_symbol;
object* begin_symbol;
object* cond_symbol;
object* else_symbol;
object* let_symbol;
object* and_symbol;
object* or_symbol;
object* apply_symbol;

object* empty_environment;
object* global_environment;



object *car(object *pair) {
    return pair->data.pair.car;
}
object *cdr(object *pair) {
    return pair->data.pair.cdr;
}

void set_car(object *obj, object* value) {
    obj->data.pair.car = value;
}

void set_cdr(object *obj, object* value) {
    obj->data.pair.cdr = value;
}

object* new_object() {
    object* temp;
    
    temp=(object *)malloc(sizeof(object));
    if (temp==NULL) {
        fprintf(stderr,"Run out of memory!\nEXIT!\n");
        exit(1);
    }
    
    return temp;
}

object* cons(object* car, object* cdr) {
    object *temp;
    
    temp=new_object();
    temp->type=PAIR;
    temp->data.pair.car=car;
    temp->data.pair.cdr=cdr;
    
    return temp;
}

// chacacter object
object* make_character(char c) {
    object *temp;
    
    temp=new_object();
    temp->type=CHARACTER;
    temp->data.character.value=c;
    
    return temp;
}

// integer object
object* make_integer(long value) {
    object* temp;
    
    temp=new_object();
    temp->type=INTEGER;
    temp->data.integer.value=value;
    
    return temp;
}

// real object
object* make_real(long f_part,long s_part) {
    object *temp;
    
    temp=new_object();
    temp->type=REAL;
    temp->data.real.f_part=f_part;
    temp->data.real.s_part=s_part;
    
    return temp;
}

// object* make_real(double num) {
//     object* temp;
//     int a=0;

//     temp=new_object();
//     temp->type=REAL;

//     while()

// }

double RealtoNum(object* obj) {
    int f=obj->data.real.f_part;
    int s=obj->data.real.s_part;
    double res=0;

    if (s==0) {
        return (double)f;
    }

    int a=10;
    while( s%a!=0 ) {
        a*=10;
    }

    res=s/a;
    res+=f;
    return res;
}

// string
object* make_string(const char* buffer)  {
    object *temp;
    
    temp=new_object();
    temp->type=STRING;
    temp->data.string.value=(char *)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(temp->data.string.value,buffer);
    

    DEBUG("buffer:%s!\n",buffer);
    DEBUG("object:%s!\n",temp->data.string.value);

    return temp;
}

object* make_symbol(const char* buffer) {
    object *temp;
    
    object *temp_table=symbol_table;
    
    // printf("start to make symbol , first to look up in the symbol table!\n");
    while(  !is_empty_list(temp_table) ) {
        if (   !strcmp(buffer,car(temp_table)->data.symbol.value)    ) {
            return car(temp_table);
        }
        temp_table=cdr(temp_table);
    }
    // printf("second to make new symbol!\n");
    temp=new_object();
    temp->type=SYMBOL;
    temp->data.symbol.value=(char *)malloc(sizeof(char)*(strlen(buffer)+1));
    if (temp->data.symbol.value == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(temp->data.symbol.value,buffer);
    // fprintf(stdout,"buffer:%s!\n",buffer);
    // fprintf(stdout,"object:%s!\n",temp->data.string.value);
    symbol_table = cons(temp, symbol_table);
    return temp;
}

object* make_warn(const char* buffer) {
    object *temp;
    
    temp=new_object();
    temp->type=WARN;
    temp->data.string.value=(char *)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(temp->data.string.value,buffer);

    return temp;
}

object* make_compound_func(object* parameters, object* body, object* env) {
    object* temp;

    temp=new_object();
    temp->type= COMPOUND_PROC;
    temp->data.compound_proc.parameters=parameters;
    temp->data.compound_proc.body=body;
    temp->data.compound_proc.env=env;

    return temp;
}

object* make_lambda(object *parameters, object *body) {
    return cons(lambda_symbol, cons(parameters, body));
}

int is_pair(object *obj) {
    return obj->type == PAIR;
}

int is_empty_list(object *obj) {
    return obj == empty_list;
}

int is_false(object *obj) {
    return obj == False;
}

int is_true(object *obj) {
    return !is_false(obj);
}

int is_boolean(object* obj) {
    return obj->type==BOOLEAN;
}

int is_character(object* obj) {
    return obj->type==CHARACTER;
}

int is_integer(object* obj) {
    return obj->type==INTEGER;
}

int is_real(object* obj) {
    return obj->type==REAL;
}

int is_number(object *exp) {
    return exp->type==INTEGER || exp->type==REAL;
}

int is_symbol(object* obj) {
    return obj->type==SYMBOL;
}

int is_warn(object* obj) {
    return obj->type=WARN;
}

int is_string(object* obj) {
    return obj->type==STRING;
}

int is_self_value(object * exp) {
    return  is_number(exp) || is_character(exp) || is_boolean(exp) || is_string(exp) ;
}

int is_quote(object * exp) {
    return is_symbol(car(exp)) && car(exp)==quote_symbol;
}

int is_variable(object* exp) {
    return is_symbol(exp);
}

// assignment expression: set!
int is_assignment(object* exp) {
    return is_pair(exp) && is_symbol(car(exp)) && car(exp)==set_symbol;
}

// define expression: define
int is_def(object* exp) {
    return is_pair(exp) && is_symbol(car(exp)) && car(exp)==define_symbol;
}

// if expression: if
int is_if(object* exp) {
    return is_pair(exp) && is_symbol(car(exp)) && car(exp)==if_symbol;
}

int is_function(object* exp) {
    return is_pair(exp);
}

int is_lambda(object* exp) {
    return is_pair(exp) && is_symbol(car(exp)) && car(exp)==lambda_symbol;
}

int is_last_exp(object* exp) {
    return is_empty_list(cdr(exp));
}

int is_begin(object* exp) {
    return is_pair(exp) && is_symbol(car(exp)) && car(exp)==begin_symbol;
}

int is_cond(object* exp) {
    return is_pair(exp) && is_symbol(car(exp)) && car(exp)==cond_symbol;
}

int is_cond_else(object* exp) {
    return is_symbol(car(exp)) && car(exp)==else_symbol;
}

int is_let(object* exp) {
    return is_pair(exp) && is_symbol(car(exp)) && car(exp)==let_symbol; 
}

int is_apply(object* exp) {
    return is_pair(exp) && is_symbol(car(exp)) && car(exp)==apply_symbol;
}

int is_and_or(object* exp) {
    return is_pair(exp) && is_symbol(car(exp)) && (car(exp)==and_symbol || car(exp)==or_symbol);
}

int is_builtin_procedure( object* obj) {
    return obj->type==BUITLIN_PROC;
}

int is_compound_func(object* obj) {
    return obj->type==COMPOUND_PROC;
}

int is_input_port(object* obj) {
    return obj->type==INPUT_PORT;
}

int is_output_port(object* obj) {
    return obj->type==OUTPUT_PORT;
}

void init_symbol() {
    empty_list=new_object();
    empty_list->type=EMPTY_LIST;

    False=new_object();
    False->type=BOOLEAN;
    False->data.boolean.value='f';
    
    True=new_object();
    True->type=BOOLEAN;
    True->data.boolean.value='t';

    symbol_table=empty_list;
    quote_symbol=make_symbol("quote");
    define_symbol=make_symbol("define");
    set_symbol=make_symbol("set!");
    ok_symbol=make_symbol("\nok");
    if_symbol=make_symbol("if");
    lambda_symbol=make_symbol("lambda");
    begin_symbol=make_symbol("begin");
    cond_symbol=make_symbol("cond");
    else_symbol=make_symbol("else");
    let_symbol=make_symbol("let");
    and_symbol=make_symbol("and");
    or_symbol=make_symbol("or");
    apply_symbol=make_symbol("apply");


    empty_environment=empty_list;
}
