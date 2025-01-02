#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>


#define caar(obj)   car(car(obj))
#define cadr(obj)   car(cdr(obj))
#define cdar(obj)   cdr(car(obj))
#define cddr(obj)   cdr(cdr(obj))
#define caaar(obj)  car(car(car(obj)))
#define caadr(obj)  car(car(cdr(obj)))
#define cadar(obj)  car(cdr(car(obj)))
#define caddr(obj)  car(cdr(cdr(obj)))
#define cdaar(obj)  cdr(car(car(obj)))
#define cdadr(obj)  cdr(car(cdr(obj)))
#define cddar(obj)  cdr(cdr(car(obj)))
#define cdddr(obj)  cdr(cdr(cdr(obj)))
#define caaaar(obj) car(car(car(car(obj))))
#define caaadr(obj) car(car(car(cdr(obj))))
#define caadar(obj) car(car(cdr(car(obj))))
#define caaddr(obj) car(car(cdr(cdr(obj))))
#define cadaar(obj) car(cdr(car(car(obj))))
#define cadadr(obj) car(cdr(car(cdr(obj))))
#define caddar(obj) car(cdr(cdr(car(obj))))
#define cadddr(obj) car(cdr(cdr(cdr(obj))))
#define cdaaar(obj) cdr(car(car(car(obj))))
#define cdaadr(obj) cdr(car(car(cdr(obj))))
#define cdadar(obj) cdr(car(cdr(car(obj))))
#define cdaddr(obj) cdr(car(cdr(cdr(obj))))
#define cddaar(obj) cdr(cdr(car(car(obj))))
#define cddadr(obj) cdr(cdr(car(cdr(obj))))
#define cdddar(obj) cdr(cdr(cdr(car(obj))))
#define cddddr(obj) cdr(cdr(cdr(cdr(obj))))

typedef enum obj_type {
        INTEGER,
        REAL,
        BOOLEAN,
        CHARACTER,
        STRING,
        PAIR,
        SYMBOL,
        BUITLIN_PROC,
        COMPOUND_PROC,
        EMPTY_LIST,
        WARN,
        INPUT_PORT,
        OUTPUT_PORT,
} obj_type;

typedef struct object {
    obj_type type;
    union {
        struct {
            long value;
        }integer;
        struct {
            long f_part;
            long s_part;
        }real;
        struct {
            char value;
        } character;
        struct {
            char value;
        }boolean;
        struct {
            char *value;
        } string;
        struct {
            object * car;
            object * cdr;
        }pair;
        struct {
            char *value;
        }symbol;
        struct {
            object* (*func)(object *args);
        }builtin_proc;
        struct {
            object* parameters;
            object* body;
            object* env;
        }compound_proc;
        struct {
            char *value;
        }warn;
        struct {
            FILE *stream;
        } input_port;
        struct {
            FILE *stream;
        } output_port;
    }data;
} object;


void init_symbol();
object* new_object();
object *car(object *pair);
object *cdr(object *pair);
void set_car(object *obj, object* value);
void set_cdr(object *obj, object* value);
object* cons(object* car, object* cdr);

// character object
object* make_character(char c);

// integer object
object* make_integer(long value);

// real object
object* make_real(long f_part,long s_part);

// object* make_real(double num) {
//     object* temp;
//     int a=0;

//     temp=new_object();
//     temp->type=REAL;

//     while()

// }

double RealtoNum(object* obj);

// string
object* make_string(const char* buffer);
object* make_symbol(const char* buffer);
object* make_warn(const char* buffer);
object* make_lambda(object *parameters, object *body);
object* make_compound_func(object* parameters, object* body, object* env);

int is_pair(object *obj);
int is_empty_list(object *obj);
int is_false(object *obj);
int is_true(object *obj);
int is_boolean(object* obj);
int is_character(object* obj);
int is_integer(object* obj);
int is_real(object* obj);
int is_number(object *exp);
int is_string(object* obj);
int is_variable(object* exp);
int is_symbol(object* obj);
int is_warn(object* obj);
int is_quote(object* exp);
int is_self_value(object* exp);

// assignment expression: set!
int is_assignment(object* exp);

// define expression: define
int is_def(object* exp);

// if expression: if
int is_if(object* exp);
int is_function(object* exp);
int is_lambda(object* exp);
int is_last_exp(object* exp);
int is_begin(object* exp);
int is_cond(object* exp);
int is_cond_else(object* exp);
int is_let(object* exp);
int is_apply(object* exp);
int is_and_or(object* exp);
int is_builtin_procedure( object* obj);
int is_compound_func(object* obj);
int is_input_port(object* obj);
int is_output_port(object* obj);

#endif
