#include <sstream>
#include <iomanip>
#include <stdarg.h>
#include "utils.h"

string repr(string s) {
    std::ostringstream r;
    r << '"';
    for (string::iterator i = s.begin(); i != s.end(); ++i) {
        switch (*i) {
            case '\n':
                r << "\\n";
                break;
            case '\r':
                r << "\\r";
                break;
            case '\t':
                r << "\\t";
                break;
            case '\v':
                r << "\\v";
                break;
            case '\f':
                r << "\\f";
                break;
            case '\x20' ... '\x7e':
                if (*i == '\\' || *i == '"') {
                    r << "\\";
                }
                r << *i;
                break;
            default:
                r << "\\x" << std::hex << int(*i);
                break;
        }
    }
    r << '"';
    return r.str();
}

string format(string fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char *p;
    vasprintf(&p, fmt.c_str(), args);
    string r(p);
    free(p);
    return r;
}
