#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置中文字体
#if 0
       a.setFont(QFont("Microsoft Yahei", 9));

       //设置中文编码
   #if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
   #if _MSC_VER
       QTextCodec *codec = QTextCodec::codecForName("gbk");
   #else
       QTextCodec *codec = QTextCodec::codecForName("utf-8");
   #endif
       QTextCodec::setCodecForLocale(codec);
       QTextCodec::setCodecForCStrings(codec);
       QTextCodec::setCodecForTr(codec);
   #else
       QTextCodec *codec = QTextCodec::codecForName("utf-8");
       QTextCodec::setCodecForLocale(codec);
   #endif

       QString str(QObject::tr("1中文"));
       qDebug() << str;
       //qDebug() << QStringLiteral("2中文");
       qDebug() << QString::fromLatin1("3中文");
       qDebug() << QString::fromLocal8Bit("4中文");
       qDebug() << TEXT_CU("5中文");
       qDebug() << QString::fromWCharArray(L"6中文");
#endif

    Widget w;
    w.show();
    return a.exec();
}
