%{
  #include <iostream>
  using namespace std;
  extern int yylex();
%}
%%
[ \t\n] ;
bool    {
    cout << "bool" << endl;
    // return BOOL; 
}
break   {
    cout << "break" << endl;
    // return BREAK; 
}
continue    {
    cout << "continue" << endl;
    // return CONTINUE; 
}
else    {
    cout << "else" << endl;
    // return ELSE;
}
false   {
    cout << "false" << endl;
    // return FALSE;
}
for {
    cout << "for" << endl;
    // return FOR;
}
if  {
    cout << "if" << endl;
    // return IF;
}
int {
    cout << "int" << endl;
    // return INT;
}
return  {
    cout << "return" << endl;
    // return RETURN;
}
true    {
    cout << "true" << endl;
    // return TRUE;
}
void    {
    cout << "void" << endl;
    // VOID;
}
while   {
    cout << "while" << endl;
    // return WHILE;
}
char    {
    cout << "char" << endl;
    // return CHAR;
}
[0-9]+\.[0-9]+  {
    cout << "Found a floating-point number:" << float << endl;
}
[0-9]+  {
    cout << "Found an integer:" << int << endl;
}
[a-zA-Z0-9]+    {
    cout << "Found a string: " << string << endl;
}
[ \t\n]          ;
.              ;
%%
int main(int, char**) {
  
//   open a file handle to a particular file:
//   FILE *myfile = fopen("a.snazzle.file", "r");
//   make sure it's valid:
//   if (!myfile) {
//     cout << "I can't open a.snazzle.file!" << endl;
//     return -1;
//   }
//   set lex to read from it instead of defaulting to STDIN:
//   yyin = myfile;
  
//   lex through the input:
  while(yylex());
}