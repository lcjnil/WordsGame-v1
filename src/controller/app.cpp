#include "app.h"
#include "../utils/Console.h"
#include "../model/User.h"
#include "../model/Player.h"
#include "../model/Referee.h"

#include <QDebug>
#include <QString>

using namespace Console;

void App::start() {
    cls();
    //TODO: made it more fancy
    print("Welcome To Words Game\n\n", RED);

    bool quit = false;

    while(true) {
        cls();

        printCenter("Words Game By LCJ", 1, BLUE);
        print("Please select your ", 4, 4);
        print("ACTION: ", RED);

        print("1. Register", 4, 5);
        print("2. Login", 4, 6);
        print("Q. Quit", 4, 7);

        locateCursor(4, 8);

        switch (getch()) {
            case '1':
                registerController();
                break;
            case '2':
                loginController();
                break;
            case 'q':
                quit = true;
                break;
            default:
                start();
        }

        if (quit) {
            break;
        }
    }


}

void App::registerController() {
    cls();
    printCenter("Register", 2, RED);
    QString username, password, type;


    print("Username: ", 4, 4);
    scin>>username;

    print("Password:  ", 4, 6);
    password = getPassword();

    print("Are you ", 4, 8);print("1. Player ", BLUE);print("2. Referee :", RED);

    switch (getch()) {
        case '1':
            type = "player";
            break;
        case '2':
        default:
            type = "referee";
            break;
    }

    User * user;
    if (User::reg(username, password, type)) {
        cls();
        printCenter("Register Success", 12, GREEN);
        waitKey();
    } else {
        cls();
        printCenter("Register Failed", 12, RED);
        waitKey();
        registerController();
    }
}

void App::loginController() {
    cls();

    printCenter("Login", 2, RED);

    QString username, password, type;
    print("Username: ", 4, 4);
    scin>>username;

    print("Password:  ", 4, 6);
    password = getPassword();

    type = User::auth(username, password);
    User * user;
    if (type == "player") {
        user = new Player();
        *user = Player::findByName(username);
        player =  dynamic_cast<Player *>(user);

        playerController();
    } else if (type == "referee") {
        user = new Referee();
        *user = Player::findByName(username);
        referee = dynamic_cast<Referee *>(user);

        refereeController();
    } else {
        cls();
        printCenter("Error: Cannot recognize user", 12, RED);
        waitKey();
    }
}

void App::refereeController() {
    cls();
    print("Refree: ", 4, 0); print(referee->getName(), GREEN);

    print("Please select your ", 4, 4);
    print("ACTION: ", RED);

    print("1. Add a word", 4, 5);
    print("2. List all my words", 4, 6);
    print("3. View all referee", 4, 7);
    print("Q. Quit", 4, 8);


    switch (getch()) {
        case '1':
            addWordController();
            break;
        case '2':
            listWordController();
            break;
        case '3':
            board->showReferee();
            refereeController();
            break;
        case 'q':
            break;
        default:
            refereeController();
    }
}

void App::addWordController() {
    QString word; int level;

    cls();
    print("Word: ", 4, 4); scin>>word;
    print("Level: ", 4, 6); scin>>level;

    referee->addQuestion(word, level);

    print("Please select your ", 4, 4);
    print("ACTION: ", RED);
    print("1. Add a word again", 4, 5);
    print("Q. Quit", 4, 6);

    switch (getch()) {
        case '1':
            addWordController();
            break;
        case 'q':
        default:
            refereeController();
            break;
    }
}

//TODO: beautifier
void App::listWordController() {
    cls();

    vector<Question> questions = Question::findQuestionByUser(referee->getId());

    for (auto question: questions) {
        print(question.get("word") + "\n");
    }

    waitKey();
    
}

void App::playerController() {
    cls();
    print("Player: ", 4, 0); print(player->getName(), GREEN);

    print("Please select your ", 4, 4);
    print("ACTION: ", RED);

    print("1. Play GAME!!!", 4, 5, RED);
    print("2. View All Players", 4, 6, RED);
    print("Q. Quit", 4, 7);


    switch (getch()) {
        case '1':
            game = new Game(player);
            game->start();
            playerController();
            break;
        case '2':
            board->showPlayer();
            playerController();
            break;
        case 'q':
            break;
        default:
            playerController();
    }
}
