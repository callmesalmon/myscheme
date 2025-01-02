#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>

#include "object.hpp"

extern object* empty_list;
extern object* global_environment;
extern object* empty_environment;

int is_empty_env(object* env);

object* enclosing_env(object* env);

object* first_frame(object* env);

object* frame_var(object* frame);

object* frame_val(object* frame);

void add_to_frame(object* var,object* val, object* frame);

object* make_frame(object* var,object* val);

int set_var_val(object* var, object* val, object* env);

void def_var_val(object* var, object* val, object* env);

object* setup_env();

object* loop_up_env(object* var, object* env);

object* extend_env(object* var,object* val, object* old_env);





#endif
