#ifndef EVAL_HPP
#define EVAL_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>

#include "object.hpp"
#include "builtin.hpp"
#include "env.hpp"

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

object* eval(object* exp, object* env);



#endif
