#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../scanner/scanner_ext.h"

bool Rules(); 
bool DirectiveLine();
bool Program();
bool ProgramLine();
bool LineNum();
bool GrpNum(); 
bool Command();
bool Set();
bool Var();
bool IndExpr();
bool Expr();
bool AddExpr();
bool MulExpr();
bool PowExpr();
bool UnaryExpr();
bool PrimaryExpr();
bool Function();
bool NameFunction();
bool Ask();
bool IOElement();
bool Type();
bool Write();
bool Goto();
bool If();
bool For();
bool Quit();
bool Do();
bool Return();
bool Comment();
bool Erase();
bool Modify();
bool Xecute();

void Er();

int errors = 0;