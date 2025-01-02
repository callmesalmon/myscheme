#ifndef IO_HPP
#define IO_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>

#include "object.hpp"
#include "parse.hpp"
#include "eval.hpp"

extern object* empty_list;
extern object* False;
extern object* True;
extern object* ok_symbol;
extern object* global_environment;

object* make_input_port(FILE* in);
object* make_output_port(FILE* out);
object* load_procedure(object* args);
object* read_procedure(object* args);
object* open_input_port_procedure(object* args);
object* close_input_port_procedure(object* args);
object* open_output_port_procedure(object* args);
object* close_output_port_procedure(object* args);
object* is_input_port_procedure(object* args);
object* is_output_port_procedure(object* args);

#endif
