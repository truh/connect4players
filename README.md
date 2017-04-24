# Connect 4 Players

[![Build Status](https://ci.truh.in/job/GPR2_Exercise03_connect4players/badge/icon)](https://ci.truh.in/job/GPR2_Exercise03_connect4players/)

## Add a new player

Create folder for your player, the folder name should be as follows:

    <first letter of first name><last name>_<name of the player>
    
Put the source and header file of your player class into that folder.
To avoid conflicts, wrap your class header in a namespace name as follows:

    <first letter of first name><last name>

The resulting files might look like this:

* ``jklepp_ExamplePlayer/ExamplePlayer.h``

``` c++
#include "../Player.h"

namespace jklepp {
    // since this is within your namespace, you can define your
    // own helper function without risking conflicts
    bool isColumnFree(const IBoard &board, unsigned int column);

    // make sure to use public inheritance
    class ExamplePlayer : public Player {
    public:
        ExamplePlayer();
        virtual ~ExamplePlayer();
        virtual unsigned int doMove(const IBoard &board, Token player) override;
    };

}
```

* ``jklepp_ExamplePlayer/ExamplePlayer.cpp``

``` c++
#include "ExamplePlayer.h"

bool jklepp::isColumnFree(const IBoard &board, unsigned int column) {
    return Token::NONE == board.get(column, board.rows - 1);
}

jklepp::ExamplePlayer::ExamplePlayer() {}
jklepp::ExamplePlayer::~ExamplePlayer() {}

unsigned int jklepp::ExamplePlayer::doMove(const IBoard &board, Token player) {
    for (unsigned int i = 0; i < board.columns; ++i) {
        if (jklepp::isColumnFree(board, i)) {
            return i;
        }
    }
    return board.columns;
}
```
    
Register your player in the player registry (PlayerRegistry.cpp):

``` c++
    /* ... */
    PlayerRegistry::PlayerRegistry() {
        /* ... */
        players["jklepp_ExamplePlayer"] = new jklepp::ExamplePlayer();
        /* ... */
    }
    /* ... */
```

Add your headers and sources to the CMakeLists.txt

``` cmake
# ...
set(jklepp_ExamplePlayer jklepp_ExamplePlayer/ExamplePlayer.h jklepp_ExamplePlayer/ExamplePlayer.cpp)

add_library(connect4players STATIC
        Player.h PlayerRegistry.cpp PlayerRegistry.h
        # ...
        ${jklepp_ExamplePlayer}
)
```
