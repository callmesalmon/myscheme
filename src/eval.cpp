#include <eval.h>

#define DEBUG(...)                   \
       do  {                         \
           if (debug==1) {           \
            fprintf(stderr, __VA_ARGS__);     \
           }                         \
       } while(0)

extern int debug;

object *content_of_quote(object *exp) {
    return cadr(exp);
}

object* assignment_var(object* exp) {
    return cadr(exp);
}

object* assignment_val(object* exp) {
    return caddr(exp);
}

object* def_var(object* exp) {
    if ( is_symbol(cadr(exp))) {
        return cadr(exp);
    }
    else {
        return caadr(exp);
    }
}

object* def_val(object* exp) {
    if ( is_symbol(cadr(exp)) ) {
        return caddr(exp);
    }
    else {
        DEBUG("def_val_2: type: %d",(cdddr(exp))->type);
        return make_lambda(cdadr(exp),cddr(exp));
    }
}

object* if_predicate(object* exp) {
    return cadr(exp);
}

object* if_true(object* exp) {
    if (is_empty_list(caddr(exp))) {
        return True;
    }
    else {
        return caddr(exp);
    }
}

object* if_false(object* exp) {
    DEBUG("if_false: exp type: %d\n",exp->type);
    if (is_empty_list(cdddr(exp))) {
        DEBUG("if_false: alternative is empty\n");
        return False;
    }
    else {
        return cadddr(exp);
    }
}

object* function(object* exp) {
    return car(exp);
}

object* operands(object* exp) {
    return cdr(exp);
}

object* first_operand(object* exp) {
    return car(exp);
}

object* rest_operands(object* exp) {
    return cdr(exp);
}

object* eval_operand_list(object* exp, object* env) {
    if ( exp==empty_list ) {
        return empty_list;
    }
    else {
        return cons(eval(first_operand(exp), env),
                    eval_operand_list(rest_operands(exp),env));
    }
}

object* lambda_parameters(object* exp) {
    return cadr(exp);
}

object* lambda_body(object* exp) {
    return cddr(exp);
}

object* first_exp(object* exp) {
    return car(exp);
}

object* rest_exp(object* exp) {
    return cdr(exp);
}

object* begin_body(object* exp) {
    return cdr(exp);
}

object* cond_body(object* exp) {
    return cdr(exp);
}

object* cond_predicate(object* exp) {
    return car(exp);
}

object* make_if(object* predicate, object* consequence, object* alternative) {
    return cons(if_symbol, cons(predicate, cons(consequence, cons(alternative, empty_list))));
}

object* make_begin(object* exp) {
    return cons(begin_symbol,exp);
}

object* cond_consequence(object* exp) {
    object* first;
    object* rest;

    first=cadr(exp);
    rest=cddr(exp);
    if ( is_empty_list(rest) ) {
        return first;
    }
    else {
        return make_begin(cdr(exp));
    }
}

object* convert_to_if(object* exp) {
    object* first;
    object* rest;

    if ( is_empty_list(exp) ) {
        return False;
    }
    else { 
        first=first_exp(exp);
        rest=rest_exp(exp);
    
        if ( is_cond_else(first) ) {
            DEBUG("cond else\n");
            if ( is_empty_list(rest) ) {
                return  cond_consequence(first);
            }
            else {
                return make_warn("cond: else is not the last expression");
            }
        }
        else {
            return make_if(cond_predicate(first), cond_consequence(first), convert_to_if(rest));
        }
    }
}

object* let_bindings_parameters(object* exp) {
    return is_empty_list(exp)? empty_list : cons( caar(exp) , let_bindings_parameters(cdr(exp)) );
}

object* let_bindings_arguments(object* exp) {
    return is_empty_list(exp)? empty_list : cons( cadar(exp) , let_bindings_arguments(cdr(exp)) );
}

object* let_parameters(object* exp) {
    return let_bindings_parameters(cadr(exp));
}

object* let_arguments(object* exp) {
    return let_bindings_arguments(cadr(exp));
}

object* let_body(object* exp) {
    return cddr(exp);
}
object* make_function(object* function, object* operand) {
    return cons( function, operand );
}

object* apply_operator(object* exp) {
    if ( is_empty_list(cdr(exp)) ) {
        return make_warn("Exception: invalid syntax (apply)");
    }
    else {
        return cadr(exp);
    }
}

object* apply_operand(object* exp) {
    return cddr(exp);
}

object* eval_and(object* exp, object* env) {
    if ( is_empty_list(exp) ) {
        return True;
    }

    if ( eval(car(exp),env)==False  ) {
        return False;
    }
    else {
        return eval_and(cdr(exp),env);
    }
}

object* eval_or(object* exp, object* env) {
    if ( is_empty_list(exp) ) {
        return False;
    }

    if ( eval(car(exp),env)==True ) {
        return True;
    }
    else {
        return eval_or(cdr(exp),env);
    }
}

object* eval_and_or(object* exp, object* env) {
    if ( car(exp)==and_symbol ) {
        return eval_and(cdr(exp),env);
    }
    else {
        return eval_or(cdr(exp),env);
    }
}

object* eval_assignment(object* exp, object* env) {
    if ( set_var_val(assignment_var(exp), eval(assignment_val(exp),env),env) ) {
        return ok_symbol;
    }
    else {
        return make_warn("Unbounded variable");
    }
}

object* eval_def(object* exp , object* env) {
    if ( is_empty_list(cdr(exp)) || is_empty_list(cddr(exp)) ) {
        return make_warn("Exception: invalid syntax (define)");
    }

    def_var_val(def_var(exp), eval(def_val(exp),env),env);
    return ok_symbol;
}

object* eval(object* exp, object* env) {
    object *proc=NULL;
    object *args=NULL;

    DEBUG("start to evaluate!\n");

    while (1) {

        if ( is_self_value(exp) ) {
            DEBUG("eval: self_value: %d\n", exp->type);
            return exp;
        }
        else if ( is_variable(exp) ) {
            DEBUG("eval: variable\n");
            return loop_up_env(exp,env);
        }
        else if ( is_quote(exp) ) {
            DEBUG("eval: quote\n");
            return content_of_quote(exp);
        }
        else if ( is_assignment(exp) ) {
            DEBUG("eval: assignment\n");
            return eval_assignment(exp,env);
        }
        else if ( is_def(exp) ) {
            DEBUG("eval: def\n");
            return eval_def(exp,env);
        }
        else if ( is_if(exp) ) {
            DEBUG("eval: if\n");
            exp= is_true(eval(if_predicate(exp),env)) ? if_true(exp):if_false(exp);
        }
        else if ( is_begin(exp) ) {
            DEBUG("eval: begin\n");
            exp = begin_body(exp);
            while( !is_last_exp(exp) ) {
                DEBUG("eval begin: is NOT last expression\n");
                eval(first_exp(exp),env);
                exp=rest_exp(exp);
            }
            exp=first_exp(exp);
        }
        else if( is_cond(exp) ) {
            DEBUG("eval: cond\n");
            if ( is_empty_list(cond_body(exp)) ) {
                return make_warn("Exception: invalid syntax (cond)");
            }
            exp= convert_to_if(cond_body(exp));
        }
        else if( is_let(exp) ) {
            DEBUG("eval: let\n");
            exp = make_function( make_lambda(let_parameters(exp),let_body(exp)),let_arguments(exp));
        }
        else if ( is_lambda(exp) ) {
            DEBUG("eval: lambda\n");
            return make_compound_func(lambda_parameters(exp),lambda_body(exp),env);
        }
        else if ( is_and_or(exp) ) {
            DEBUG("eval: and / or\n");
            return eval_and_or((exp),env);
        }
        else if ( is_apply(exp) ) {
            DEBUG("eval: apply\n");
            proc=apply_operator(exp);
            args=apply_operand(exp);
            exp= cons(proc,args);
        }
        else if ( is_function(exp) ) {
            DEBUG("eval: function\n");
            proc= eval(function(exp), env);
            args= eval_operand_list(operands(exp), env);
            if ( is_builtin_procedure(proc) ) {
                DEBUG("eval: builtin function\n");
                return (proc->data.builtin_proc.func)(args);
            }
            else if ( is_compound_func(proc) ) {
                DEBUG("eval: compound function\n");
                env = extend_env(proc->data.compound_proc.parameters, args, proc->data.compound_proc.env);
                exp=proc->data.compound_proc.body;

                DEBUG("eval: compound function: type: %d\n",car(exp)->type);
                while( !is_last_exp(exp) ) {
                    DEBUG("eval compound function: is NOT last expression , type: %d\n",cdr(exp)->type);
                    eval(first_exp(exp),env);
                    exp=rest_exp(exp);
                }
                exp=first_exp(exp);
            }
            else {
                fprintf(stderr, "[ERROR] Cannot eval unknown expression.\n");
                exit(1);
            }
        }
        else if ( is_warn(exp) ) {
            return exp;
        }
        else {
            fprintf(stderr, "[ERROR] Cannot eval unknown expression.\n");
            exit(1);
        }

        if (is_last_exp(exp)) {
            DEBUG("eval: exp IS last expression!\n");
            break;
        }

        if (proc->type==WARN) {
            DEBUG("return: proc\n");
            return proc;
        }

        if (args->type==WARN) {
            DEBUG("return: args\n");
            return args;
        }
    }

    return ok_symbol;
}