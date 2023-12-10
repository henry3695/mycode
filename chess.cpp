#include "chess.h"
#include "def.h"
Chess::Chess(QString sName,ChessColor clr)
    :m_Name(sName)
    ,m_Color(clr)
{
}
void Chess::Draw(QPainter& painter,int i,int j)
{
    //painter.setPen(Qt::NoPen);  // 不绘制边框
    if(GetColor()==ChessColor::RED)
    {
        painter.setBrush(Qt::red);
    }
    else
    {
        painter.setBrush(Qt::black);  // 设置圆的填充颜色
    }
    painter.drawEllipse(BOARD_LEFT+j*SPAN_CX, BOARD_TOP+i*SPAN_CY, 35, 35);

    // 设置文本颜色和字体
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 20,1000));
    painter.drawText(BOARD_LEFT+3+j*SPAN_CX, BOARD_TOP+28+i*SPAN_CY, GetName());
}
QString Chess::GetName()
{
    return  m_Name;
}

void  Chess::SetName(QString sName)
{
    m_Name=sName;
}

void Chess::SetChessColor(ChessColor clr)
{
    m_Color=clr;
}

ChessColor Chess::GetColor()
{
    return  m_Color;
}


