#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "chess.h"
#include "def.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void Reset();
    void LoadRect();
    void Rollover();
    void LoadMap();
    void  drawArrow(QPainter &painter, int startX, int startY, int endX, int endY);
private slots:
    void on_pushButtonChange_clicked();

    void on_pushButtonReset_clicked();

    void on_pushButtonOut_clicked();

    void on_pushButtonInput_clicked();

private:
    Ui::Widget *ui;
    ChessColor m_clrLocal;
    QMap<QString,Chess*> m_mapChess;
    QPixmap m_imgChessBoard;

    bool    m_bSel;
    QPair<int,int> m_selidx;
    QRect   m_aryRect[BOARD_ROW][BOARD_COL];
    QString m_aryData[BOARD_ROW][BOARD_COL];
    QMap<QString,QString> m_mpQ2Z;
    QMap<QString,QString> m_mpZ2Q;

};
#endif // WIDGET_H
