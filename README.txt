This is a Recursive Descent Compiler using flex for Tokenization.
The file that was unzipped includes compiled executable files.
To compile this on your machine make a copy of the directory structure 
like you see here:
./
├── build
│   ├── lexer
│   └── parser
├── include
│   └── recdec.h
├── infile.txt
├── Makefile
└── src
    ├── lex.yy.c
    ├── main.c
    ├── rules.l

Then use:
$ make clean
$ make
$ ./build/parser
To compile and run the program from "scratch".

If you use an input file please name it "infile.txt"
Else you will resort to user input. 

If you want to send the output to a .asm file please use I/O redirection 
$ ./build/parser > test.asm 
