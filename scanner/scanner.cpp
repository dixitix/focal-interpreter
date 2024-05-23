#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "scanner_data.h"
#include "scanner_local.h"
#include "scanner_type.h"

//------------------------------------------------------------------------------
// Функции транслитератора, используемые для определения класса лексем
//------------------------------------------------------------------------------

// Определяет принадлежность символа к классу букв
bool inline IsAlpha(int ch) {
  if((ch >= 'A' && ch <= 'Z')) {
    return true;
  } else {
    return false;
  }
}

// Определяет принадлежность символа к классу цифр
bool inline IsDigit(int ch) {
  if((ch >= '0' && ch <= '9')) {
    return true;
  } else {
    return false;
  } 
}

// Определяет принадлежность символа к классу игнорируемых
bool inline IsIgnore(int ch) {
  if(ch > 0 && ch < ' ' && ch != '\t' && ch != '\n' && ch != '\f') {
    return true;
  } else {
    return false;
  } 
}

//------------------------------------------------------------------------------
// Вспомогательные инструменты.
//------------------------------------------------------------------------------

// Максимальное значение двоичного целого числа до сдвига. 
// Используется для проверки на переполнение
unsigned int u_dec_max = (0x7FFFFFFF / 10);

// Преобразование строки десятичных цифр в целое число
unsigned int DecToInt(char* str)
{
  unsigned int num = 0;
  while(*str != '\0')
  {
    unsigned int digit = static_cast<unsigned int>(*str);
    if(u_dec_max < num)
    { 
      lc = lexError;
      return 0;
    }
    num = (num * 10) + (digit - static_cast<unsigned int>('0'));
    ++str;
  }
  return num;
}

// Определяет принадлежность к ключевому слову
static void FindKw(void)
{
  for (int i = 0; i < rw_size; ++i) {
     if (!strcmp(rwtab[i].wrd, lv)) {
      lc = rwtab[i].lc;
      return;
    }
  }
   
  lc = lexId;
}

// Читает следующий символ из входного потока
static void Nxch(void)
{
    if((ch = getc(infil)) == '\n') {
        ++line; 
        column = 0;
    } else {
        ++column;
    }
    ++pos;
}

// Откат назад при неудачной попытке распознать лексему
static void Unset() {
  fseek(infil, oldpos, 0);  
  Nxch();
  i_lv = -1; 
  lv[0] = '\0'; 
  pos = oldpos;
  line = oldline; 
  column = oldcolumn;
}

//------------------------------------------------------------------------------
// Лексический анализатор.
//------------------------------------------------------------------------------

// Определяет принадлежность символа к классу пробелов
bool inline IsSkip(int ch) {
  if(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\f') {
    return true;
  } else {
    return false;
  } 
}

// Определяет принадлежность символа к классу левых скобок
bool inline IsLeftParenthesis(int ch) {
  if(ch == '(' || ch == '[' || ch == '<') {
    return true;
  } else {
    return false;
  } 
}

// Определяет принадлежность символа к классу правых скобок
bool inline IsRightParenthesis(int ch) {
  if(ch == ')' || ch == ']' || ch == '>') {
    return true;
  } else {
    return false;
  } 
}

// Распознавание идентификатора или ключевого слова
static bool IsIdOrKw()
{
  if (IsAlpha(ch) || ch == '_') {
    lv[++i_lv] = ch; 
    Nxch();
  } else {
    return false;
  }

  while (IsAlpha(ch) || IsDigit(ch) || ch == '_') {
    lv[++i_lv] = ch;
    Nxch();
  }

  lv[++i_lv] = '\0';
  FindKw(); 
  return true;
}

// Распознавание целого десятичного числа
static bool IsInteger() {
  if(IsDigit(ch)) {
    lv[++i_lv] = ch; 
    Nxch();
  } else {
    return false;
  }
  while (IsDigit(ch)){
    lv[++i_lv] = ch;
    Nxch();
  }
  if (IsAlpha(ch)) {lc = lexError; lv[++i_lv] = '\0'; return true;}
  lc = lexInt; lv[++i_lv] = '\0'; 
  unum = DecToInt(lv);
  return true; 
}

static bool IsLineNum() {
  if (IsDigit(ch)) {
    lv[++i_lv] = ch;
    Nxch();
    goto _1;
  } else {
    return false;
  }
  _1:
  if (IsDigit(ch)) {
    lv[++i_lv] = ch;
    Nxch();
    goto _2;
  }
  if (ch == '.') {
    lv[++i_lv] = ch;
    Nxch();
    goto _3;
  }
  return false;
  _2:
  if (ch == '.') {
    lv[++i_lv] = ch;
    Nxch();
    goto _3;
  }
  return false;
  _3:
  if (IsDigit(ch)) {
    lv[++i_lv] = ch;
    Nxch();
    goto _4;
  }
  return false;
  _4:
  if (IsDigit(ch)) {
    lv[++i_lv] = ch;
    Nxch();
    goto _end;
  }
  return false;
  _end:
  if (IsAlpha(ch) || ch == '_') {
    lc = lexError; lv[++i_lv] = '\0'; return true;
  }
  lc = lexLineNum;
  lv[++i_lv] = '\0';
  return true;
}

// Распознавание вещественного числа.
static bool IsReal() {
  if(IsDigit(ch)) {
    lv[++i_lv]=ch;
    Nxch();
    goto _1;
  } else {
    return false;
  }
  _1:
  if(IsDigit(ch)) {
    lv[++i_lv]=ch;
    Nxch();
    goto _1;
  }
  if(ch=='.') {
    lv[++i_lv]=ch;
    Nxch();
    goto _2;
  }
  return false;
  _2:
  if(IsDigit(ch)) {
    lv[++i_lv]=ch;
    Nxch();
    goto _2;
  }
  if(ch=='E') {
    lv[++i_lv]=ch;
    Nxch();
    goto _3;
  };
  goto _end;
  _3:
  if((ch=='+') || (ch=='-')) {
    lv[++i_lv]=ch;
    Nxch();
    goto _4;
  };
  if(IsDigit(ch)) {
    lv[++i_lv]=ch;
    Nxch();
    goto _5;
  }
  return false;
  _4:
  if(IsDigit(ch)) {
    lv[++i_lv]=ch;
    Nxch();
    goto _5;
  }
  return false;
  _5:
  if(IsDigit(ch)) {
    lv[++i_lv]=ch;
    Nxch();
    goto _5;
  }
  goto _end;
  _end:
  if(IsAlpha(ch) || ch=='_')
  {
    lc=lexError; lv[++i_lv]='\0'; return true;
  }
  lc = lexReal;
  lv[++i_lv] = '\0';
  dnum = atof(lv);
  return true;
}

// Распознавание строки любых символов кроме "
static bool IsText(void)
{
//_0:
  if(ch == '\"') {
    Nxch(); 
    goto _1;
  } else {
    return false;
  }
_1:
  if(ch == '\"') {
    Nxch(); 
    goto _2;
  }
  if(ch == EOF) { 
    lc = lexError; 
    lv[++i_lv] = '\0'; 
    return true; //  чтобы не было отката
  }
  lv[++i_lv] = ch; 
  Nxch();
  goto _1;
_2:
  if(ch == '\"') { 
    lv[++i_lv] = ch; 
    Nxch(); 
    goto _1;
  }
  lc = lexText; 
  lv[++i_lv] = '\0'; 
  return true;
}

// Распознавание комментария
static bool IsComment()
{
    if (ch == '/') {Nxch();}
    else { return false; }
    if (ch != '*') {return false;}
    Nxch();
  loop:
    if(ch == EOF) {
      lc = lexError; 
      lv[++i_lv] = '\0'; 
      return true;
    } 
    while(ch != '*') {
      if(ch == EOF) 
      {
        lc = lexError; 
        lv[++i_lv] = '\0'; 
        return true;
      }
      Nxch();
    }
    Nxch(); 
    if(ch != '/') 
    {
      goto loop;
    }
    lv[++i_lv] = '\0';
    lc = lexComment;
    Nxch();
    return true;   
}

// Функция, формирующая следующую лексему
void Nxl(void) {
  do {
    i_lv = -1;   
    lv[0] = '\0';

    oldpos = ftell(infil)-1;
    oldline = line; 
    oldcolumn = column;

    if(ch == EOF) {lc = lexEof; return;}
    if(IsSkip(ch)) {Nxch(); lc = lexSkip; continue; /*return;*/}
    if(IsIgnore(ch)) {Nxch(); lc = lexIgnore; continue; /*return;*/}
    if(IsIdOrKw()) {return;} Unset();
    if(IsText()) {return;} Unset();
    if(IsLeftParenthesis(ch)) {Nxch(); lc = lexLftBr; return;}
    if(IsRightParenthesis(ch)) {Nxch(); lc = lexRghBr; return;}
    if(IsComment())      {continue; /*return;*/} Unset();
    if(IsLineNum()) {return;} Unset();
    if(IsReal()) {return;} Unset();
    if(IsInteger()) {return;} Unset();
    if(ch == ';') {Nxch(); lc = lexSmcl; return;}
    if(ch == ',') {Nxch(); lc = lexComma; return;}
    if(ch == '.') {Nxch(); lc = lexPeriod; return;}
    if(ch == '@') {Nxch(); lc = lexATR; return;}
    if(ch == '+') {Nxch(); lc = lexPlus; return;}
    if(ch == '-') {Nxch(); lc = lexMinus; return;}
    if(ch == '*') {Nxch(); lc = lexMul; return;}
    if(ch == '/') {Nxch(); lc = lexDiv; return;}
    if(ch == '^') {Nxch(); lc = lexCaret; return;}
    if(ch == '%') {Nxch(); lc = lexPercent; return;}
    if(ch == '=') {Nxch(); lc = lexEQ; return;}
    if(ch == 'e') {Nxch(); lc = lexEE; return;}
    if(ch == '!') {Nxch(); lc = lexExcl; return;}
    lc = lexError; Nxch();
  } while (lc == lexComment || lc == lexSkip || lc == lexIgnore);
}

// Функция, инициирующая работу со сканером
bool ScanInit(char *file_name) {
  if((infil = fopen(file_name, "r")) == nullptr) {
    printf("\nОтсутствует входной файл.\n"); 
    return false;
  }

  Nxch();
  Nxl();

  return true;
}

// Функция, завершающая работу сканера
void ScanDestroy() {
  fclose(infil);
}
