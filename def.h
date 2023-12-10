#ifndef DEF_H
#define DEF_H
#include <QtCore>
extern QString ConverToUnicode(const char* p);
//#define TEXT_CU(p) ConverToUnicode(p)


#define TEXT_CU(p) QString::fromLocal8Bit(p)


#define OFFSET_TOP  40
#define BOARD_LEFT  10
#define BOARD_TOP   (55+OFFSET_TOP)
#define SPAN_CX     50
#define SPAN_CY     50


#define BOARD_ROW   10
#define BOARD_COL   9

#define INVALID_CHESS  "0"
#endif // DEF_H

//https://www.xqbase.com/protocol/cchess_ucci.htm
