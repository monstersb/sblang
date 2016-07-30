#include <unistd.h>
#include <iostream>
#include <fstream>

#include "tokenizer.h"
#include "parser.h"
#include "log.h"


int echo(std::istream &in) {
    int c;
    while ((c = in.get()) != EOF) {
        std::cout << char(c);
    }
    return 0;
}

int tokenize(std::istream &in) {
    sb_tokenizer t(in);
    while (!t.stop()) {
        sb_token tk = t.next();
        if (tk.type == TK_T_INVALID) {
            std::cout << "INVALID TOKEN at line: " << t.line() << ", column: " << t.column()
                      << std::endl;
        } else if (tk.type == TK_T_NONE) {
            continue;
        } else {
            sb_log::info(tk.info());
        }
    }
    return 0;
}

int parse(std::istream &in) {
    sb_parser p(in);
    std::cout << p.parse() << std::endl;
    return 0;
}

int usage(string argv) {
    std::cout << "Usage:" << std::endl;
    std::cout << "      " << argv << " -e -f [filename]" << std::endl;
    std::cout << std::endl;
    std::cout << "      -h:  help" << std::endl;
    std::cout << "      -e:  echo" << std::endl;
    std::cout << "      -t:  tokenize" << std::endl;
    std::cout << "      -p:  parse" << std::endl;
    std::cout << "      -f:  read from file" << std::endl;
    std::cout << "      -l:  log level [0 - 4]" << std::endl;
    return 0;
}

int main(int argc, char *argv[]) {
    std::ifstream fin;
    fin.setstate(std::ios_base::badbit);
    int opt;
    enum {
        SB_ACTION_NONE,
        SB_ACTION_ECHO,
        SB_ACTION_TOKENIZE,
        SB_ACTION_PARSE,
    } action = SB_ACTION_NONE;

    while ((opt = getopt(argc, argv, "hetpf:l:")) != -1) {
        switch (opt) {
            case 'e':
                if (action != SB_ACTION_NONE) {
                    return -1;
                }
                action = SB_ACTION_ECHO;
                break;
            case 't':
                if (action != SB_ACTION_NONE) {
                    return -1;
                }
                action = SB_ACTION_TOKENIZE;
                break;
            case 'p':
                if (action != SB_ACTION_NONE) {
                    return -1;
                }
                action = SB_ACTION_PARSE;
                break;
            case 'f':
                fin.open(optarg);
                if (!fin) {
                    std::cout << "file not readable" << std::endl;
                    return -1;
                }
                break;
            case 'l':
                if (optarg[0] >= '0' and optarg[0] < '0' + LOG_LEVEL_COUNT && optarg[1] == '\0') {
                    sb_log::set_level(sb_log_level_t(optarg[0] - '0'));
                } else {
                    std::cout << "invalid log level" << std::endl;
                    usage(argv[0]);
                    return -1;
                }
                break;
            case 'h':
            case '?':
            default:
                usage(argv[0]);
                return -1;
        }
    }
    std::istream &in = fin ? fin : std::cin;
    switch (action) {
        case SB_ACTION_ECHO:
            echo(in);
            break;
        case SB_ACTION_TOKENIZE:
            tokenize(in);
            break;
        case SB_ACTION_PARSE:
            parse(in);
            break;
        case SB_ACTION_NONE:
        default:
            break;
    }
    if (fin) {
        fin.close();
    }
    return 0;
}
