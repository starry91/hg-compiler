%{
  #include <iostream>
  #include <cstdio>
  using namespace std;
  extern "C" int yylex();
  int linenum = 1;
%}
%x COMMENTS
%%
[ \t\n] ;
break   {
    cout << "found break" << endl;
    // return BREAK; 
}
continue    {
    cout << "found continue" << endl;
    // return CONTINUE; 
}
else    {
    cout << "found else" << endl;
    // return ELSE;
}
false   {
    cout << "found false" << endl;
    // return FALSE;
}
for {
    cout << "found for" << endl;
    // return FOR;
}
if  {
    cout << "found if" << endl;
    // return IF;
}
int {
    cout << "found int" << endl;
    // return INT;
}
bool {
    cout << "found int" << endl;
    // return BOOL;
}
char {
    cout << "found int" << endl;
    // return CHAR;
}
uint {
    cout << "found int" << endl;
    // return UINT;
}
sint {
    cout << "found int" << endl;
    // return SINT;
}
return  {
    cout << "found return" << endl;
    // return RETURN;
}
true    {
    cout << "found true" << endl;
    // return TRUE;
}
void    {
    cout << "found void" << endl;
    // return VOID;
}
while   {
    cout << "found while" << endl;
    // return WHILE;
}
cout {
    cout<< "found COUT" <<endl;
    // return COUT;
}
cin {
    cout<<"found CIN"<<endl;
    // CIN;
}
endl {
    cout<<"found endl"<<endl;
    // ENDL;
}

, {
    cout << "found comma" << endl;
    // return COMMA;
}
; {
    cout<<"found semicolon"<<endl;
    // return SEMICOLON;
}
[\{] {
    cout << "found Braces Open" << endl;
    // return BRACE_OPEN;
}
[\}] {
    cout << "found Braces close" << endl;
    // return BRACE_CURLY_CLOSE;
}
[\(] {
    cout << "found paranthesis open" <<endl;
    // return BRACE_PARAN_OPEN;
}
[\)] {
    cout << "found paranthesis close" <<endl;
    // return BRACE_PARAN_CLOSE;
}
\[ {
    cout << "found square open" <<endl;
    // return BRACE_SQUARE_OPEN;
}
\] {
    cout << "found square close" <<endl;
    // return BRACE_SQUARE_CLOSE;
}
\/\/.* {
    cout<<"found SINGLE COMMENT"<<endl;
    // return SINGLE_COMMENT;
}
\<\< {
    cout << "found Left shift" << endl;
    // return LEFT_SHIFT;
}
>> {
    cout << "found right shift" << endl;
    // return RIGHT_SHIFT;
}
[0-9]+  {
    cout << "Found an integer:" << endl;
    // return NUM_CONST;
}
[a-zA-Z][a-zA-Z0-9]*    {
    cout << "Found a ID" << endl;
    // return ID;
}
\"[a-zA-Z0-9]+\"    {
    cout << "Found a CHAR_LITERAL" << endl;
    // return CHAR_CONST;
}
(\+|\-|\*|\/|AND|OR|\^|==|!=|<=|>=|<|>)   {
    cout << "found Bin Op" << endl;
    // return BIN_OP;
}
(\+\+|--|!|-)   {
    cout << "found Unary Op" << endl;
    // return UNARY_OP;
}
=   {
    cout << "found Equal to Op" << endl;
    // return EQUAL_OP;
}
\/* { // start of a comment: go to a 'COMMENTS' state.
    BEGIN(COMMENTS);
}
<COMMENTS>*\/   {   // end of a comment: go back to normal parsing.
    BEGIN(INITIAL);
}
<COMMENTS>\n    { ++linenum; }   // still have to increment line numbers inside of comments!
<COMMENTS>. ;   // ignore every other character while we're in this state
%%

int main(int argc, char** argv) {
    // open a file handle to a particular file:
    FILE *myfile = fopen(argv[1], "r");
    // make sure it's valid:
    if (!myfile) {
        cout << "I can't open a.snazzle.file!" << endl;
        // return -1;
    }
    // set lex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    // lex through the input:
    while(yylex());
}