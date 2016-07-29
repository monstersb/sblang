#include <unistd.h>
#include <iostream>
#include <fstream>

#include "tokenizer.h"

int echo (std::istream &in) {
    int c;
    while ((c = in.get()) != EOF) {
        std::cout << char(c);
    }
    std::cout << std::endl;
    return 0;
}

int tokenize(std::istream &in) {
    tokenizer t(in);
    while (!t.stop()) {
        std::cout << t.next().info() << std::endl;
    }
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
    } action = SB_ACTION_NONE;
    
    while ((opt = getopt(argc, argv, "htef:")) != -1) {
        switch (opt) {
            case 't':
                if (action != SB_ACTION_NONE) {
                    return -1;
                }
                action = SB_ACTION_TOKENIZE;
                break;
            case 'e':
                if (action != SB_ACTION_NONE) {
                    return -1;
                }
                action = SB_ACTION_ECHO;
                break;
            case 'f':
                fin.open(optarg);
                if (!fin) {
                    std::cout << "file not readable" << std::endl;
                    return -1;
                }
                break;
            case 'h':
            case '?':
            default:
                std::cout << "Usage:" << std::endl;
                std::cout << "      " << argv[0] << " -t -f [filename]" << std::endl;
                std::cout << std::endl;
                std::cout << "      -h:  help" << std::endl;
                std::cout << "      -t:  tokenize" << std::endl;
                std::cout << "      -e:  echo" << std::endl;
                std::cout << "      -f:  read from file" << std::endl;
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
        case SB_ACTION_NONE:
        default:
            break;
    }
    if (fin) {
        fin.close();
    }
    return 0;
}
