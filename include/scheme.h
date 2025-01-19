#ifndef SCHEME_H
#define SCHEME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>

#include "object.h"
#include "util.h"
#include "eval.h"
#include "parse.h"
#include "printer.h"
#include "env.h"
#include "io.h"
#include "config.h"

/* C library */
#include "cterm.h"


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

#endif