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
//#include <JkLog.h>
#include "ForcedOrGaussPlayer.h"

using namespace jklepp;

ForcedOrGaussPlayer::ForcedOrGaussPlayer() {}

ForcedOrGaussPlayer::~ForcedOrGaussPlayer() {}

unsigned int ForcedOrGaussPlayer::doMove(const IBoard &board, Token player) {
    int forcedMove = findForcedMove(board, player);
    if (forcedMove >= 0 &&
        forcedMove < board.rows &&
        Token::NONE == board.get((unsigned int) forcedMove, board.rows - 1)) {
        return (unsigned int) forcedMove;
    }
    return backupStrategy(board, player);
}

int ForcedOrGaussPlayer::findForcedMove(const IBoard &board, Token player) {
    int column = -1;
    for (unsigned int x = 0; x < board.columns; ++x) {
        for (unsigned int y = 0; y < board.rows; ++y) {
            AreaEvaluation areaEvaluation;
            areaEvaluation = countStonesUp(board, player, x, y);
            if (areaEvaluation.blankSet && NONE == board.get(areaEvaluation.blank.col, board.rows -1)) {
                if (areaEvaluation.friendlyCount >= 3) {
                    //Debug("[Up] Found forced move (chance): " + to_string(areaEvaluation.blank.col + 1));
                    return areaEvaluation.blank.col;
                }
                if (areaEvaluation.opponentCount >= 3) {
                    column = areaEvaluation.blank.col;
                }
            }
            areaEvaluation = countStonesRight(board, player, x, y);
            if (areaEvaluation.blankSet && NONE == board.get(areaEvaluation.blank.col, board.rows -1)) {
                if (areaEvaluation.friendlyCount >= 3) {
                    //Debug("[Right] Found forced move (chance): " + to_string(areaEvaluation.blank.col + 1));
                    return areaEvaluation.blank.col;
                }
                if (areaEvaluation.opponentCount >= 3) {
                    column = areaEvaluation.blank.col;
                }
            }
            areaEvaluation = countStonesUpRight(board, player, x, y);
            if (areaEvaluation.blankSet && NONE == board.get(areaEvaluation.blank.col, board.rows -1)) {
                if (areaEvaluation.friendlyCount >= 3) {
                    //Debug("[UpRight] Found forced move (chance): " + to_string(areaEvaluation.blank.col + 1));
                    return areaEvaluation.blank.col;
                }
                if (areaEvaluation.opponentCount >= 3) {
                    column = areaEvaluation.blank.col;
                }
            }
            areaEvaluation = countStonesDownRight(board, player, x, y);
            if (areaEvaluation.blankSet && NONE == board.get(areaEvaluation.blank.col, board.rows -1)) {
                if (areaEvaluation.friendlyCount >= 3) {
                    //Debug("[DownRight] Found forced move (chance): " + to_string(areaEvaluation.blank.col + 1));
                    return areaEvaluation.blank.col;
                }
                if (areaEvaluation.opponentCount >= 3) {
                    column = areaEvaluation.blank.col;
                }
            }
        }
    }
    //if (column != -1) Debug("Found forced move (danger): " + to_string(column + 1));
    return column;
}

unsigned int ForcedOrGaussPlayer::backupStrategy(const IBoard &board, Token player) {
    double mean = (board.columns + 1) / 2.0;
    double deviation = mean / 2;
    std::normal_distribution<double> dist(mean, deviation);
    std::random_device rd;
    std::mt19937 e2(rd());

    unsigned int column = board.columns;
    while (0 > column || board.columns <= column || NONE != board.get(column, board.rows - 1)) {
        int rng = (int) std::round(dist(e2)) - 1;
        if (rng >= 0) {
            column = (unsigned int) rng;
        }
    }
    return column;
}

void ForcedOrGaussPlayer::countStones(
        const IBoard &board, Token player, Token token,
        unsigned int x, unsigned int y,
        AreaEvaluation &areaEvaluation) {
    if (NONE == token) {
        if (areaEvaluation.blankSet) {
            areaEvaluation.stopFlag = true;
        } else {
            areaEvaluation.blank = {x,y};
            areaEvaluation.blankSet = true;
        }
    } else if (player == token) {
        if (areaEvaluation.opponentCount > 0) {
            areaEvaluation.stopFlag = true;
        } else {
            areaEvaluation.friendlyCount++;
        }
    } else if (player != token) {
        if (areaEvaluation.friendlyCount > 0) {
            areaEvaluation.stopFlag = false;
        } else {
            areaEvaluation.opponentCount++;
        }
    }
}

AreaEvaluation ForcedOrGaussPlayer::countStonesUp(
        const IBoard &board, Token player, unsigned int x, unsigned int y) {
    AreaEvaluation areaEvaluation = {
            {},
            false,
            0, 0,
            false
    };
    if (y + 4 <= board.rows) {
        for (int i = 0; i < 4; ++i) {
            Token token = board.get(x, y + i);
            countStones(board, player, token, x, y + i, areaEvaluation);
            if (areaEvaluation.stopFlag) {
                break;
            }
        }
    }
    return areaEvaluation;
}

AreaEvaluation ForcedOrGaussPlayer::countStonesRight(
        const IBoard &board, Token player, unsigned int x, unsigned int y) {
    AreaEvaluation areaEvaluation = {
            {},
            false,
            0, 0,
            false
    };
    if (x + 4 <= board.columns) {
        for (int i = 0; i < 4; ++i) {
            Token token = board.get(x + i, y);
            countStones(board, player, token, x + i, y, areaEvaluation);
            if (areaEvaluation.stopFlag) {
                break;
            }
        }
    }
    return areaEvaluation;
}

AreaEvaluation ForcedOrGaussPlayer::countStonesUpRight(
        const IBoard &board, Token player, unsigned int x, unsigned int y) {
    AreaEvaluation areaEvaluation = {
            {},
            false,
            0, 0,
            false
    };
    if (x + 4 <= board.columns && y + 4 <= board.rows) {
        for (int i = 0; i < 4; ++i) {
            Token token = board.get(x + i, y + i);
            countStones(board, player, token, x + i, y + i, areaEvaluation);
            if (areaEvaluation.stopFlag) {
                break;
            }
        }
    }
    return areaEvaluation;
}

AreaEvaluation ForcedOrGaussPlayer::countStonesDownRight(
        const IBoard &board, Token player, unsigned int x, unsigned int y) {
    AreaEvaluation areaEvaluation = {
            {},
            false,
            0, 0,
            false
    };
    if (x + 4 <= board.columns && y + 1 >= 4)
    for (int i = 0; i < 4; ++i) {
        Token token = board.get(x + i, y - i);
        countStones(board, player, token, x + i, y - i, areaEvaluation);
        if (areaEvaluation.stopFlag) {
            break;
        }
    }
    return areaEvaluation;
}
