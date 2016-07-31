#ifndef SB_LOG_H
#define SB_LOG_H

#include <iostream>

using std::ostream;
using std::cout;
using std::endl;
using std::string;

typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    
    LOG_LEVEL_COUNT,
} sb_log_level_t;

class sb_log {
private:
    std::ostream &out;
    sb_log_level_t level;
    void _log(sb_log_level_t l, string tag, string s);
    static sb_log logger;

public:
    sb_log();
    sb_log(ostream &_out);
    sb_log(ostream &_out, sb_log_level_t _level);
    sb_log(sb_log_level_t _level);

    static void set_level(sb_log_level_t _level);

    static void log(sb_log_level_t l, string s);

    static void info(string s);
    static void debug(string s);
    static void warning(string s);
    static void error(string s);
};

#endif // SB_LOG_H