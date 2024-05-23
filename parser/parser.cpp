#include "parser.h"
#include "../scanner/scanner_ext.h"

#include <cstring>
#include <stdio.h>
#include <string.h>

void Er(int i);

bool Rules() {
    if (DirectiveLine()) {goto _end;}
    if (Program()) {goto _end;}
    return false;
  _end:
    return true;
}

bool DirectiveLine() {
    if (Command()) {goto _1;}
    return false;
  _1:
    if (lc == lexSmcl) {Nxl(); goto _2;}
    if (lc == kwVK) {Nxl(); goto _end;}
    Er(1); return false;
  _2:
    if (Command()) {goto _1;}
    Er(1); return false;
  _end:
    return true;
}

bool Program() {
    if (ProgramLine()) {goto _1;}
    return false;
  _1:
    if (ProgramLine()) {goto _1;}
    if (lc == lexEof) {Nxl(); goto _end;}
    Er(2); return false;
  _end:
    return true;
}

bool LineNum() {
    if (lc == lexLineNum) { Nxl(); goto _end; }
    return false;
  _end:
    return true;
}

bool ProgramLine() {
    if (LineNum()) {goto _1;}
    return false;
  _1:
    if (Command()) {goto _2;}
    if (lc == kwVK) {Nxl(); goto _end;}
    Er(3); return false;
  _2:
    if (lc == lexSmcl) {Nxl(); goto _3;}
    if (lc == kwVK) {Nxl(); goto _end;}
    Er(3); return false;
  _3:
    if (Command()) {goto _2;}
    Er(3); return false;
  _end:
    return true;
}

bool GrpNum() {
    if (lc == lexInt) {Nxl(); goto _end;}
    return false;
  _end:
    return true;
}

bool Command() {
    if (Set()) {goto _end;}
    if (Ask()) {goto _end;}
    if (Type()) {goto _end;}
    if (Write()) {goto _end;}
    if (Goto()) {goto _end;}
    if (If()) {goto _end;}
    if (For()) {goto _end;}
    if (Quit()) {goto _end;}
    if (Do()) {goto _end;}
    if (Return()) {goto _end;}
    if (Comment()) {goto _end;}
    if (Erase()) {goto _end;}
    if (Modify()) {goto _end;}
    if (Xecute()) {goto _end;}
    return false;
  _end:
    return true;
}

bool Set() {
    if (lc == lexId && lv[0] == 'S') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "ET") == 0) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (Var()) {goto _3;}
    Er(5); return false;
  _3:
    if (lc == lexEQ) {Nxl(); goto _4;}
    Er(5); return false;
  _4:
    if (Expr()) {goto _end;}
    Er(5); return false;
  _end:
    return true;
}

bool Var() {
    if (lc == lexId) {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexLftBr) {Nxl(); goto _2;}
    goto _end;
  _2:
    if (IndExpr()) {goto _3;}
    Er(6); return false;
  _3:
    if (lc == lexComma) {Nxl(); goto _4;}
    goto _5;
  _4:
    if (IndExpr()) {goto _5;}
    Er(6); return false;
  _5:
    if (lc == lexRghBr) {Nxl(); goto _end;}
    Er(6); return false;
  _end:
    return true;
}

bool IndExpr() {
    if (lc == lexInt) {Nxl(); goto _end;}
    if (Var()) {goto _end;}
    if (Expr()) {goto _end;}
    return false;
  _end:
    return true;
}

bool Expr() {
    if (AddExpr()) {goto _end;}
    return false;
  _end:
    return true;
}

bool AddExpr() {
    if (MulExpr()) {goto _1;}
    return false;
  _1:
    if (lc == lexPlus) {Nxl(); goto _2;}
    if (lc == lexMinus) {Nxl(); goto _2;}
    goto _end;
  _2:
    if (MulExpr()) {goto _3;}
    Er(7); return false;
  _3:
    if (lc == lexPlus) {Nxl(); goto _2;}
    if (lc == lexMinus) {Nxl(); goto _2;}
    goto _end;
  _end:
    return true;
}

bool MulExpr() {
    if (PowExpr()) {goto _1;}
    return false;
  _1:
    if (lc == lexMul) {Nxl(); goto _2;}
    if (lc == lexDiv) {Nxl(); goto _2;}
    goto _end;
  _2:
    if (PowExpr()) {goto _3;}
    Er(8); return false;
  _3:
    if (lc == lexMul) {Nxl(); goto _2;}
    if (lc == lexDiv) {Nxl(); goto _2;}
    goto _end;
  _end:
    return true;
}

bool PowExpr() {
    if (UnaryExpr()) {goto _1;}
    return false;
  _1:
    if (lc == lexCaret) {Nxl(); goto _2;}
    goto _end;
  _2:
    if (UnaryExpr()) {goto _3;}
    Er(9); return false;
  _3:
    if (lc == lexCaret) {Nxl(); goto _2;}
    goto _end;
  _end:
    return true;
}

bool UnaryExpr() {
    if (lc == lexPlus) {Nxl(); goto _1;}
    if (lc == lexMinus) {Nxl(); goto _1;}
    goto _1;
  _1:
    if (PrimaryExpr()) {goto _end;}
    Er(10); return false;
  _end:
    return true;
}

bool PrimaryExpr() {
    if (lc == lexReal) {Nxl(); goto _end;}
    if (lc == lexInt) {Nxl(); goto _end;}
    if (Var()) {goto _end;}
    if (Function()) {goto _end;}
    if (lc == lexLftBr) {Nxl(); goto _1;}
    return false;
  _1:
    if (Expr()) {goto _2;}
    Er(11); return false;
  _2:
    if (lc == lexRghBr) {Nxl(); goto _end;}
    Er(11); return false;
  _end:
    return true;
}

bool Function() {
    if (NameFunction()) {goto _1;}
    return false;
  _1:
    if (lc == lexLftBr) {Nxl(); goto _2;}
    Er(12); return false;
  _2: 
    if (Expr()) {goto _3;}
    if (lc == lexRghBr) {Nxl(); goto _end;}
    Er(12); return false;
  _3:
    if (lc == lexRghBr) {Nxl(); goto _end;}
    if (lc == lexComma) {Nxl(); goto _4;}
    Er(12); return false;
  _4:
    if (Expr()) {goto _3;}
    Er(12); return false;
  _end:
    return true;
}

bool NameFunction() {
    if (lc == kwFABS) {Nxl(); goto _end;}
    if (lc == kwFCHR) {Nxl(); goto _end;}
    if (lc == kwFCOS) {Nxl(); goto _end;}
    if (lc == kwFITR) {Nxl(); goto _end;}
    if (lc == kwFLOG) {Nxl(); goto _end;}
    if (lc == kwFRAN) {Nxl(); goto _end;}
    if (lc == kwFSBR) {Nxl(); goto _end;}
    if (lc == kwFSGN) {Nxl(); goto _end;}
    if (lc == kwFSQT) {Nxl(); goto _end;}
    if (lc == kwFSIN) {Nxl(); goto _end;}
    if (lc == kwFX) {Nxl(); goto _end;}
    return false;
  _end:
    return true;
}

bool Ask() {
    if (lc == lexId && lv[0] == 'A') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "SK")) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (IOElement()) {goto _3;}
    Er(13); return false;
  _3:
    if (lc == lexComma) {Nxl(); goto _2;}
    goto _end;
  _end:
    return true;
}

bool IOElement() {
    if (Var()) {goto _end;}
    if (lc == lexExcl) {Nxl(); goto _end;}
    if (lc == lexPercent) {Nxl(); goto _end;}
    if (lc == lexText) {Nxl(); goto _end;}
    return false;
  _end:
    return true;
}

bool Type() {
    if (lc == lexId && lv[0] == 'T') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "YPE") == 0) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (IOElement()) {goto _3;}
    Er(15); return false;
  _3:
    if (lc == lexComma) {Nxl(); goto _2;}
    goto _end;
  _end:
    return true;
}

bool Write() {
    if (lc == lexId && lv[0] == 'W') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "RITE") == 0) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (lc == LineNum()) {goto _end;}
    if (lc == GrpNum()) {goto _end;}
    if (lc == lexId && lv[0] == 'A') {Nxl(); goto _3;}
    goto _end;
  _3:
    if (lc == lexId && strcmp(lv + 1, "LL") == 0) {Nxl(); goto _end;}
    goto _end;
  _end:
    return true;
}

bool Goto() {
    if (lc == lexId && lv[0] == 'G') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "OTO") == 0) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (LineNum()) {goto _end;}
    goto _end;
  _end:
    return true;
}

bool If() {
    if (lc == lexId && lv[0] == 'I') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "F") == 0) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (lc == lexLftBr) {Nxl(); goto _3;}
    Er(16); return false;
  _3:
    if (Expr()) {goto _4;}
    Er(16); return false;
  _4:
    if (lc == lexRghBr) {Nxl(); goto _5;}
    Er(16); return false;
  _5:
    if (LineNum()) {goto _6;}
    Er(16); return false;
  _6:
    if (lc == lexComma) {Nxl(); goto _7;}
    goto _8;
  _7:
    if (LineNum()) {goto _8;}
    Er(16); return false;
  _8:
    if (lc == lexComma) {Nxl(); goto _9;}
    goto _end;
  _9:
    if (LineNum()) {goto _end;}
    Er(16); return false;
  _end:
    return true;
}

bool For() {
    if (lc == lexId && lv[0] == 'F') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "OR") == 0) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (Var()) {goto _3;}
    Er(17); return false;
  _3:
    if (lc == lexEQ) {Nxl(); goto _4;}
    Er(17); return false;
  _4:
    if (Expr()) {goto _5;} 
    Er(17); return false;
  _5:
    if (lc == lexComma) {Nxl(); goto _6;}
    goto _7;
  _6:
    if (Expr()) {goto _7;}
    Er(17); return false;
  _7:
    if (lc == lexComma) {Nxl(); goto _8;}
    goto _9;
  _8:
    if (Expr()) {goto _9;}
    Er(15); return false;
  _9:
    if (lc == lexSmcl) {Nxl(); goto _10;}
    Er(15); return false;
  _10:
    if (Command()) {goto _11;}
    goto _end;
  _11:
    if (Command()) {goto _11;}
    goto _end;
  _end:
    return true;
}

bool Quit() {
    if (lc == lexId && lv[0] == 'Q') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "UIT") == 0) {Nxl(); goto _end;}
    goto _end;
  _end:
   return true;
}

bool Do() {
    if (lc == lexId && lv[0] == 'D') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "O") == 0) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (LineNum()) {goto _end;}
    if (GrpNum()) {goto _end;}
    if (lc == lexId && lv[0] == 'A') {Nxl(); goto _3;}
    goto _end;
  _3:
    if (lc == lexId && strcmp(lv + 1, "LL") == 0) {Nxl(); goto _end;}
    goto _end;
  _end:
    return true;
}

bool Return() {
    if (lc == lexId && lv[0] == 'R') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "ETURN") == 0) {Nxl(); goto _end;}
    goto _end;
  _end:
    return true;
}

bool Comment() {
    if (lc == lexId && lv[0] == 'C') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "OMMENT") == 0) {Nxl(); goto _2;}
    if (lc == lexText) {Nxl(); goto _end;}
    Er(16); return false;
  _2:
    if (lc == lexText) {Nxl(); goto _end;}
    Er(16); return false;
  _end:
    return true;
}

bool Erase() {
    if (lc == lexId && lv[0] == 'E') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "RASE") == 0) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (LineNum()) {goto _end;}
    if (GrpNum()) {goto _end;}
    if (lc == lexId && lv[0] == 'A') {Nxl(); goto _3;}
    if (lc == lexId && lv[0] == 'T') {Nxl(); goto _4;}
    goto _end;
  _3:
    if (lc == lexId && strcmp(lv + 1, "LL") == 0) {Nxl(); goto _end;}
    goto _end;
  _4:
    if (lc == lexId && strcmp(lv + 1, "EXT") == 0) {Nxl(); goto _end;}
    goto _end;
  _end:
    return true;
}

bool Modify() {
    if (lc == lexId && lv[0] == 'M') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "ODIFY") == 0) {Nxl(); goto _2;}
    if (LineNum()) {goto _end;}
    Er(17); return false;
  _2:
    if (LineNum()) {goto _end;}
    Er(17); return false;
  _end:
    return true;
}

bool Xecute() {
    if (lc == lexId && lv[0] == 'X') {Nxl(); goto _1;}
    return false;
  _1:
    if (lc == lexId && strcmp(lv + 1, "ECUTE") == 0) {Nxl(); goto _2;}
    goto _2;
  _2:
    if (Function()) {goto _end;}
    Er(18); return false;
  _end:
    return true;
}
