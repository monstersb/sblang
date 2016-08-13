#ifndef SB_TYPE_H
#define SB_TYPE_H

#include <string>

using std::string;

class sb_t_object {
public:
    sb_t_object(){};
    virtual ~sb_t_object(){};

    virtual string str();
    virtual sb_t_object *copy();
};

class sb_t_null : public sb_t_object {
public:
    virtual string str();
};

class sb_t_int : public sb_t_object {
public:
    int value;

    sb_t_int(int v);

    virtual string str();
};

class sb_t_string : public sb_t_object {
public:
    string value;

    sb_t_string(string v);

    virtual string str();
};


#endif // SB_TYPE_H
