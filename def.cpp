#include "def.h"
QString ConverToUnicode(const char* p)
{
    QByteArray ba = p;
    QTextCodec *gbk = QTextCodec::codecForName("GBK");
    QString strUnicode = gbk->toUnicode(ba);
    return strUnicode;
}
