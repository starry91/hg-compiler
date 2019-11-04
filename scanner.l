%{
    #include <iostream>
    #include "ast.h"
    #include "parser.tab.h"
    using namespace std;
    int linenum = 1;
%}
%x COMMENTS
%%
[ \t] {
    cout << yytext;
}
[\n] {
    cout << yytext;
    ++linenum;
}
break   {
    cout << yytext;
    return BREAK; 
}
continue    {
    cout << yytext;
    return CONTINUE; 
}
else    {
    cout << yytext;
    return ELSE;
}
true    {
    cout << yytext;
    return TRUE;
}
false   {
    cout << yytext;
    return FALSE;
}
for {
    cout << yytext;
    return FOR;
}
if  {
    cout << yytext;
    return IF;
}
int {
    cout << yytext;
    return INT;
}
bool {
    cout << yytext;
    return BOOL;
}
char {
    cout << yytext;
    return CHAR;
}
uint {
    cout << yytext;
    return UINT;
}
sint {
    cout << yytext;
    return SINT;
}
return  {
    cout << yytext;
    return RETURN;
}
void    {
    cout << yytext;
    return VOID;
}
while   {
    cout << yytext;
    return WHILE;
}
cout {
    cout << yytext;
    return COUT;
}
cin {
    cout << yytext;
    return CIN;
}
endl {
    cout << yytext;
    return ENDL;
}
[;,\?:=\(\)\[\]\{\}]    {
    cout << yytext;
    return yytext[0];
}
\/\/.* {
    cout << yytext;
}
\<\< {
    cout << yytext;
    return LEFT_SHIFT;
}
>> {
    cout << yytext;
    return RIGHT_SHIFT;
}
[0-9]+  {
    cout << yytext;
    // yylval.ival = atoi(yytext);
    yylval.num_const = new NumConstASTnode(atoi(yytext));
    return NUM_CONST;
}
[a-zA-Z][a-zA-Z0-9]*    {
    cout << yytext;
    yylval.sval = strdup(yytext);
    return ID;
}
\".*\"    {
    cout << yytext;
    // yylval.sval = strdup(yytext);
    yylval.char_const = new CharConstASTnode(string(yytext));
    return CHAR_CONST;
}
\+|\-|\*|\/|&&|\|\||\^|==|!=|<=|>=|<|>|%   {
    cout << yytext;
    yylval.sval = strdup(yytext);
    return BIN_OP;
}
(\+\+|--|!|-)   {
    cout << yytext;
    yylval.sval = strdup(yytext);
    return UNARY_OP;
}
\/\* { // start of a comment: go to a 'COMMENTS' state.
    BEGIN(COMMENTS);
}
<COMMENTS>\*\/   {   // end of a comment: go back to normal parsing.
    BEGIN(INITIAL);
}
<COMMENTS>\n    { ++linenum; }
<COMMENTS>. ;
%%

// int main(int argc, char** argv) {
//     // open a file handle to a particular file:
//     FILE *myfile = fopen(argv[1], "r");
//     // make sure it's valid:
//     if (!myfile) {
//         cout << "I can't open a.snazzle.file!" << endl;
//         return -1;
//     }
//     // set lex to read from it instead of defaulting to STDIN:
//     yyin = myfile;

//     // lex through the input:
//     while(yylex());
// }