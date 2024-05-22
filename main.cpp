//------------------------------------------------------------------------------
// main.cpp - функция, тестирующая работу сканера
//------------------------------------------------------------------------------

#include     "scanner/scanner_ext.h"
#include     "parser/parser_ext.h"

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
    printf("\nПравильный формат: scanner sourced_file recived_file.\n");
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
    printf("\nОшибка в синтаксисе программы.\n");
  }

  ScanDestroy();
  fclose(outfil);
  return 0;
} 
