#include <builtin.hpp>

#define DEBUG(...)                   \
       do  {                         \
           if (debug==1) {           \
            fprintf(stderr, __VA_ARGS__);     \
           }                         \
       } while(0)

extern int debug;

object* make_builtin_procedure( object *(*func)(object* arguments) ) {
    object* obj;

    obj=new_object();
    obj->type = BUITLIN_PROC;
    obj->data.builtin_proc.func=func;

    return obj;
}

object* add_procedure(object* args) {
    long res=0;

    DEBUG("ADD_PROCEDURE!\n");

    while( !is_empty_list(args)) {
        if ( car(args)->type==INTEGER ) {
            res=res+(car(args))->data.integer.value;
        }
        else if ( car(args)->type==PAIR ) {
            // get_type(car(args)->type);
            res=res+add_procedure(car(args))->data.integer.value;
        }
        else {
            return make_warn("Exception in +: operand is not a number");
        }
        args = cdr(args);
    }
    return make_integer(res);
}

object* sub_procedure(object* args) {
    long res=0;

    if ( !is_empty_list(args) ) {
        if ( car(args)->type==INTEGER ) {
            res+=(car(args))->data.integer.value;
        }
        args=cdr(args);
    }

    while( !is_empty_list(args)) {
        if ( car(args)->type==INTEGER ) {
            res-=(car(args))->data.integer.value;
        }
        else {
            return make_warn("Exception in -: operand is not a number");
        }
        args = cdr(args);
    }

    return make_integer(res);
}

object* mul_procedure(object* args) {
    long res=1;
    int c=0;

    while( !is_empty_list(args)) {
        if ( car(args)->type==INTEGER ) {
            res=res*(car(args))->data.integer.value;
        }
        else if ( car(args)->type==PAIR ) {
            // get_type(car(args)->type);
            res=res+mul_procedure(car(args))->data.integer.value;
        }
        args = cdr(args);
        c++;
    }
    if(c<=1) {
        return False;
    }
    return make_integer(res);
}

object* div_procedure(object* args) {
    double res=0;

    if ( !is_empty_list(args) ) {
        if ( car(args)->type==INTEGER ) {
            res+=(car(args))->data.integer.value;
        }
        args=cdr(args);
    }

    while( !is_empty_list(args)) {
        if ( car(args)->type==INTEGER ) {
            res/=(car(args))->data.integer.value;
        }
        args = cdr(args);
    }
    return make_integer((int)res);
}

object* mod_procedure(object* args) {
    int res=0;
    if ( car(args)->type==INTEGER && 
        cadr(args)->type==INTEGER && 
        is_empty_list(cddr(args))) {
        res = car(args)->data.integer.value % cadr(args)->data.integer.value;
    }
    return make_integer(res);
}

object* num_equal_procedure(object* args) {
    long value=0;

    value=(car(args))->data.integer.value;
    while ( !is_empty_list(args=cdr(args))) {
        if (value!=car(args)->data.integer.value) {
            return False;
        }
    }
    return True;
}

object* less_than_procedure(object* args) {
    long first;
    long second;

    first=car(args)->data.integer.value;
    while( !is_empty_list(args=cdr(args))) {
        second=car(args)->data.integer.value;
        if (first<second) {
            first=second;
        }
        else {
            return False;
        }
    }
    return True;
}

object* greater_than_procedure(object* args) {
    long first;
    long second;

    first=car(args)->data.integer.value;
    while( !is_empty_list(args=cdr(args))) {
        second=car(args)->data.integer.value;
        if (first>second) {
            first=second;
        }
        else {
            return False;
        }
    }
    return True;
}

object* and_procedure(object* args) {
    if( is_empty_list(args) ) {
        return True;
    }

    if ( car(args)==False ) {
        return False;
    }
    else {
        return and_procedure(cdr(args));
    }
}

object* or_procedure(object* args) {
    if( is_empty_list(args) ) {
        return False;
    }

    if ( car(args)==True ) {
        return True;
    }
    else {
        return and_procedure(cdr(args));
    }
}

object* null_procedure(object* args) {
    return is_empty_list(car(args))?True:False;
}

object* boolean_procedure(object* args) {
    return is_boolean(car(args))?True:False;
}

object* symbol_procedure(object* args) {
    return is_symbol(car(args))?True:False;
}

object* integer_procedure(object* args) {
    return is_integer(car(args))?True:False;
}

object* char_procedure(object* args) {
    return is_character(car(args))?True:False;
}

object* string_procedure(object* args) {
    return is_string(car(args)) ?True:False;
}

object* pair_procedure(object *args) {
    return is_pair(car(args))?True:False;
}

object* procedure_procedure(object* args) {
    return (is_builtin_procedure(car(args)) || is_compound_func(car(args)))?True:False;
}

object* char_to_integer_procedure(object* args) {
    return make_integer(car(args)->data.character.value);
}

object* integer_to_char_procedure(object* args) {
    return make_character(car(args)->data.integer.value);
}

object* number_to_string_procedure(object* args) {
    char buffer[11];

    sprintf(buffer, "%ld", (car(args))->data.integer.value);
    return make_string(buffer);
}

object* string_to_number_procedure(object* args) {
    return make_integer(atoi((car(args)->data.string.value)));
}

object* symbol_to_string_procedure(object* args) {
    return make_string((car(args))->data.symbol.value);
}

object* string_to_symbol_procedure(object* args) {
    return make_symbol((car(args))->data.string.value);
}

object* cons_procedure(object* args) {
    return cons(car(args),cadr(args));
}

object* car_procedure(object* args) {
    return caar(args);
}

object* cdr_procedure(object* args) {
    return cdar(args);
}

object* set_car_procedure(object* args) {
    set_car(car(args),cadr(args));
    return ok_symbol;
}

object* set_cdr_procedure(object* args) {
    set_cdr(car(args),cadr(args));
    return ok_symbol;
}

object* list_procedure(object* args) {
    return args;
}

object* eq_procedure(object* args) {
    object *obj1;
    object *obj2;
    
    obj1 = car(args);
    obj2 = cadr(args);
    
    if (obj1->type != obj2->type) {
        return False;
    }
    switch (obj1->type) {
        case INTEGER:
            return (obj1->data.integer.value == 
                    obj2->data.integer.value) ?
                        True : False;
            break;
        case CHARACTER:
            return (obj1->data.character.value == 
                    obj2->data.character.value) ?
                        True : False;
            break;
        case STRING:
            return (strcmp(obj1->data.string.value, 
                           obj2->data.string.value) == 0) ?
                        True : False;
            break;
        default:
            return (obj1 == obj2) ? True : False;
    }
}

object* write_procedure(object* args) {
    printer((object*)args->data.string.value);
    return ok_symbol;
}

object* typeof_procedure(object* args) {
    const char *res;
    DEBUG("args' type: %d\n", args->type);
    switch (args->type) {
        case 0: 
            res = "<integer>\n";
            break;
        case 1:
            res = "<real>\n";
            break;
        case 2: 
            res = "<boolean>\n";
            break;
        case 3:
            res = "<character>\n";
            break;
        case 4:
            res = "<string>\n";
            break;
        case 5:        
            res = "<pair>\n";
            break;
        case 6:
            res = "<symbol>\n";
            break;
        case 7:
            res = "<builtin_function>\n";
            break;
        case 8:       
            res = "<compound_function\n>";
            break;
        case 9:
            res = "<empty_list>\n";
            break;
        case 10:
            res = "<warn>\n";
            break;
        case 11:
            res = "<INPUT PORT>\n";
            break;                  
        default:                   
            res = "<OUTPUT PORT>\n";
            break;
    }
    DEBUG("evaluated type to: %s\n", res);
    return (object*)res;
}