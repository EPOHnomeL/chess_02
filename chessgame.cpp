#include "chessgame.h"
#include <QDebug>

ChessGame::ChessGame(QObject *parent) : QObject(parent)
{
    board = new ChessBoard();
    setupPieces();
    select = {-1, -1};
    whitesTurn = true;
    qInfo() << "White's turn";
    connect(board->getScene(),
            (&MyGraphicsScene::userClick),
            this,
            (&ChessGame::userClickedSquare));
}

ChessBoard *ChessGame::getBoard() const
{
    return board;
}

void ChessGame::userClickedSquare(Pos pos)
{
    // If there are no pieces on the square or nothing selected or the same thing selected or other player's piece
    Piece *piece = state[pos.x][pos.y];

    if ((piece == nullptr && (select.x == -1 && select.y == -1)) || (select.x == pos.x && select.y == pos.y))
    {
        return;
    }
    // If something is selected
    if (select.x == -1 && select.y == -1)
    {
        if (piece->getColor() != whitesTurn)
            return;
        select = pos;
        qInfo() << "selected " << piece->getType() << "at x: " << pos.x << " y: " << pos.y;
        // toggle active square;
        // get list of valid moves
        // show valid moves tiles
    }
    else // If something is placed
    {
        // check if in list of valid moves
        // clear valid moves tiles
        // move piece
        qInfo() << "to x: " << pos.x << " y: " << pos.y;
        select = {-1, -1};
        whitesTurn = !whitesTurn;
        qInfo() << (whitesTurn ? "White's turn" : "Black's turn");
    }
}

void ChessGame::setupPieces()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i < 2)
            {
                const QString piece = "b_" + b_starting[i][j];
                QGraphicsPixmapItem *png = board->putPieceAt(piece, {i, j});
                state[i][j] = new Piece(b_starting[i][j], {i, j}, false, png);
            }
            if (i >= 2 && i <= 5)
                state[i][j] = nullptr;
            if (i > 5)
            {
                const QString piece = "w_" + w_starting[i - 6][j];
                QGraphicsPixmapItem *png = board->putPieceAt(piece, {i, j});
                state[i][j] = new Piece(w_starting[i - 6][j], {i, j}, true, png);
            }
        }
    }
}
