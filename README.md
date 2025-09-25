# Compiler-Design

Welcome to the **Compiler-Design** repository! This repository contains **Flex-based lexical analyzers** demonstrating different concepts in **lexical analysis**, a fundamental phase of compiler design. Each program tokenizes input, counts characters, or recognizes patterns.

---

## 🌟 Animated Welcome Message

<div style="text-align:center;">
  <h1 style="color:#1E90FF; animation: colorchange 4s infinite;">🚀 Welcome to Compiler-Design Repo 🚀</h1>
  <p style="font-size:16px; color:#333;">Learn <strong>Lexical Analysis</strong> with Flex code examples and token recognition.</p>
  <marquee behavior="scroll" direction="left" scrollamount="5" style="color:red; font-weight:bold;">
    Run the code and count characters, vowels, or identifiers in your input!
  </marquee>
</div>


---

## 💻 Lexical Analyzer Codes

### 1️⃣ Count Total Characters
```c
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


Explanation: [A-Z] matches uppercase letters, [a-z] matches lowercase. . ignores other characters.

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


Explanation: Detects keywords, identifiers, numbers, operators, delimiters, strings, and comments. Uses yytext to print matched tokens. Reads input from input.txt.

4️⃣ Pattern Matching Examples
^.*aa$          {printf("Matched: %s\n", yytext);}
^.*[^.*aa$]     {printf("Not Matched: %s\n", yytext);}


Explanation: ^ → start of line, $ → end of line. Flex matches strings exactly or by pattern.

5️⃣ Number Systems
0[xX][0-9a-fA-F]+    { printf("Hexadecimal: %s\n", yytext); }
0[bB][01]+           { printf("Binary: %s\n", yytext); }
0[0-7]+              { printf("Octal: %s\n", yytext); }
0?[1-9][0-9]*        { printf("Decimal: %s\n", yytext); }


Detects binary, octal, decimal, and hexadecimal numbers.

6️⃣ Vowels & Consonants Count
[aeiouAEIOU]              v++;
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]   c++;
.                          ;
\n                         return 0;

✅ How to Run Flex Programs
flex filename.l
gcc lex.yy.c -lfl -o output
./output

🌈 Interactive HTML Example
<div style="text-align:center;">
  <h2 style="color:#FF6347; animation: bounce 2s infinite;">Lexical Analyzer in Action!</h2>
  <p style="font-size:16px; color:#2E8B57;">Check your input and see tokens highlighted live.</p>
  <marquee behavior="alternate" scrollamount="10" style="color:purple; font-weight:bold;">
    Modify patterns and see results in real-time!
  </marquee>
</div>

<style>
@keyframes bounce {
  0% {transform: translateY(0px);}
  50% {transform: translateY(-15px);}
  100% {transform: translateY(0px);}
}
</style>

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
