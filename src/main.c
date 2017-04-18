/* File: main.c */
/* Another blood offering */
#include <stdio.h>
#include "lex.yy.c"
int size = 0;
void insert(char** c);
void display();
struct SymbTab {
	char* string;
	struct SymbTab *next;
};
struct SymbTab *first,*last;
int next = -1;
int pass = 1;
void program();
void stmt();
void stmt_list();
void stmt_list_prime();
void expr();
void expr_prime();
void term();
void term_prime();
void factor();
int lookahead();
void match(int tok);
void error();

// Runs our recursive descent parser
int main() {
	FILE *myFile;
	myFile = fopen("infile.txt","r");
	if(!myFile) {
		fprintf(stderr, "can't open infile.txt\nResorting to stdin\n");
		yyin = stdin;
	} else {
	yyin = myFile;
	}
	// First pass to populate symbol tables
	program();
	display();
	fclose(myFile);
	myFile = fopen("infile.txt","r");
	if(!myFile) {
		fprintf(stderr, "can't open infile.txt\nResorting to stdin\n");
		yyin = stdin;
	} else {
	yyin = myFile;
	}
	// Second pass to display .code
	pass = 2;
	program();
	fclose(myFile);
}

/* Recursive Descent Parser Functions/Productions */
void program() {
	//printf("in program() block\n");

	match( BEGINTOK );
	if(pass == 2)
		printf("Section\t.code\n");
	stmt_list();
	match( ENDTOK );
	if(pass == 2)
		printf("\tHALT\n");
}

void stmt()
{
	//printf("in stmt() block\n");
	match( ID );
	if(pass == 1)
		insert(&yylstring);
	if(pass == 2)
		printf("\tLVALUE\t%s\n",yylstring);
//	printf("matching ID\n");
//  push the ID into the symbol table
//	printf("ID: %s\n", yylstring);
	match( ASSIGNTOK );
	expr();
	if(pass == 2)
		printf("\tSTO\n");
}

void stmt_list()
{
	//printf("in stmt_list() block\n");
	stmt();
	stmt_list_prime();
}

void stmt_list_prime()
{
	//printf("in stmt_list_prime() block\n");
	int temp = lookahead();
	if( SEMITOK == temp )
	{
		match( SEMITOK );
		stmt();
		stmt_list_prime();
	}
}

void expr()
{
	//printf("in expr() block\n");
	term();
	expr_prime();
}

void expr_prime()
{
	//printf("in expr_prime() block\n");
	int temp = lookahead();
	if( PLUSTOK == temp )
	{
		match( PLUSTOK );
		term();
		if(pass == 2)
			printf("\tADD\n");
		expr_prime();
	}
	if( MINUSTOK == temp )
	{
		match( MINUSTOK );
		term();
		if(pass == 2)
			printf("\tSUB\n");
		expr_prime();
	}
}

void term()
{
	//printf("in term() block\n");
	factor();
	term_prime();
}

void term_prime()
{
	//printf("in term_prime() block\n");
	int temp = lookahead();
	if( MULTOK == temp )
	{
		match( MULTOK );
		factor();
		if(pass == 2)
			printf("\tMPY\n");
		term_prime();
	}
	if( DIVTOK == temp )
	{
		match( DIVTOK );
		factor();
		if(pass == 2)
			printf("\tDIV\n");
		term_prime();
	}
	if( MODTOK == temp )
	{
		match( MODTOK );
		factor();
		if(pass == 2)
			printf("\tMOD\n");
		term_prime();
	}
}

void factor()
{
	//printf("in factor() block\n");
	int temp = lookahead();
	if( ID == temp )
	{
		//printf("matching ID\n");
		//printf("ID: %s\n", yylstring);
		match( ID );
		if(pass == 1)
			insert(&yylstring);
		if(pass == 2)
			printf("\tRVALUE\t%s\n", yylstring);
	}
	if( NUM == temp )
	{
		//printf("matching Number\n");
		//printf("NUM value: %lf\n", yylval);
		match( NUM );
		if(pass == 2)
			printf("\tPUSH\t%d\n", yylval);
	}
	if( LPARENTOK == temp )
	{
		//printf("matching expr\n");
		match( LPARENTOK );
		expr();
		match( RPARENTOK );
	}
}
/*End of Recursive Descent Parser Productions*/

/*Helper functions*/
int lookahead()
{
	//printf("enter input\n");
	if(next == -1) next = yylex();
	//printf("yylex: %d\n", next);
	return next;
}

void match(int tok)
{
	//printf("matchmaker?\n");
	if (tok == lookahead()) { next = -1;/* printf("Success!\n");*/ }
	else error(tok);
}

/*Symbol Table Functions*/
/* Yeah we have warnings here, but it inserts and prints out the strings.
   So ¯\_(ツ)_/¯ */
void insert(char** c) {
	struct SymbTab *p;
	p = malloc(sizeof(struct SymbTab));
	strcpy(&p->string,c);
	p->next=NULL;
	if(size==0) {
		first=p;
		last=p;
	}
	else {
		last->next=p;
		last=p;
	}
	size++;
}

void display() {
	int i;
	struct SymbTab *p;
	p=first;
	printf("Section\t.data\n");
	for(i=0; i < size; i++) {
		printf("\t%s:\tword\n",p->string);
		p=p->next;
	}
}

/*Error*/
void error(int i)
{
	printf("Parse error!\n");
	switch (i) {
		case 1:
			printf("No begin statement\n");
			break;
		case 2:
			printf("No end statement\n");
			break;
		case 3:
			printf("Missing :=\n");
			break;
		case 4:
			printf("Missing ;\n");
			break;
		case 11:
			printf("Expected )\n");
			break;
		case 12:
			printf("Expected an ID\n");
			break;
		case 13:
			printf("Expected a number\n");
			break;
		default:
			break;
	}
	exit(1);
}
