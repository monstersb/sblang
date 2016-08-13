#include "type.h"
#include "utils.h"

string sb_t_object::str() {
    return "object";
}

sb_t_object *sb_t_object::copy() {
    return new sb_t_object();
}


string sb_t_null::str() {
    return "null";
}


sb_t_int::sb_t_int(int v) : value(v) {}

string sb_t_int::str() {
    return format("%d", value);
}


sb_t_string::sb_t_string(string v) : value(v) {}

string sb_t_string::str() {
    return value;
}
