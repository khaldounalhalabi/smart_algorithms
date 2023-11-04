//
// Created by Khaldoun Alhalabi on 11/4/2023.
//

#include <queue>
#include "Board.h"

void Board::handleAttractReflection(int currentRow, int currentCol) const {
    this->handleAttractReflectionRight(currentRow, currentCol);
    this->handleAttractReflectionLeft(currentRow, currentCol);
    this->handleAttractReflectionUp(currentRow, currentCol);
    this->handleAttractReflectionDown(currentRow, currentCol);
}

void Board::handleAttractReflectionRight(int row, int column) const {
    queue<Stone> rightSide;
    for (int col = column; col < this->cols; col++) {
        if (col + 1 >= this->cols) {
            break;
        }
        Stone *nextStone = &this->board[row][col + 1];
        Board::pushAcceptableStones(rightSide, nextStone);
    }

    while (!rightSide.empty() && rightSide.front().type != OBSTACLE) {
        Stone stone = rightSide.front();
        rightSide.pop();
        auto [oldRow, oldCol] = stone.position;
        int newRow = oldRow;
        int newCol = oldCol - 1;
        if (newCol >= this->cols) {
            break;
        }
        this->movementReplacing(oldRow, oldCol, newRow, newCol);
    }
}

void Board::handleAttractReflectionLeft(int row, int column) const {
    queue<Stone> leftSide;
    for (int col = column; col >= 0; col--) {
        if (col - 1 < 0) {
            break;
        }
        Stone *nextStone = &this->board[row][col - 1];
        Board::pushAcceptableStones(leftSide, nextStone);
    }

    while (!leftSide.empty() && leftSide.front().type != OBSTACLE) {
        Stone stone = leftSide.front();
        leftSide.pop();
        auto [oldRow, oldCol] = stone.position;
        int newRow = oldRow;
        int newCol = oldCol + 1;
        if (newCol < this->cols) {
            this->movementReplacing(oldRow, oldCol, newRow, newCol);
        } else {
            break;
        }
    }
}

void Board::handleAttractReflectionUp(int row, int column) const {
    queue<Stone> upSide;
    for (int r = row; r >= 0; r--) {
        if (r - 1 < 0) {
            break;
        }
        Stone *nextStone = &this->board[r - 1][column];
        Board::pushAcceptableStones(upSide, nextStone);
    }

    while (!upSide.empty() && upSide.front().type != OBSTACLE) {
        Stone stone = upSide.front();
        upSide.pop();
        auto [oldRow, oldCol] = stone.position;
        int newRow = oldRow + 1;
        int newCol = oldCol;
        if (newRow < this->rows) {
            this->movementReplacing(oldRow, oldCol, newRow, newCol);
        } else {
            break;
        }
    }
}

void Board::handleAttractReflectionDown(int row, int column) const {
    queue<Stone> downSide;
    for (int r = row; r < this->rows; r++) {
        if (r + 1 >= this->rows) {
            break;
        }
        Stone *nextStone = &this->board[r + 1][column];
        Board::pushAcceptableStones(downSide, nextStone);
    }

    while (!downSide.empty() && downSide.front().type != OBSTACLE) {
        Stone stone = downSide.front();
        downSide.pop();
        auto [oldRow, oldCol] = stone.position;
        int newRow = oldRow - 1;
        int newCol = oldCol;
        if (newRow >= 0) {
            this->movementReplacing(oldRow, oldCol, newRow, newCol);
        } else {
            break;
        }
    }
}


void Board::pushAcceptableStones(queue<Stone> &queue, const Stone *nextStone) {
    if (nextStone->type == STONE || nextStone->type == STONEANDGOAL || nextStone->type == REPEL ||
        nextStone->type == REPELANDGOAL || nextStone->type == ATTRACT || nextStone->type == ATTRACTANDGOAL) {
        queue.push(*nextStone);
    }
}
