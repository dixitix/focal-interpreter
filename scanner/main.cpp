//------------------------------------------------------------------------------
// main.cpp - функция, тестирующая работу сканера
//------------------------------------------------------------------------------

#include     <string.h>
#include     <stdio.h>

#include     "scanner_ext.h"

void Fprintlex(FILE*);
bool ScanInit(char*);
void ScanDestroy(void);

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

  ScanDestroy();
  fclose(outfil);
  return 0;
} 
