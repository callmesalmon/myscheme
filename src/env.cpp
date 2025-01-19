#include <env.h>


int is_empty_env(object* env) {
    return env==empty_environment;
}

object* enclosing_env(object* env) {
    return cdr(env);
}

object* first_frame(object* env) {
    return car(env);
}

object* frame_var(object* frame) {
    return car(frame);
}

object* frame_val(object* frame) {
    return cdr(frame);
}

object* loop_up_env(object* var, object* env) {
    object* frame;
    object* var_list;
    object* val_list;
    while (!is_empty_list(env)) {
        frame=first_frame(env);
        var_list=frame_var(frame);
        val_list=frame_val(frame);
        while (!is_empty_list(var_list)) {
            if (var==car(var_list)) {
                return car(val_list);
            }
            var_list=cdr(var_list);
            val_list=cdr(val_list);
        }
        env=enclosing_env(env);
    }
    // fprintf(stderr," unbound variable\n");
    // exit(1);
    return make_warn("unbound variable");
}

void add_to_frame(object* var,object* val, object* frame) {
    set_car(frame , cons(var , car(frame)));
    set_cdr(frame , cons(val , cdr(frame)));
}

object* make_frame(object* var,object* val) {
    return cons(var,val);
}

object* extend_env(object* var,object* val, object* old_env) {
    return cons(make_frame(var,val),old_env);
}

int set_var_val(object* var, object* val, object* env) {
    object* frame;
    object* var_list;
    object* val_list;

    while ( !is_empty_list(env)) {
        frame=first_frame(env);
        var_list=frame_var(frame);
        val_list=frame_val(frame);
        while ( !is_empty_list(var_list) ) {
            if (var==car(var_list) ) {
                set_car(val_list, val);
                return 1;
            }
            var_list=cdr(var_list);
            val_list=cdr(val_list);
        }
        env=enclosing_env(env);
    }
    // fprintf(stderr,"unbound variable\n");
    // exit(1);
    return 0;
}

void def_var_val(object* var, object* val, object* env) {
    object* frame;
    object* var_list;
    object* val_list;

    frame=first_frame(env);
    var_list=frame_var(frame);
    val_list=frame_val(frame);

    while ( !is_empty_list(var_list)) {
        if (var==car(var_list)) {
            set_car(val_list, val);
            return;
        }
        var_list=cdr(var_list);
        val_list=cdr(val_list);
    }
    add_to_frame(var,val,frame);
}

object* setup_env() {
    object * env=NULL;
    
    env=extend_env( empty_list, empty_list, empty_environment);

    return env;
}