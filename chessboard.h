#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "def.h"
class ChessBoard
{
public:
    ChessBoard();

    void Reset();
private:
    QString m_aryData[BOARD_ROW][BOARD_COL];
};

#endif // CHESSBOARD_H
