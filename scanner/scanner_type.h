#pragma once

//------------------------------------------------------------------------------
// scanner_type.h - содержит общие для всех типы данных
//------------------------------------------------------------------------------

typedef enum {
  lexEof,
  lexSkip,
  lexComment,
  lexIgnore,
  lexSmcl,
  lexComma,
  lexPeriod,
  lexATR,
  lexPlus,
  lexMinus,
  lexMul,
  lexDiv,
  lexCaret,
  lexPercent,
  lexEQ,
  lexEE,
  lexExcl,
  lexQuote,
  lexError,
  lexInt,
  lexReal,
  lexId,
  lexText,
  lexLftBr,
  lexRghBr,

  kwFABS,
  kwFCHR,
  kwFCOS,
  kwFITR,
  kwFLOG,
  kwFRAN,
  kwFSBR,
  kwFSGN,
  kwFSQT,
  kwFSIN,
  kwFX,
  kwVK
} LcType;
