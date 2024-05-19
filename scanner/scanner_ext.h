#ifndef __scanner_ext__
#define __scanner_ext__

//------------------------------------------------------------------------------
// scanner_ext.h - экспортируемые объекты сканера
//------------------------------------------------------------------------------

#include <stdio.h>
#include "scanner_type.h"

void Nxl(void); // используемая всеми функция взятия следующей лексемы

extern LcType     lc;
extern char  lv[]; 

extern int line,    // номер текущей строки
           column;  // номер текущего столбца

extern unsigned int unum; // преобразованное значение целого
extern double       dnum; // преобразованное значение действительного

extern FILE  *infil;

#endif
