all: main

main: main.cc tokenizer.o token.o
	clang++ main.cc tokenizer.o token.o -Wall -o main

tokenizer.o: tokenizer.cc tokenizer.h
	clang++ -c tokenizer.cc -Wall -o tokenizer.o

token.o: token.cc token.h
	clang++ -c token.cc -Wall -o token.o

.PHONY: clean
clean:
	rm *.o
	rm main
