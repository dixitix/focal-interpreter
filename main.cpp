//------------------------------------------------------------------------------
// main.cpp - функция, тестирующая работу сканера
//------------------------------------------------------------------------------

#include     "scanner/scanner_ext.h"
#include     "parser/parser_ext.h"
#include     "name_table/name_table_ext.h"

#include     <string.h>
#include     <stdio.h>

void Fprintlex(FILE*);
bool ScanInit(char*);
void ScanDestroy(void);

bool Rules(void);   

extern int errors;

FILE    *outfil;

int main(int argc, char** argv)
{
  if(argc != 3) {
    printf("\nНеправильный формат команды!\n");
    printf("\nПравильный формат: compiler input_file output_file.\n");
    return 1;
  }

  outfil = fopen(argv[2], "w");
  line = 1; column = 0;

  if(!ScanInit(argv[1])) {
    return 2;
  }
  
  while(lc != lexEof)
  {
    Fprintlex(outfil);
    Nxl();
  }
  Fprintlex(outfil);

  if(!ScanInit(argv[1])) { 
    return 2;
  }

  printf("\nЛексический анализ завершен.\n");
  printf("\nНачинаю синтаксический анализ.\n");

  if(!ScanInit(argv[1])) { 
    return 2;
  }

  if(Rules() && errors == 0)
  {
    printf("\nСинтаксис программы корректен!\n");
  }
  else
  {
    printf("\nОшибка в синтаксисе программы. Errors = %d\n", errors);
  }

  FILE* table_file = fopen(strcat(argv[2], "_table_name"), "w");

  Out(table, table_file);

  ScanDestroy();
  fclose(outfil);

  Clear(table);
  return 0;
}
