#pragma once

//------------------------------------------------------------------------------
// Файл name_table.h - содержит описания типов и данных, 
// используемых функциями, работающими с таблицей имен
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string>
#include <map>

#include "app_types.h"

typedef std::map<std::string, Application*, std::less<std::string> > NameTable;

NameTable table;

int glob_addr = 0;
