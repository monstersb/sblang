#include <iomanip>

#include "log.h"


#define LOG_LEVEL_DESC(l, c)                                                                        \
{ l, #l, c }

struct {
    sb_log_level_t level;
    string name;
    string color;
} log_level_desc[LOG_LEVEL_COUNT] = {
    LOG_LEVEL_DESC(LOG_LEVEL_DEBUG, "\033[32m"),
    LOG_LEVEL_DESC(LOG_LEVEL_INFO, "\033[36m"),
    LOG_LEVEL_DESC(LOG_LEVEL_WARNING, "\033[33m"),
    LOG_LEVEL_DESC(LOG_LEVEL_ERROR, "\033[31m"),
};

sb_log sb_log::logger = sb_log();

sb_log::sb_log():out(cout), level(LOG_LEVEL_DEBUG) {
    
}

sb_log::sb_log(ostream &_out):out(_out), level(LOG_LEVEL_DEBUG) {
    
}

sb_log::sb_log(ostream &_out, sb_log_level_t _level):out(_out), level(_level) {
    
}

sb_log::sb_log(sb_log_level_t _level):out(cout), level(_level) {
    
}

void sb_log::set_level(sb_log_level_t _level) {
    logger.level = _level;
}

void sb_log::_log(sb_log_level_t l, string tag, string s) {
    if (l >= level) {
        out.setf(std::ios::left);
        out << log_level_desc[l].color;
        out << "[ " << std::setw(17) << log_level_desc[l].name << " ]: " << s;
        out << "\033[0m" << endl;
    }
}

void sb_log::log(sb_log_level_t l, string s) {
    logger._log(l, "", s);
}


void sb_log::info(string s) {
    logger._log(LOG_LEVEL_INFO, "", s);
}

void sb_log::debug(string s) {
    logger._log(LOG_LEVEL_DEBUG, "", s);
}

void sb_log::warning(string s) {
    logger._log(LOG_LEVEL_WARNING, "", s);
}

void sb_log::error(string s) {
    logger._log(LOG_LEVEL_ERROR, "", s);
}

