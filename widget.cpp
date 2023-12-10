#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QtCore>
#include <QMouseEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //QPixmap pixmap(qApp->applicationDirPath() +"/chess_board.png");  // 替换为你的PNG图片路径
    // ui->labelboard->setPixmap(pixmap);
    //ui->labelboard->resize(pixmap.width(), pixmap.height());
    //resize(pixmap.width(), pixmap.height());

    m_imgChessBoard.load(qApp->applicationDirPath() +"/chess_board.png");
    resize(m_imgChessBoard.width(), m_imgChessBoard.height()+OFFSET_TOP);


    //move(500,800);

    Chess* pChess = new Chess(TEXT_CU("车"),ChessColor::RED);
    m_mapChess[TEXT_CU("红车")]=pChess;

    pChess = new Chess(TEXT_CU("马"),ChessColor::RED);
    m_mapChess[TEXT_CU("红马")]=pChess;

    pChess = new Chess(TEXT_CU("相"),ChessColor::RED);
    m_mapChess[TEXT_CU("红相")]=pChess;

    pChess = new Chess(TEXT_CU("仕"),ChessColor::RED);
    m_mapChess[TEXT_CU("红仕")]=pChess;

    pChess = new Chess(TEXT_CU("帅"),ChessColor::RED);
    m_mapChess[TEXT_CU("红帅")]=pChess;

    pChess = new Chess(TEXT_CU("炮"),ChessColor::RED);
    m_mapChess[TEXT_CU("红炮")]=pChess;

    pChess = new Chess(TEXT_CU("兵"),ChessColor::RED);
    m_mapChess[TEXT_CU("红兵")]=pChess;


    pChess = new Chess(TEXT_CU("车"),ChessColor::BLACK);
    m_mapChess[TEXT_CU("黑车")]=pChess;

    pChess = new Chess(TEXT_CU("马"),ChessColor::BLACK);
    m_mapChess[TEXT_CU("黑马")]=pChess;

    pChess = new Chess(TEXT_CU("象"),ChessColor::BLACK);
    m_mapChess[TEXT_CU("黑象")]=pChess;

    pChess = new Chess(TEXT_CU("士"),ChessColor::BLACK);
    m_mapChess[TEXT_CU("黑士")]=pChess;

    pChess = new Chess(TEXT_CU("将"),ChessColor::BLACK);
    m_mapChess[TEXT_CU("黑将")]=pChess;

    pChess = new Chess(TEXT_CU("炮"),ChessColor::BLACK);
    m_mapChess[TEXT_CU("黑炮")]=pChess;

    pChess = new Chess(TEXT_CU("卒"),ChessColor::BLACK);
    m_mapChess[TEXT_CU("黑卒")]=pChess;

    m_clrLocal=ChessColor::RED;

    m_bSel=false;
    LoadMap();
    LoadRect();
    Reset();
    installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::LoadRect()
{
    for(int i=0;i<BOARD_ROW;i++)
    {
        for(int j=0;j<BOARD_COL;j++)
        {
            m_aryRect[i][j]=QRect(BOARD_LEFT+j*SPAN_CX, BOARD_TOP+i*SPAN_CY, 35, 35);
        }
    }
}
void Widget::Rollover()
{
    QString sTmp;
    for(int i=0;i<BOARD_ROW/2;i++)
    {
        for(int j=0;j<BOARD_COL;j++)
        {
            sTmp =m_aryData[i][j];
            m_aryData[i][j] = m_aryData[BOARD_ROW-1-i][BOARD_COL-1-j];
            m_aryData[BOARD_ROW-1-i][BOARD_COL-1-j]=sTmp;
        }
    }
}

void Widget::LoadMap()
{
    //position fen rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1
    m_mpQ2Z[TEXT_CU("红车")]="R";
    m_mpQ2Z[TEXT_CU("红马")]="N";
    m_mpQ2Z[TEXT_CU("红相")]="B";
    m_mpQ2Z[TEXT_CU("红仕")]="A";
    m_mpQ2Z[TEXT_CU("红帅")]="K";
    m_mpQ2Z[TEXT_CU("红炮")]="C";
    m_mpQ2Z[TEXT_CU("红兵")]="P";

    m_mpQ2Z[TEXT_CU("黑车")]="r";
    m_mpQ2Z[TEXT_CU("黑马")]="n";
    m_mpQ2Z[TEXT_CU("黑象")]="b";
    m_mpQ2Z[TEXT_CU("黑士")]="a";
    m_mpQ2Z[TEXT_CU("黑将")]="k";
    m_mpQ2Z[TEXT_CU("黑炮")]="c";
    m_mpQ2Z[TEXT_CU("黑卒")]="p";

    for(auto itor=m_mpQ2Z.begin();itor!=m_mpQ2Z.end();itor++)
    {
        m_mpZ2Q[itor.value()]=itor.key();
    }
}
void Widget::Reset()
{
    for(int i=0;i<BOARD_ROW;i++)
    {
        for(int j=0;j<BOARD_COL;j++)
        {
            m_aryData[i][j]=INVALID_CHESS;
        }
    }
    if(m_clrLocal==ChessColor::RED)
    {
        m_aryData[9][0]=TEXT_CU("红车");
        m_aryData[9][1]=TEXT_CU("红马");
        m_aryData[9][2]=TEXT_CU("红相");
        m_aryData[9][3]=TEXT_CU("红仕");
        m_aryData[9][4]=TEXT_CU("红帅");
        m_aryData[9][5]=TEXT_CU("红仕");
        m_aryData[9][6]=TEXT_CU("红相");
        m_aryData[9][7]=TEXT_CU("红马");
        m_aryData[9][8]=TEXT_CU("红车");
        m_aryData[7][1]=TEXT_CU("红炮");
        m_aryData[7][7]=TEXT_CU("红炮");
        m_aryData[6][0]=TEXT_CU("红兵");
        m_aryData[6][2]=TEXT_CU("红兵");
        m_aryData[6][4]=TEXT_CU("红兵");
        m_aryData[6][6]=TEXT_CU("红兵");
        m_aryData[6][8]=TEXT_CU("红兵");

        m_aryData[0][0]=TEXT_CU("黑车");
        m_aryData[0][1]=TEXT_CU("黑马");
        m_aryData[0][2]=TEXT_CU("黑象");
        m_aryData[0][3]=TEXT_CU("黑士");
        m_aryData[0][4]=TEXT_CU("黑将");
        m_aryData[0][5]=TEXT_CU("黑士");
        m_aryData[0][6]=TEXT_CU("黑象");
        m_aryData[0][7]=TEXT_CU("黑马");
        m_aryData[0][8]=TEXT_CU("黑车");
        m_aryData[2][1]=TEXT_CU("黑炮");
        m_aryData[2][7]=TEXT_CU("黑炮");
        m_aryData[3][0]=TEXT_CU("黑卒");
        m_aryData[3][2]=TEXT_CU("黑卒");
        m_aryData[3][4]=TEXT_CU("黑卒");
        m_aryData[3][6]=TEXT_CU("黑卒");
        m_aryData[3][8]=TEXT_CU("黑卒");
    }
    else
    {
        m_aryData[0][0]=TEXT_CU("红车");
        m_aryData[0][1]=TEXT_CU("红马");
        m_aryData[0][2]=TEXT_CU("红相");
        m_aryData[0][3]=TEXT_CU("红仕");
        m_aryData[0][4]=TEXT_CU("红帅");
        m_aryData[0][5]=TEXT_CU("红仕");
        m_aryData[0][6]=TEXT_CU("红相");
        m_aryData[0][7]=TEXT_CU("红马");
        m_aryData[0][8]=TEXT_CU("红车");
        m_aryData[2][1]=TEXT_CU("红炮");
        m_aryData[2][7]=TEXT_CU("红炮");
        m_aryData[3][0]=TEXT_CU("红兵");
        m_aryData[3][2]=TEXT_CU("红兵");
        m_aryData[3][4]=TEXT_CU("红兵");
        m_aryData[3][6]=TEXT_CU("红兵");
        m_aryData[3][8]=TEXT_CU("红兵");

        m_aryData[9][0]=TEXT_CU("黑车");
        m_aryData[9][1]=TEXT_CU("黑马");
        m_aryData[9][2]=TEXT_CU("黑象");
        m_aryData[9][3]=TEXT_CU("黑士");
        m_aryData[9][4]=TEXT_CU("黑将");
        m_aryData[9][5]=TEXT_CU("黑士");
        m_aryData[9][6]=TEXT_CU("黑象");
        m_aryData[9][7]=TEXT_CU("黑马");
        m_aryData[9][8]=TEXT_CU("黑车");
        m_aryData[7][1]=TEXT_CU("黑炮");
        m_aryData[7][7]=TEXT_CU("黑炮");
        m_aryData[6][0]=TEXT_CU("黑卒");
        m_aryData[6][2]=TEXT_CU("黑卒");
        m_aryData[6][4]=TEXT_CU("黑卒");
        m_aryData[6][6]=TEXT_CU("黑卒");
        m_aryData[6][8]=TEXT_CU("黑卒");
    }
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton && mouseEvent->modifiers() == Qt::ControlModifier) {
            // 组合键ctrl+鼠标左键被按下
            // 在这里执行你需要的操作
            QPoint mousePos = mouseEvent->pos();
            //int x = mousePos.x();
            //int y = mousePos.y();
            //qDebug()<<"x="<<x<<",y="<<y;


            for(int i=0;i<BOARD_ROW;i++)
            {
                for(int j=0;j<BOARD_COL;j++)
                {
                    const QRect& rct = m_aryRect[i][j];
                    if(rct.contains(mousePos) && m_aryData[i][j]!=INVALID_CHESS)
                    {
                        m_aryData[i][j]=INVALID_CHESS;
                        m_bSel=false;
                        update();
                        goto loop;
                    }
                }
            }
loop:
            ;
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint mousePos = event->pos();
        //int x = mousePos.x();
        //int y = mousePos.y();
        //qDebug()<<"x="<<x<<",y="<<y;

        bool b = m_bSel;
        m_bSel=false;
        for(int i=0;i<BOARD_ROW;i++)
        {
            for(int j=0;j<BOARD_COL;j++)
            {
                const QRect& rct = m_aryRect[i][j];
                if(rct.contains(mousePos) && m_aryData[i][j]!=INVALID_CHESS)
                {
                    //qDebug()<<"i="<<i<<",j="<<j<<","<<m_aryData[i][j];
                    m_bSel=true;
                    m_selidx.first=i;
                    m_selidx.second=j;
                    update();
                    return;
                }
            }
        }

        if(b && m_bSel==false)
        {
            update();
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        QPoint mousePos = event->pos();
        //int x = mousePos.x();
        //int y = mousePos.y();
        if(!m_bSel)
            return;

        for(int i=0;i<BOARD_ROW;i++)
        {
            for(int j=0;j<BOARD_COL;j++)
            {
                const QRect& rct = m_aryRect[i][j];
                if(rct.contains(mousePos))
                {
                    //qDebug()<<"i="<<i<<",j="<<j<<","<<m_aryData[i][j];
                    m_bSel=false;

                    if(i!=m_selidx.first || j!=m_selidx.second)
                    {
                        m_aryData[i][j]=m_aryData[m_selidx.first][m_selidx.second];
                        m_aryData[m_selidx.first][m_selidx.second]=INVALID_CHESS;
                    }

                    update();
                    return;
                }
            }
        }

        m_bSel=false;
        update();
    }
}
void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //qDebug()<<"void Widget::paintEvent(QPaintEvent *event)";
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿
    // 绘制图片
    painter.drawPixmap(0, OFFSET_TOP, m_imgChessBoard);
    for(int i=0;i<BOARD_ROW;i++)
    {
        for(int j=0;j<BOARD_COL;j++)
        {
            const QString sKey = m_aryData[i][j];
            if(sKey!="0")
            {
                m_mapChess[sKey]->Draw(painter,i,j);
            }
        }
    }

    if(m_bSel)
    {
        int i=m_selidx.first;
        int j=m_selidx.second;
        const QString sKey = m_aryData[i][j];

        QBrush brush;
        if(m_mapChess[sKey]->GetColor()==ChessColor::RED)
        {
            brush=(QColor(0, 0, 255, 128));
        }
        else
        {
            brush=(QColor(255, 255, 255, 128));
        }
        painter.setBrush(brush);
        painter.drawEllipse(m_aryRect[i][j]);
    }

    //drawArrow(painter, 50, 50, 150, 150);
}

void Widget::on_pushButtonChange_clicked()
{
    if(m_clrLocal==ChessColor::RED)
    {
        m_clrLocal=ChessColor::BLACK;
    }
    else
    {
        m_clrLocal=ChessColor::RED;
    }
    Rollover();
    update();
}

void Widget::on_pushButtonReset_clicked()
{
    m_clrLocal=ChessColor::RED;
    Reset();
    update();
}

void Widget::on_pushButtonOut_clicked()
{
    QString str("position fen ");
    QString sTmp;
    int nc = 0;
    for(int i=0;i<BOARD_ROW;i++)
    {
        sTmp="";
        nc=0;
        for(int j=0;j<BOARD_COL;j++)
        {
            if(m_aryData[i][j]==INVALID_CHESS)
            {
                nc++;
            }
            else
            {
                if(nc>0)
                {
                    sTmp+=QString::number(nc);
                    nc=0;
                }
                sTmp+=m_mpQ2Z[m_aryData[i][j]];
            }
        }
        if(nc>0)
        {
            sTmp+=QString::number(nc);
            nc=0;
        }
        str+=sTmp;
        if(i+1 != BOARD_ROW)
            str+="/";
    }
    //qDebug()<<str;
    ui->lineEdit->setText(str);
}

void Widget::on_pushButtonInput_clicked()
{
    QString str = ui->lineEdit->text();
    QStringList ary = str.split(" ");
    if(ary.length()>=3 && ary[0]=="position"&& ary[1]=="fen")
    {
        QString boardInfo = ary[2];
        int nPos = 0;
        int i = 0;

        QString aryData[BOARD_ROW*BOARD_COL];
        for(i=0;i<BOARD_ROW*BOARD_COL;i++)
        {
            aryData[i]=INVALID_CHESS;
        }

        i=0;
        while (i< boardInfo.length())
        {
            QChar c = boardInfo.at(i);
            if(c=='/')
            {
                i++;
                continue;
            }
            QString sKey = QString(c);
            if(c.isDigit())
            {
                int intValue = sKey.toInt();
                qDebug()<<intValue;
                for(int n=0;n<intValue;n++)
                {
                    aryData[nPos++]=INVALID_CHESS;
                }
            }
            else
            {

                aryData[nPos++] = m_mpZ2Q[sKey];
            }
            qDebug() << "Character at position" << nPos-1 << ":" <<aryData[nPos-1];


            qDebug() << "Character at position" << i << ":" <<c;
            i++;
        }

        nPos=0;
        for(int i=0;i<BOARD_ROW;i++)
        {
            for(int j=0;j<BOARD_COL;j++)
            {
                m_aryData[i][j]=aryData[nPos++];
            }
        }
    }
    update();
}

void  Widget::drawArrow(QPainter &painter, int startX, int startY, int endX, int endY)
{
    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
    // 计算箭头的方向和长度
    double angle = atan2(endY - startY, endX - startX);
    double arrowSize = 15.0;
    double arrowX = endX - arrowSize * cos(angle);
    double arrowY = endY - arrowSize * sin(angle);

    // 绘制箭身
    painter.drawLine(startX, startY, arrowX, arrowY);

    // 绘制箭头
    painter.drawLine( arrowX + arrowSize * cos(angle + M_PI / 6), arrowY + arrowSize * sin(angle + M_PI / 6),arrowX, arrowY);
    painter.drawLine(arrowX + arrowSize * cos(angle - M_PI / 6), arrowY + arrowSize * sin(angle - M_PI / 6),arrowX, arrowY);

}
