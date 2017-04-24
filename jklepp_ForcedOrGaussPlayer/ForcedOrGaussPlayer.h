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
#ifndef CONNECT4PLAYERS_JKLEPP_FORCEDORGAUSSPLAYER_H
#define CONNECT4PLAYERS_JKLEPP_FORCEDORGAUSSPLAYER_H


#include "../Player.h"
#include <string>
#include <random>

namespace jklepp {

    struct ColRow {
        unsigned int col;
        unsigned int row;
    };

    struct AreaEvaluation {
        ColRow blank;
        bool blankSet;
        unsigned int friendlyCount;
        unsigned int opponentCount;
        bool stopFlag;
    };

/**
 * An AI player looking for forced moves. When no forced move
 * is found, randomly choose a slot with bias towards the middle
 * columns.
 */
    class ForcedOrGaussPlayer : public Player {
    public:
        ForcedOrGaussPlayer();

        virtual ~ForcedOrGaussPlayer();

        unsigned int doMove(const IBoard &board, Token player) override;

    private:
        int findForcedMove(const IBoard &board, Token player);

        void countStones(const IBoard &board, Token player, Token token, unsigned int x, unsigned int y,
                         AreaEvaluation &areaEvaluation);

        AreaEvaluation countStonesUp(const IBoard &board, Token player, unsigned int x, unsigned int y);

        AreaEvaluation countStonesRight(const IBoard &board, Token player, unsigned int x, unsigned int y);

        AreaEvaluation countStonesUpRight(const IBoard &board, Token player, unsigned int x, unsigned int y);

        AreaEvaluation countStonesDownRight(const IBoard &board, Token player, unsigned int x, unsigned int y);

        unsigned int backupStrategy(const IBoard &board, Token player);
    };
}

#endif //CONNECT4PLAYERS_JKLEPP_FORCEDORGAUSSPLAYER_H
