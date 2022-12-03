#include "OmokUI.h"
#include "filefunc.h"
#include "login.h"
#include "replay.h"

int main() {
    int play = 0;
    string user1 = "";
    string user2 = "";
    while (play != -1) {
        OmokUI *omokGame = new OmokUI();
        Login *login = new Login();
        if (omokGame->isreplay == 0) {
            login->startLogin();
            user1 = login->getUser1();
            user2 = login->getUser2();
            omokGame->setUsername(user1, user2);
        }

        userfilecreate(user1, user2);

        scoreboard(user1, user2);
        omokGame->run();

        play = omokGame->isreplay;
        int result = omokGame->getWinner();
        userfilesave(user1, user2, result);
        delete omokGame;
        delete login;
    }
    return 0;
}
