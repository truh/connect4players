/*
 * Copyright 2017 Jakob Klepp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef CONNECT4PLAYERS_PLAYER_H
#define CONNECT4PLAYERS_PLAYER_H

enum Token {
    NONE = 0,
    PLAYER1,
    PLAYER2,
};

/**
 * Represents the interface of a game board.
 */
class IBoard {
public:
    const unsigned int columns;
    const unsigned int rows;

    IBoard(unsigned int columns, unsigned int rows) : columns(columns), rows(rows) {};
    /**
     * Layout:
     * (0,5) (1,5) (2,5) (3,5) (4,5) (5,5) (6,5)
     * (0,4) (1,4) (2,4) (3,4) (4,4) (5,4) (6,4)
     * (0,3) (1,3) (2,3) (3,3) (4,3) (5,3) (6,3)
     * (0,2) (1,2) (2,2) (3,2) (4,2) (5,2) (6,2)
     * (0,1) (1,1) (2,1) (3,1) (4,1) (5,1) (6,1)
     * (0,0) (1,0) (2,0) (3,0) (4,0) (5,0) (6,0)
     *
     * @param column
     * @param row
     * @return the Token
     */
    virtual Token get(unsigned int column, unsigned int row) const = 0;
};


class Player {
public:
    /**
     * Player gets a look at the board and returns a
     * number representing a row.
     *
     * @param board Connect4Board representing the game state.
     * @return A row represented by a positive number.
     */
    virtual unsigned int doMove(const IBoard &board, Token player) = 0;
};


#endif //CONNECT4PLAYERS_PLAYER_H
