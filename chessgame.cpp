#include "chessgame.h"
#include "rulemanager.h"
#include <QDebug>

ChessGame::ChessGame(QObject *parent) : QObject(parent)
{
    board = new ChessBoard();
    setupPieces();
    select = {-1, -1};
    whitesTurn = true;
    cm = new CheckManager(board);
    qInfo() << "White's turn";
    inGame = true;
    connect(board->getScene(),
            (&MyGraphicsScene::userClick),
            this,
            (&ChessGame::userClickedSquare));
    connect(cm->getRm(),
            (&RuleManager::promotePawn),
            this,
            (&ChessGame::promotePawn));
}

ChessBoard *ChessGame::getBoard() const
{
    return board;
}

void ChessGame::userClickedSquare(Pos pos)
{
    // If there are no pieces on the square or nothing selected or the same thing selected or other player's piece
    Piece *piece = state[pos.x][pos.y];

//    qInfo()<< "selected x: "<< pos.x<<"  y: "<<pos.y;
    if ((piece == nullptr && (select == (Pos){-1, -1})) || (select == pos) || !inGame)
    {
        return;
    }

    // If something is selected
    if (select == (Pos){-1, -1})
    {
        if (piece->getColor() != whitesTurn)
            return;

        validMoves = cm->getValidMoves(state, piece);

        if (validMoves == nullptr || validMoves->size() == 0)
            return;
        select = pos;
        board->toggleSquare(pos, true);
        for (int i = 0; i < validMoves->size(); i++)
            board->toggleSquare(validMoves->at(i), false);
    }
    else
    {
        board->toggleSquare(select, true);
        for (int i = 0; i < validMoves->size(); i++)
            board->toggleSquare(validMoves->at(i), false);

        if (validMoves->indexOf(pos) == -1)
        {
            select = {-1, -1};
            return;
        }

        Piece *enemy = state[pos.x][pos.y];
        if (enemy != nullptr)
        {
            if (enemy->getColor() == whitesTurn)
            {
                return;
            }
            else
            {
                delete enemy;
                state[pos.x][pos.y] = nullptr;
            }
        }

        piece = state[select.x][select.y];
        piece->setPos(pos);
        state[pos.x][pos.y] = state[select.x][select.y];
        state[select.x][select.y] = nullptr;
        select = {-1, -1};

        if (cm->checkCheckMate(state, !whitesTurn))
        {
            qInfo() << (whitesTurn ? "======= White won!!" : "======= Black won!!");
            inGame = false;
            return;
        }

        whitesTurn = !whitesTurn;
        qInfo() << (whitesTurn ? "White's turn" : "Black's turn");
    }
}

void ChessGame::promotePawn(Pos pos)
{
    // Ask user for queen or knight
     if(pos.x == 0){
         const QString piece = "w_queen";
         QGraphicsPixmapItem *png = board->putPieceAt(piece, pos);
         state[pos.x][pos.y] = new Piece("queen", pos, true, png);
     }
     if(pos.x == 7){
         const QString piece = "b_queen";
         QGraphicsPixmapItem *png = board->putPieceAt(piece, pos);
         state[pos.x][pos.y] = new Piece("queen", pos, false, png);
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
