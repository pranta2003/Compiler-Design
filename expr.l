%option noyywrap
%{
#include "expr.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+  { yylval = atoi(yytext); return NUMBER; }
[ \t]+  ;  // skip whitespace
\n      return '\n';
"+"     return '+';
"-"     return '-';
"*"     return '*';
"/"     return '/';
"%"     return '%';
"("     return '(';
")"     return ')';
.       return yytext[0];

%%
