#include "chessgame.h"
#include "rulemanager.h"
#include <QMessageBox>

ChessGame::ChessGame(bool onePlayer,bool LAN, QObject *parent) : QObject(parent)
{
    board = new ChessBoard();
    setupPieces();
    this->onePlayer = onePlayer;
    this->LAN = LAN;
    select = {-1, -1};
    whitesTurn = true;
    canCastle[0] = true;
    canCastle[1] = true;
    cm = new CheckManager(board);
    inGame = true;
    aiTurn = false;
    if(onePlayer)
    {
        api = new Api();
        if(!api->setupOnePlayer()){
            QMessageBox msgBox;
            msgBox.setText("ERROR: Database not initalized");
            msgBox.exec();
        }
    }
    connect(board->getScene(),
            (&MyGraphicsScene::userClick),
            this,
            (&ChessGame::userClickedSquare));
    connect(cm->getRm(),
            (&RuleManager::promotePawn),
            this,
            (&ChessGame::promotePawn));
}

void ChessGame::setNetworking(Networking *n)
{
    this->n = n;
    if(n->isServer){
        canMove = true;
        connect(n->getServer(), SIGNAL(dataReceived(QByteArray)), this, SLOT(receive(QByteArray)));
    } else {
        canMove = false;
        connect(n->getClient(), SIGNAL(dataReceived(QByteArray)), this, SLOT(receive(QByteArray)));
    }
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
    if ((piece == nullptr && (select == (Pos){-1, -1})) || (select == pos) || !inGame || (LAN &!canMove))
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
                emit pieceTaken(enemy);
                delete enemy;
                state[pos.x][pos.y] = nullptr;
            }
        }

        if(canCastle[whitesTurn])
            if (state[select.x][select.y]->getType() == "king")
            {
                checkCastle(state[select.x][select.y], pos);
                canCastle[whitesTurn] = false;
                cm->getRm()->canCastle[whitesTurn] = false;
            }

        piece = state[select.x][select.y];

        piece->setPos(pos);
        state[pos.x][pos.y] = state[select.x][select.y];

        state[select.x][select.y] = nullptr;
        emit turnChange(getMoveNotation(select, pos), whitesTurn);

        if (onePlayer){
            afterMoveForAI(select, pos);
        }
        if(LAN){
            afterMoveForLAN(select, pos);
            changeSides();
        }

        select = {-1, -1};

        if (cm->checkCheckMate(state, !whitesTurn))
        {
            emit gameFinished("Checkmate", whitesTurn);
            inGame = false;
            return;
        }

        whitesTurn = !whitesTurn;

    }
}

void ChessGame::promotePawn(Pos pos)
{
    // Ask user for queen or knight
    if (pos.x == 0)
    {
        const QString piece = "w_queen";
        QGraphicsPixmapItem *png = board->putPieceAt(piece, pos);
        state[pos.x][pos.y] = new Piece("queen", pos, true, png);
    }
    if (pos.x == 7)
    {
        const QString piece = "b_queen";
        QGraphicsPixmapItem *png = board->putPieceAt(piece, pos);
        state[pos.x][pos.y] = new Piece("queen", pos, false, png);
    }
}

void ChessGame::receive(QByteArray data)
{
    Move m = stringToMove(data);

    Pos pos = m.to;
    Piece *piece = state[m.from.x][m.from.y];

    Piece *enemy = state[pos.x][pos.y];
    if (enemy != nullptr)
    {
        if (enemy->getColor() == whitesTurn)
        {
            return;
        }
        else
        {
            emit pieceTaken(enemy);
            delete enemy;
            state[pos.x][pos.y] = nullptr;
        }
    }

    if(canCastle[whitesTurn])
        if (state[m.from.x][m.from.y]->getType() == "king")
        {
            checkCastle(state[m.from.x][m.from.y], pos);
            canCastle[whitesTurn] = false;
            cm->getRm()->canCastle[whitesTurn] = false;
        }

    piece->setPos(pos);
    state[pos.x][pos.y] = state[m.from.x][m.from.y];
    state[m.from.x][m.from.y] = nullptr;
    emit turnChange(getMoveNotation(m.from, pos), whitesTurn);

    if (cm->checkCheckMate(state, !whitesTurn))
    {
        emit gameFinished("Checkmate", whitesTurn);
        inGame = false;
        return;
    }
    whitesTurn = !whitesTurn;
    canMove = true;
}

void ChessGame::checkCastle(Piece *king, Pos to)
{
    int x = king->getColor() ? 7 : 0;
    if (king->getPos() == (Pos){x, 4} && to == (Pos){x, 2})
    {
        state[x][0]->setPos({x, 3});
        state[x][3] = state[x][0];
        state[x][0] = nullptr;
    }
    if (king->getPos() == (Pos){x, 4} && to == (Pos){x, 6})
    {
        state[x][7]->setPos({x, 5});
        state[x][5] = state[x][7];
        state[x][7] = nullptr;
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

void ChessGame::afterMoveForAI(Pos from, Pos to)
{
    if(!aiTurn)
    {
        // AI stuff here
        Move move;
        move.from = from;
        move.to = to;
        api->tryMakeMove(move);
        Move aiMove = api->aiMove();
        aiTurn = true;

        Piece *enemy = state[aiMove.to.x][aiMove.to.y];
        if (enemy != nullptr)
        {
            if (enemy->getColor() == !whitesTurn)
            {
                return;
            }
            else
            {

                emit pieceTaken(enemy);
                delete enemy;
                state[aiMove.to.x][aiMove.to.x] = nullptr;
            }
        }

        Piece *piece = state[aiMove.from.x][aiMove.from.y];
        if(piece == nullptr)
        {
            qInfo()<<"ERROR from: "<< aiMove.from.toString() << " to: " <<aiMove.to.toString();
            // Retry move?
            return;
        }
        piece->setPos(aiMove.to);
        state[aiMove.to.x][aiMove.to.y] = state[aiMove.from.x][aiMove.from.y];
        state[aiMove.from.x][aiMove.from.y] = nullptr;
        whitesTurn = !whitesTurn;
        emit turnChange(getMoveNotation(aiMove.from, aiMove.to), whitesTurn);
        aiTurn = false;
    }
}

void ChessGame::afterMoveForLAN(Pos from, Pos to)
{
    canMove = false;
    QString msg = posToString(from) + posToString(to);
    if(n->isServer){
        n->serverSend(msg);
    } else {
        n->clientSend(msg);
    }
}

QString ChessGame::getMoveNotation(Pos from, Pos to)
{
    Piece* p = state[to.x][to.y];
    // Check for castle
//    if(state[from.x][from.y]->getType() == "king")
    QString res = to.toString();

    const QString abr[6] = {"", "R", "B", "N", "Q", "K"};
    for(int i=0; i<6;i++)
    {
        if(p->getType() == piecesNames[i])
        {
            res = abr[i] + res;
            return res;
        }
    }
    return "none";
}

void ChessGame::changeSides()
{
    for(int i=0;i<8;i++){
//        Piece *t[8] = state[4-i]
//        state[i]
    }
}

Move ChessGame::stringToMove(QString str)
{
    Move m = Move{Pos{-str[1].toLatin1()+56, str[0].toLatin1()-65}, Pos{-str[3].toLatin1()+56, str[2].toLatin1()-65}};
    return m;
}

QString ChessGame::posToString(Pos p)
{
    QString s = QString(char(p.y+65)) + QString(char(56-p.x));
    return s;
}



