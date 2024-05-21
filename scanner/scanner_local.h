#pragma once

//------------------------------------------------------------------------------
// scanner_local.h - описание типов данных, используемых только сканером
//------------------------------------------------------------------------------

#include "scanner_type.h"

typedef enum {
    tltLetter, tltDigit, tltSkip
} SicType;

struct FindString {
    char* wrd;   
    LcType lc;
};

struct FindString rwtab[] = {
    {(char*)"VK", kwVK},
    {(char*)"FABS",   kwFABS},
    {(char*)"FCHR",   kwFCHR},
    {(char*)"FCOS",   kwFCOS},
    {(char*)"FITR",   kwFITR},
    {(char*)"FLOG",   kwFLOG},
    {(char*)"FRAN",   kwFRAN},
    {(char*)"FSBR",   kwFSBR},
    {(char*)"FSGN",   kwFSGN},
    {(char*)"FSQT",   kwFSQT},
    {(char*)"FSIN",   kwFSIN},
    {(char*)"FX",   kwFX}
};

int rw_size = sizeof(rwtab) / sizeof(FindString);

long int pos = 0, oldpos;
int oldline, oldcolumn;
