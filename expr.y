%{
#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE int

int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/' '%'
%right UMINUS

%%

input:
    /* empty */
  | input line
;

line:
    '\n'
  | expr '\n' { printf("Result = %d\n", $1); }
;

expr:
    expr '+' expr { $$ = $1 + $3; }
  | expr '-' expr { $$ = $1 - $3; }
  | expr '*' expr { $$ = $1 * $3; }
  | expr '/' expr { 
        if ($3 == 0) {
          yyerror("division by zero");
          $$ = 0;
        } else {
          $$ = $1 / $3;
        }
    }
  | expr '%' expr { 
        if ($3 == 0) {
          yyerror("mod by zero");
          $$ = 0;
        } else {
          $$ = $1 % $3;
        }
    }
  | '(' expr ')' { $$ = $2; }
  | '-' expr %prec UMINUS { $$ = -$2; }
  | NUMBER { $$ = $1; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter expression:\n");
    yyparse();
    return 0;
}
