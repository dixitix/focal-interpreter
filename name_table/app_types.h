#pragma once

//------------------------------------------------------------------------------
// Файл app_types.h - содержит элементы таблицы имен, определяющие назначение
// именованных программных объектов.
//------------------------------------------------------------------------------

#include <stdio.h>

class Application 
{
public:
  virtual void Out(FILE* of = stdout) = 0;
};

enum varType {USUAL_TYPE, INDEXED_TYPE};

// Класс, определяющий переменную
class AppVariable: public Application
{
public:
  void Out(FILE* of = stdout);

  varType _type; 
  int    _addr;
};
