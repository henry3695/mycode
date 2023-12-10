#include "chessboard.h"

ChessBoard::ChessBoard()
{
    Reset();
}
void ChessBoard::Reset()
{
    for(int i=0;i<BOARD_ROW;i++)
    {
        for(int j=0;j<BOARD_COL;j++)
        {
            m_aryData[i][j]="0";
        }
    }

     m_aryData[0][0]=TEXT_CU("红车");
     m_aryData[0][1]=TEXT_CU("红马");
     m_aryData[0][2]=TEXT_CU("红象");
     m_aryData[0][3]=TEXT_CU("红仕");
     m_aryData[0][4]=TEXT_CU("红帅");
     m_aryData[0][5]=TEXT_CU("红仕");
     m_aryData[0][6]=TEXT_CU("红象");
     m_aryData[0][7]=TEXT_CU("红马");
     m_aryData[0][8]=TEXT_CU("红车");
}
