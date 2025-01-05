#ifndef BUILTIN_HPP
#define BUILTIN_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>

#include "object.hpp"
#include "printer.hpp"

extern object* empty_list;
extern object* False;
extern object* True;
extern object* symbol_table;
extern object* quote_symbol;
extern object* define_symbol;
extern object* set_symbol;
extern object* ok_symbol;
extern object* if_symbol;
extern object* lambda_symbol;
extern object* begin_symbol;
extern object* cond_symbol;
extern object* else_symbol;
extern object* let_symbol;
extern object* and_symbol;
extern object* or_symbol;
extern object* apply_symbol;

extern object* empty_environment;
extern object* global_environment;

object* make_builtin_procedure( object *(*func)(object* arguments) );
object* add_procedure(object* args);
object* sub_procedure(object* args);
object* mul_procedure(object* args);
object* div_procedure(object* args);
object* mod_procedure(object* args);
object* num_equal_procedure(object* args);
object* less_than_procedure(object* args);
object* greater_than_procedure(object* args);
object* and_procedure(object* args);
object* or_procedure(object* args);
object* null_procedure(object* args);
object* boolean_procedure(object* args);
object* symbol_procedure(object* args);
object* integer_procedure(object* args);
object* char_procedure(object* args);
object* string_procedure(object* args);
object* pair_procedure(object *args);
object* procedure_procedure(object* args);
object* char_to_integer_procedure(object* args);
object* integer_to_char_procedure(object* args);
object* number_to_string_procedure(object* args);
object* string_to_number_procedure(object* args);
object* symbol_to_string_procedure(object* args);
object* string_to_symbol_procedure(object* args);
object* cons_procedure(object* args);
object* car_procedure(object* args);
object* cdr_procedure(object* args);
object* set_car_procedure(object* args);
object* set_cdr_procedure(object* args);
object* list_procedure(object* args);
object* eq_procedure(object* args);
object* write_procedure(object* args);
object* typeof_procedure(object* args);

#endif