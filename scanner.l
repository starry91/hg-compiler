%{
    #include <iostream>
    #include "parser.tab.h"
    using namespace std;
    int linenum = 1;
%}
%x COMMENTS
%%
[ \t\n] ;
break   {
    cout << "found break" << endl;
    return BREAK; 
}
continue    {
    cout << "found continue" << endl;
    return CONTINUE; 
}
else    {
    cout << "found else" << endl;
    return ELSE;
}
false   {
    cout << "found false" << endl;
    return FALSE;
}
for {
    cout << "found for" << endl;
    return FOR;
}
if  {
    cout << "found if" << endl;
    return IF;
}
int {
    cout << "found int" << endl;
    return INT;
}
bool {
    cout << "found int" << endl;
    return BOOL;
}
char {
    cout << "found int" << endl;
    return CHAR;
}
uint {
    cout << "found int" << endl;
    return UINT;
}
sint {
    cout << "found int" << endl;
    return SINT;
}
return  {
    cout << "found return" << endl;
    return RETURN;
}
true    {
    cout << "found true" << endl;
    return TRUE;
}
void    {
    cout << "found void" << endl;
    return VOID;
}
while   {
    cout << "found while" << endl;
    return WHILE;
}
cout {
    cout<< "found COUT" <<endl;
    return COUT;
}
cin {
    cout<<"found CIN"<<endl;
    // CIN;
}
endl {
    cout<<"found endl"<<endl;
    // ENDL;
}
[;,\?:=\(\)\[\]\{\}]    {
    cout << "special char " << endl;
    return yytext[0];
}
\/\/.* {
    cout<<"found SINGLE COMMENT"<<endl;
    return SINGLE_COMMENT;
}
\<\< {
    cout << "found Left shift" << endl;
    return LEFT_SHIFT;
}
>> {
    cout << "found right shift" << endl;
    return RIGHT_SHIFT;
}
[0-9]+  {
    cout << "Found an integer:" << endl;
    return NUM_CONST;
}
[a-zA-Z][a-zA-Z0-9]*    {
    cout << "Found a ID" << endl;
    return ID;
}
\".*\"    {
    cout << "Found a CHAR_LITERAL" << endl;
    return CHAR_CONST;
}
(\+|\-|\*|\/|AND|OR|\^|==|!=|<=|>=|<|>)   {
    cout << "found Bin Op" << endl;
    return BIN_OP;
}
(\+\+|--|!|-)   {
    cout << "found Unary Op" << endl;
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