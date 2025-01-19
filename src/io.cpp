#include <io.h>


object* make_input_port(FILE* in) {
    object* temp=NULL;

    temp=new_object();
    temp->type=INPUT_PORT;
    temp->data.input_port.stream=in;
    return temp;
}

object* make_output_port(FILE* out) {
    object* temp=NULL;

    temp=new_object();
    temp->type=OUTPUT_PORT;
    temp->data.output_port.stream=out;
    return temp;
}

object* load_procedure(object* args) {
    char *file=NULL;
    FILE *in=NULL;
    object* exp;

    file=car(args)->data.string.value;
    in=fopen(file,"r");
    if (in==NULL) {
        return make_warn("Exception in Load: Cannot load the file");
    }

    while( (exp=read(in))!=NULL ) {
        eval(exp,global_environment);
        printf("\n");
    }
    fclose(in);
    return ok_symbol;
}

object* read_procedure(object* args) {
    return args;
}

object* open_input_port_procedure(object* args) {
    char *file=NULL;
    FILE *in=NULL;


    file=car(args)->data.string.value;
    in=fopen(file,"r");
    if (in==NULL) {
        return make_warn("Exception in open input port: Cannot open input port");
    }
    return make_input_port(in);
}

object* close_input_port_procedure(object* args) {
    char res;

    res=fclose(car(args)->data.input_port.stream);
    if ( res==EOF ) {
        return make_warn("Exception in close input port: Cannot close input port");
    }
    return ok_symbol;
}

object* open_output_port_procedure(object* args) {
    char *file=NULL;
    FILE *out=NULL;


    file=car(args)->data.string.value;
    out=fopen(file,"w");
    if (out==NULL) {
        return make_warn("Exception in open input port: Cannot open input port");
    }
    return make_output_port(out);
}

object* close_output_port_procedure(object* args) {
    char res;

    res=fclose(car(args)->data.output_port.stream);
    if ( res==EOF ) {
        return make_warn("Exception in close input port: Cannot close input port");
    }
    return ok_symbol;
}    

object* is_input_port_procedure(object* args) {
    return is_input_port(car(args))?True:False;
}

object* is_output_port_procedure(object* args) {
    return is_output_port(car(args))?True:False;
}