#pragma once

int errors = 0;

void Er(int);

static char *error_messages[] = {
  (char*)"Error in \"Rules\" rool",
  (char*)"Error in \"DirectiveLine\" rool",
  (char*)"Error in \"Program\" rool",
  (char*)"Error in \"ProgramLine\" rool",
  (char*)"Error in \"Set\" rool",
  (char*)"Error in \"Var\" rool",
  (char*)"Error in \"AddExpr\" rool",
  (char*)"Error in \"MulExpr\" rool",
  (char*)"Error in \"PowExpr\" rool",
  (char*)"Error in \"PrimaryExpr\" rool",
  (char*)"Error in \"Function\" rool",
  (char*)"Error in \"Ask\" rool",
  (char*)"Error in \"IOElement\" rool",
  (char*)"Error in \"Type\" rool",
  (char*)"Error in \"If\" rool",
  (char*)"Error in \"For\" rool",
  (char*)"Error in \"Comment\" rool",
  (char*)"Error in \"Modify\" rool",
  (char*)"Error in \"Xecute\" rool",
  (char*)"Error in \"Var\" rool. It is not variable!",
};
