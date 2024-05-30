#pragma once

//------------------------------------------------------------------------------
// Файл name_table_ext.h - содержит описания типов и данных, 
// используемых функциями, работающими с таблицей имен
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>

#include "app_types.h"

typedef std::map<std::string, Application*, std::less<std::string> > NameTable;

extern NameTable table;

extern int glob_addr;

void Out(NameTable &table, FILE *os = stdout);

void Clear(NameTable &table);
