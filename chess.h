#ifndef CHESS_H
#define CHESS_H

#include <QtCore>
#include <QPainter>

enum ChessColor{
    RED,
    BLACK
};

class Chess
{
public:
    Chess(QString sName,ChessColor clr);

    void Draw(QPainter& painter,int i,int j);
    inline QString GetName();
    inline ChessColor GetColor();
    void SetName(QString sName);
    void SetChessColor(ChessColor clr);
private:
    QString     m_Name;//车马炮
    ChessColor  m_Color;
};

#endif // CHESS_H
