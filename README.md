
Compiler-Design

Welcome to the Compiler-Design repository!
This repository contains Flex-based lexical analyzers demonstrating different concepts in lexical analysis, a fundamental phase of compiler design. Each program tokenizes input, counts characters, or recognizes patterns.

💻 Lexical Analyzer Codes
1️⃣ Count Total Characters

Counts all characters in the input.

%{
#include <stdio.h>
int v = 0;
%}

%%
.          v++;
\n         return 0;
%%

int yywrap(){}
int main(){
    printf("Enter String: ");
    yylex();
    printf("\nNumber of Char = %d ", v);
    return 0;
}


Explanation:

. matches any character except newline and increments v.

\n stops the scanner.

2️⃣ Count Uppercase & Lowercase Letters
%{
#include <stdio.h>
int up = 0;
int low = 0;
%}

%%
[A-Z]      up++;
[a-z]      low++;
.          ;
\n         return 0;
%%

int yywrap(){}
int main(){
    printf("Enter String: ");
    yylex();
    printf("\nNumber of UpperCase = %d \nNumber of LowerCase = %d \n", up, low);
    return 0;
}


Explanation:

[A-Z] matches uppercase letters, [a-z] matches lowercase.

. ignores other characters.

3️⃣ Identify Keywords, Operators, Identifiers, Numbers, Strings, Comments
%{
#include <stdio.h>
#include <string.h>
FILE *yyin;
%}

%%
"int"|"float"|"char"|"if"|"else"|"while"|"return"  { printf("KEYWORD: %s\n", yytext); }
[0-9]+(\.[0-9]+)?                                { printf("NUMBER: %s\n", yytext); }
"=="|"<="|">="|"!="|">"|"<"                     { printf("RELATIONAL OPERATOR: %s\n", yytext); }
"="|"+"|"-"|"*"|"/"                             { printf("OPERATOR: %s\n", yytext); }
"(" | ")" | "{" | "}" | ";" | ","              { printf("DELIMITER: %s\n", yytext); }
\"[^\"]*\"                                      { printf("STRING: %s\n", yytext); }
"//".*                                         { printf("COMMENT (SINGLE LINE): %s\n", yytext); }
"/*"([^*]|\*+[^*/])*\*+"/"                    { printf("COMMENT (MULTI LINE): %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                        { printf("IDENTIFIER: %s\n", yytext); }
[ \t\n]+                                      ; // Ignore whitespace
.                                             { printf("UNKNOWN: %s\n", yytext); }
%%

int yywrap() { return 1; }

int main(int argc, char **argv) {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("Failed to open input.txt");
        return 1;
    }
    yylex();
    fclose(yyin);
    return 0;
}


Explanation:

Detects keywords, identifiers, numbers, operators, delimiters, strings, and comments.

Uses yytext to print matched tokens.

Reads input from input.txt.

4️⃣ Pattern Matching Examples

Match exact patterns like "aa" or "abb".

Recognize sequences using regular expressions in Flex.

Example:

^.*aa$          {printf("Matched: %s\n", yytext);}
^.*[^.*aa$]     {printf("Not Matched: %s\n", yytext);}


Explanation:

^ → start of line, $ → end of line.

Flex matches strings exactly or by pattern.

5️⃣ Number Systems

Recognizes binary, octal, decimal, and hexadecimal numbers.

0[xX][0-9a-fA-F]+    { printf("Hexadecimal: %s\n", yytext); }
0[bB][01]+           { printf("Binary: %s\n", yytext); }
0[0-7]+              { printf("Octal: %s\n", yytext); }
0?[1-9][0-9]*        { printf("Decimal: %s\n", yytext); }


Tip:

Use regex patterns for each numeric type.

Great for lexical analyzers handling multiple number systems.

6️⃣ Vowels & Consonants Count
[aeiouAEIOU]              v++;
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]   c++;
.                          ;
\n                         return 0;


Simple example of character classification in Flex.

✅ How to Run Flex Programs
flex filename.l
gcc lex.yy.c -lfl -o output
./output


flex filename.l → generates scanner lex.yy.c.

gcc lex.yy.c -lfl -o output → compile with Flex library.

./output → run scanner.

🌟 HTML & Visuals for README

You can make this README interactive and visually appealing using simple HTML snippets. Example:

<h2 style="color:blue; text-align:center;">Welcome to Compiler-Design Repo</h2>

<p style="font-size:16px;">
Learn <strong>Lexical Analysis</strong> with Flex code examples and token recognition.
</p>

<marquee behavior="scroll" direction="left" scrollamount="5" style="color:red;">
Try running the code and count characters, vowels, or identifiers in your input!
</marquee>


marquee → moving text animation.

style → colors, fonts, alignment.

Works inside GitHub README (.md) because GitHub renders basic HTML.

📂 Folder Structure
Compiler-Design/
│
├─ Lexical/
│   ├─ count_char.l
│   ├─ count_case.l
│   ├─ keyword_identifier.l
│   ├─ pattern_match.l
│   ├─ number_system.l
│   ├─ vowel_consonant.l
│   └─ ...
└─ README.md

🎯 Learning Tips

Run each example with different inputs to see Flex in action.

Modify patterns to create your own token rules.

Practice building a full compiler lexer using these examples.
