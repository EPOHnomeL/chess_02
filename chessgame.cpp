#include "chessgame.h"

ChessGame::ChessGame(QObject *parent) : QObject(parent)
{
    board = new ChessBoard();
    setupPieces();
}

ChessBoard *ChessGame::getBoard() const
{
    return board;
}

void ChessGame::userClickedSquare()
{

}

void ChessGame::setupPieces()
{
    for(int i=0; i<8; i++){
        for(int j=0;j<8;j++){
            if(i<2){
                const QString piece = "b_" + b_starting[i][j];
                QGraphicsPixmapItem *png = board->putPieceAt(piece, {i, j});
                state[i][j] = new Piece(b_starting[i][j], {i, j}, false, png);
            }
            if(i>=2 && i<=5)
                state[i][j] = nullptr;
            if(i>5){
                const QString piece = "w_" + w_starting[i-6][j];
                QGraphicsPixmapItem *png = board->putPieceAt(piece, {i, j});
                state[i][j] = new Piece(w_starting[i-6][j], {i, j}, false, png);
            }
        }
    }
}
