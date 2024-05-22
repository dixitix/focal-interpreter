//------------------------------------------------------------------------------
// tesout.cpp - тестовый вывод информации о лексемах
//------------------------------------------------------------------------------

#include "scanner_ext.h"
#include "scanner_type.h"

#include <stdio.h>

int const kBufSize = 256;

void Fprintlex(FILE* f) 
{
  char* lcs;
  char* lvs;

  switch(lc) 
  {
    case lexEof:       lcs=(char*)"lexEof";      lvs=(char*)"-1";  break;
    case lexSkip:     lcs=(char*)"lexSkip";    lvs=(char*)" "; break;
    case lexComment:    lcs=(char*)"lexComment";   lvs=lv;   break;
    case lexIgnore:      lcs=(char*)"lexIgnore";     lvs=lv;  break;
    case lexSmcl:      lcs=(char*)"lexSmcl";     lvs=(char*)";";  break;
    case lexComma:         lcs=(char*)"lexComma";        lvs=(char*)",";  break;
    case lexPeriod:          lcs=(char*)"lexPeriod";      lvs=(char*)"."; break;
    case lexATR:      lcs=(char*)"lexATR";     lvs=lvs=(char*)'@';  break;
    case lexPlus:        lcs=(char*)"lexPlus";       lvs=(char*)"+"; break;
    case lexMinus:      lcs=(char*)"lexMinus";     lvs=(char*)"-";   break;
    case lexReal:      
      lcs=(char*)"lexReal";     lvs=lv;   
      fprintf(f, "[%d, %d]    \tlc: %s\t\tlv: %s\t\tdnum = %e\n", 
        line, column, lcs, lvs, dnum);  
      return;
    case lexMul:         lcs=(char*)"lexMul";        lvs=(char*)"*"; break;
    case lexDiv:         lcs=(char*)"lexDiv";        lvs=(char*)"/";  break;
    case lexCaret:         lcs=(char*)"lexCaret";    lvs=(char*)"^";   break;
    case lexPercent:     lcs=(char*)"lexPercent";    lvs=(char*)"%";   break;
    case lexInt:        
      lcs = (char*)"lexInt";
      lvs = lv;
      fprintf(f, "[%d, %d]    \tlc: %s\t\tlv: %s\t\tunum = %u\n", 
        line, column, lcs, lvs, unum);  
      return;
    case lexEQ:         lcs=(char*)"lexEQ";        lvs=(char*)"="; break;
    case lexEE:   lcs=(char*)"lexEE";  lvs=(char*)"E";  break;
    case lexExcl:    lcs=(char*)"lexExcl";   lvs=(char*)"!";  break;
    case lexError:      lcs=(char*)"lexError";     lvs=lv;  break;
    case lexId:      lcs=(char*)"lexId";     lvs=lv;  break;
    case lexText:      lcs=(char*)"lexText";     lvs=lv;  break;
    case lexLftBr:      lcs=(char*)"lexLftBr";     lvs=(char*)"(";  break;
    case lexRghBr:      lcs=(char*)"lexRghBr";     lvs=(char*)")";  break;

    case kwFABS:       lcs=(char*)"KWFABS";      lvs=lv;   break;
    case kwFCHR:       lcs=(char*)"KWFCHR";      lvs=lv;   break;
    case kwFCOS:       lcs=(char*)"KWFCOS";      lvs=lv;   break;
    case kwFITR:       lcs=(char*)"KWFITR";      lvs=lv;   break;
    case kwFLOG:       lcs=(char*)"KWFLOG";      lvs=lv;   break;
    case kwFRAN:       lcs=(char*)"KWFRAN";      lvs=lv;   break;
    case kwFSBR:       lcs=(char*)"KWFSBR";      lvs=lv;   break;
    case kwFSGN:       lcs=(char*)"KWFSGN";      lvs=lv;   break;
    case kwFSQT:       lcs=(char*)"KWFSQT";      lvs=lv;   break;
    case kwFSIN:       lcs=(char*)"KWFSIN";      lvs=lv;   break;
    case kwFX:       lcs=(char*)"KWFX";      lvs=lv;   break;
    case kwVK:       lcs=(char*)"KWVK";      lvs=lv;   break;

    default:            lcs=(char*)"nonprinted lex class"; lvs=lv;
  }
  fprintf(f, "[%d, %d]    \tlc: %s\t\tlv: %s\n", line, column, lcs, lvs);  
}
