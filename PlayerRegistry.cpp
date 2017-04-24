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


#include "PlayerRegistry.h"
#include "jklepp_ExamplePlayer/ExamplePlayer.h"
#include "jklepp_ForcedOrGaussPlayer/ForcedOrGaussPlayer.h"

PlayerRegistry::PlayerRegistry() {
    // jklepp_ExamplePlayer
    players["jklepp_ExamplePlayer"] = new jklepp::ExamplePlayer();
    players["jklepp_ForcedOrGaussPlayer"] = new jklepp::ForcedOrGaussPlayer();
}

PlayerRegistry::~PlayerRegistry() {
    for (const auto &entry : players) {
        delete entry.second;
    }
}

void PlayerRegistry::addPlayer(const std::string& playerName, Player *player) {
    players[playerName] = player;
}

const std::map<std::string, Player *> & PlayerRegistry::getPlayers() const {
    return players;
}
