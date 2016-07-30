CC_FLAGS=-Wall

.PHONY: main
all: main

main: main.cc parser.o ast.o tokenizer.o token.o utils.o
	clang++ main.cc parser.o ast.o tokenizer.o token.o utils.o $(CC_FLAGS) -o main

parser.o: parser.cc parser.h
	clang++ -c parser.cc $(CC_FLAGS) -o parser.o

ast.o: ast.cc ast.h
	clang++ -c ast.cc $(CC_FLAGS) -o ast.o

tokenizer.o: tokenizer.cc tokenizer.h
	clang++ -c tokenizer.cc $(CC_FLAGS) -o tokenizer.o

token.o: token.cc token.h
	clang++ -c token.cc $(CC_FLAGS) -o token.o

utils.o: utils.cc utils.h
	clang++ -c utils.cc $(CC_FLAGS) -o utils.o

.PHONY: clean
clean:
	rm *.o
	rm main
