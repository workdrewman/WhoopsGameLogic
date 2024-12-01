#include "../../include/game_logic/logic_controller.hpp"

#include <vector> // for std::vector
#include <iostream> // for std::cout and std::endl

using namespace std;

namespace logic_controller
{
    const int MAX_PLAYERS = 4;
    const int PIECES_PER_PLAYER = 3;
    const int MAX_PIECES = MAX_PLAYERS * PIECES_PER_PLAYER;
    const int BOARD_SIZE = 80;

    int currentPlayer;
    int playerCount;
    //No card yet: -1, Whoops!: 0, Other cards: 1-12
    int lastCard = -1;
    //Yellow: 1, Green: 2, Red: 3, Blue: 4
    int player1Color = 0;
    int player2Color = 0;
    int player3Color = 0;
    int player4Color = 0;

    //Locations
    //Map
    // 0-43: Around the board starting from Yellow
    // 44-46: Yellow's Home
    // 47-49: Yellow's Safety Zone
    // 50-52: Yellow's Start
    // 53-55: Green's Home
    // 56-58: Green's Safety Zone
    // 59-61: Green's Start
    // 62-64: Red's Home
    // 65-67: Red's Safety Zone
    // 68-70: Red's Start
    // 71-73: Blue's Home
    // 74-76: Blue's Safety Zone
    // 77-79: Blue's Start
    vector<int> currentLocations(BOARD_SIZE);
    vector<int> lastLocations(BOARD_SIZE);
    int movingFrom;
    int leftOverSpaces; //For sevens

    //Function declarations
    void startGame();
    void getPlayerCount();
    void takeTurn();
    void nextPlayer();
    int waitForCard();
    bool checkWin();
    int getPlayerColor();
    void setPlayerColor();
    vector<int> findPossibleMoves(int location, int distance);
    int findNextOpenHome(int color);
    void saveCurrentLocations(std::vector<int> locations);
    void saveLastLocations(std::vector<int> locations);
    bool allPiecesPlaced();
    bool allPiecesOnStart();
    int t_GetCard();
    int t_setStartAreas();
    void t_displayCardInstructions();
    void t_whereAreMyPieces();
    void t_selectPiece();

    void startGame() {
        cout << "Setup Complete" << endl;
        cout << "Press any key to start game" << endl;
        cin.get();
        cout << "Game Started" << endl;
        currentPlayer = 0;
        getPlayerCount();
        cout << "Player count: " << playerCount << endl << endl;

        //code to ensure setup is done correctly
        cout << "Please place pieces on start locations" << endl;
        while (!allPiecesOnStart()) {};

        takeTurn();
    }

    void getPlayerCount() {
        //Scan card to get player count
        cout << "Get number of players: " << endl;
        //Audio
        lastCard = waitForCard();
        while (lastCard < 2 || lastCard > 4) {
            //ERROR
            cout << "Invalid number of players" << endl;
            //Audio
            //Scan card to get player count
            lastCard = waitForCard();
        }
        playerCount = lastCard;
        lastCard = -1;
    }

    void takeTurn() {
        cout << "Player " << currentPlayer + 1 << "'s turn" << endl << endl;
        //Scan card
        cout << "Draw and scan a card" << endl;
        lastCard = waitForCard();
        t_displayCardInstructions();

        //Display pieces
        t_whereAreMyPieces();

        //Pick up a piece
        t_selectPiece();

        //Light leds of possible moves
        vector<int> possibleMoves = findPossibleMoves(movingFrom, lastCard);
        cout << "Possible moves: ";
        for (int i = 0; i < possibleMoves.size(); i++) {
            cout << possibleMoves[i] << " ";
        }
        cout << endl;

        //If piece returned to spot do again

        //If piece hits other piece, send other piece back to start

        //Slide if on slide square

        //Save places
        
        if (checkWin()) {
            cout << "Player " << currentPlayer + 1 << " wins!" << endl;
        } else {
            nextPlayer();
            takeTurn();
        }
    }

    //Next player, 4 players in total
    void nextPlayer() {
        currentPlayer = (currentPlayer + 1) % playerCount;
    } 

    //Wait for a card to be scanned
    int waitForCard() {
        //Add physical card scanning later
        int card = t_GetCard();

        //check if card is valid
        while ((card < 0 || card > 12) || card == 6 || card == 9) {
            //ERROR
            cout << "Invalid card" << endl;
            card = t_GetCard();
        }
        return card;
    }

    bool checkWin() {
        int color = getPlayerColor();

        //Check if all pieces are in home
        switch (color) {
            //Yellow
            case 1:
                for (int i = 44; i < 47; i++) {
                    if (currentLocations[i] != 1) {
                        return false;
                    }
                }
                break;
            //Green
            case 2:
                for (int i = 53; i < 56; i++) {
                    if (currentLocations[i] != 2) {
                        return false;
                    }
                }
                break;
            //Red
            case 3:
                for (int i = 62; i < 65; i++) {
                    if (currentLocations[i] != 3) {
                        return false;
                    }
                }
                break;
            //Blue
            case 4:
                for (int i = 71; i < 74; i++) {
                    if (currentLocations[i] != 4) {
                        return false;
                    }
                }
                break;
        }
        return true;
    }

    int getPlayerColor() {
        switch (currentPlayer) {
            case 0:
                return player1Color;
            case 1:
                return player2Color;
            case 2:
                return player3Color;
            case 3:
                return player4Color;
            default:
                return 0;
        }
    }
    
    //POSSIBLE BUG: if player picks up a piece that already has a color
    void setPlayerColor() {
        int movingColor;
        if (movingFrom >= 50 && movingFrom <= 52) {
            movingColor = 1;    //Yellow
        } else if (movingFrom >= 59 && movingFrom <= 61) {
            movingColor = 2;    //Green
        } else if (movingFrom >= 68 && movingFrom <= 70) {
            movingColor = 3;    //Red
        } else if (movingFrom >= 77 && movingFrom <= 79) {
            movingColor = 4;    //Blue
        }

        switch (currentPlayer) {
            case 0:
                player1Color = movingColor;
                break;
            case 1:
                player2Color = movingColor;
                break;
            case 2:
                player3Color = movingColor;
                break;
            case 3:
                player4Color = movingColor;
                break;
        }
    }

    vector<int> findPossibleMoves(int selectedPawn, int distance) {
        vector<int> possibleMoves;
        int color = getPlayerColor();
        switch (distance) {
            case 0: //Whoops!
                for (int i = 0; i < BOARD_SIZE; i++) {
                    if(currentLocations[i] != color && currentLocations[i] != 0) {
                        
                    }
                }
                break;
            case 1:
                if (selectedPawn >= (50 + (9*(color-1))) && selectedPawn <= 52 + (9*(color-1))) {   //If pawn is in start
                    possibleMoves.push_back(3 + (11*(color-1)));
                } 
                else if (selectedPawn == (1 + (11*(color-1)))) {  //If pawn can move to safety zone
                    possibleMoves.push_back(49 + (9*(color-1)));
                }
                else if ((selectedPawn == (48 + 9*(color - 1))) || (selectedPawn == (49 + 9*(color - 1)))) {    //Pawn is in safety zone
                    possibleMoves.push_back(selectedPawn - 1);
                }
                else if (selectedPawn == (47 + 9*(color-1))) {    //Pawn can move to home
                    possibleMoves.push_back(findNextOpenHome(color));
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else {  //Otherwise move 1 space forwards
                    possibleMoves.push_back((selectedPawn + 1)%44);
                }
                break;
            case 2:
                if (selectedPawn >= (50 + (9*(color-1))) && selectedPawn <= 52 + (9*(color-1))) {   //If pawn is in start
                    possibleMoves.push_back(4 + (11*(color-1)));
                } 
                else if (selectedPawn == (1 + (11*(color-1)))) {  //If pawn is one away from safety zone
                    possibleMoves.push_back(48 + (9*(color-1)));
                }
                else if (selectedPawn == (0 + (11*(color-1)))) {  //If pawn is two away from safety zone
                    possibleMoves.push_back(49 + (9*(color-1)));
                }
                else if (selectedPawn == (49 + 9*(color-1))) {    //Pawn is in safety zone
                    possibleMoves.push_back(selectedPawn - 2);
                }
                else if (selectedPawn == (48 + 9*(color-1))) {    //Pawn can move to home
                    possibleMoves.push_back(findNextOpenHome(color));
                }
                else if (selectedPawn == (47 + 9*(color-1))) {    //Pawn too close to home
                    break;
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else {  //Otherwise move 2 spaces forwards
                    possibleMoves.push_back((selectedPawn + 2)%44);
                }
                break;
            case 3:
                if (selectedPawn == (1 + (11*(color-1)))) {  //If pawn is one away from safety zone
                    possibleMoves.push_back(47 + (9*(color-1)));
                }
                else if (selectedPawn == (0 + (11*(color-1)))) {  //If pawn is two away from safety zone
                    possibleMoves.push_back(48 + (9*(color-1)));
                }
                else if (selectedPawn == ((43 + (11*(color-1)))%44)) {  //If pawn is three away from safety zone
                    possibleMoves.push_back(49 + (9*(color-1)));
                }
                else if (selectedPawn == (49 + 9*(color-1))) {    //Pawn can move to home
                    possibleMoves.push_back(findNextOpenHome(color));
                }
                else if ((selectedPawn >= (47 + 9*(color-1))) && (selectedPawn <= (48 + 9*(color-1)))) {    //Pawn too close to home
                    break;
                }
                else if ((selectedPawn >= (50 + 9*(color-1))) && (selectedPawn <= (52 + 9*(color-1)))) {    //Pawn can't move in start
                    break;
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else {  //Otherwise move 3 spaces forwards
                    possibleMoves.push_back((selectedPawn + 3)%44);
                }
                break;
            case 4:
                if (selectedPawn == (47 + (9*(color-1)))) {  //If pawn is in safety zone near home
                    possibleMoves.push_back(0 + (11*(color-1)));
                }
                else if (selectedPawn == (48 + (9*(color-1)))) {  //If pawn is in saftey zone middle
                    possibleMoves.push_back((43 + (11*(color-1)))%44);
                }
                else if (selectedPawn == (49 + (9*(color-1)))) {  //If pawn is in safety zone near exit
                    possibleMoves.push_back((42 + (11*(color-1)))%44);
                }
                else if ((selectedPawn >= (50 + 9*(color-1))) && (selectedPawn <= (52 + 9*(color-1)))) {    //Pawn can't move in start
                    break;
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else {  //Otherwise move 4 spaces backwards
                    int newLocation = selectedPawn - 4;
                    if (newLocation < 0) {
                        newLocation += 44;
                    }
                    possibleMoves.push_back(newLocation);
                }
                break;
            case 5:
                if (selectedPawn == ((43 + (11*(color-1))))%44) {  //If pawn is three away from safety zone
                    possibleMoves.push_back(47 + (9*(color-1)));
                }
                else if (selectedPawn == ((42 + (11*(color-1))))%44) {  //If pawn is four away from safety zone
                    possibleMoves.push_back(48 + (9*(color-1)));
                }
                else if (selectedPawn == ((41 + (11*(color-1)))%44)) {  //If pawn is five away from safety zone
                    possibleMoves.push_back(49 + (9*(color-1)));
                }
                else if (selectedPawn == (0 + 11*(color-1))) {    //Pawn can move to home
                    possibleMoves.push_back(findNextOpenHome(color));
                }
                else if (((selectedPawn >= (47 + 9*(color-1))) && (selectedPawn <= (49 + 9*(color-1)))) || (selectedPawn == (1 + 11*(color-1)))) {    //Pawn too close to home
                    break;
                }
                else if ((selectedPawn >= (50 + 9*(color-1))) && (selectedPawn <= (52 + 9*(color-1)))) {    //Pawn can't move in start
                    break;
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else {  //Otherwise move 5 spaces forwards
                    possibleMoves.push_back((selectedPawn + 5)%44);
                }
                break;
            case 7:
                if ((selectedPawn >= (50 + 9*(color-1))) && (selectedPawn <= (52 + 9*(color-1)))) {    //Pawn can't move in start
                    break;
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else if (selectedPawn == (47 + 9*(color-1))) {  //One away from home
                    possibleMoves.push_back(findNextOpenHome(color));
                }
                else if (selectedPawn == (48 + 9*(color-1))) {  //Two away from home
                    possibleMoves.push_back(findNextOpenHome(color));
                    possibleMoves.push_back(selectedPawn - 1);
                }
                else if (selectedPawn == (49 + 9*(color-1))) {  //Three away from home
                    possibleMoves.push_back(findNextOpenHome(color));
                    possibleMoves.push_back(selectedPawn - 1);
                    possibleMoves.push_back(selectedPawn - 2);
                }
                else if (selectedPawn == (1 + 11*(color-1))) {  //Four away from home
                    possibleMoves.push_back(findNextOpenHome(color));
                    possibleMoves.push_back(47 + 9*(color-1));
                    possibleMoves.push_back(48 + 9*(color-1));
                    possibleMoves.push_back(49 + 9*(color-1));
                }
                else if (selectedPawn == (0 + 11*(color-1))) {  //Five away from home
                    possibleMoves.push_back(findNextOpenHome(color));
                    possibleMoves.push_back(47 + 9*(color-1));
                    possibleMoves.push_back(48 + 9*(color-1));
                    possibleMoves.push_back(49 + 9*(color-1));
                    possibleMoves.push_back(1 + 11*(color-1));
                }
                else if (selectedPawn == ((43 + 11*(color-1))%44)) {    //Six away from home
                    possibleMoves.push_back(findNextOpenHome(color));
                    possibleMoves.push_back(47 + 9*(color-1));
                    possibleMoves.push_back(48 + 9*(color-1));
                    possibleMoves.push_back(49 + 9*(color-1));
                    possibleMoves.push_back(1 + 11*(color-1));
                    possibleMoves.push_back(0 + 11*(color-1));
                }
                else if (selectedPawn == ((42 + 11*(color-1))%44)) {    //Seven away from home
                    possibleMoves.push_back(findNextOpenHome(color));
                    possibleMoves.push_back(47 + 9*(color-1));
                    possibleMoves.push_back(48 + 9*(color-1));
                    possibleMoves.push_back(49 + 9*(color-1));
                    possibleMoves.push_back(1 + 11*(color-1));
                    possibleMoves.push_back(0 + 11*(color-1));
                    possibleMoves.push_back((43 + 11*(color-1))%44);
                }
                else {
                    possibleMoves.push_back((selectedPawn + 7)%44);
                    possibleMoves.push_back((selectedPawn + 6)%44);
                    possibleMoves.push_back((selectedPawn + 5)%44);
                    possibleMoves.push_back((selectedPawn + 4)%44);
                    possibleMoves.push_back((selectedPawn + 3)%44);
                    possibleMoves.push_back((selectedPawn + 2)%44);
                    possibleMoves.push_back((selectedPawn + 1)%44);
                }
                //Need to check if second pawn can move the left over amount and set leftOverSpaces
                break;
            case 8:
                if (selectedPawn == ((40 + (11*(color-1))))%44) {  //If pawn is six away from safety zone
                    possibleMoves.push_back(47 + (9*(color-1)));
                }
                else if (selectedPawn == ((39 + (11*(color-1))))%44) {  //If pawn is seven away from safety zone
                    possibleMoves.push_back(48 + (9*(color-1)));
                }
                else if (selectedPawn == ((38 + (11*(color-1)))%44)) {  //If pawn is eight away from safety zone
                    possibleMoves.push_back(49 + (9*(color-1)));
                }
                else if (selectedPawn == ((41 + 11*(color-1))%44)) {    //Pawn can move to home
                    possibleMoves.push_back(findNextOpenHome(color));
                }
                else if (((selectedPawn >= (47 + 9*(color-1))) && (selectedPawn <= (49 + 9*(color-1)))) || (selectedPawn == (0 + 11*(color-1))) || (selectedPawn == (1 + 11*(color-1))) || ((selectedPawn >= ((42 + 11*(color-1))%44)) && (selectedPawn <= ((43 + 11*(color-1))%44)))) {    //Pawn too close to home
                    break;
                }
                else if ((selectedPawn >= (50 + 9*(color-1))) && (selectedPawn <= (52 + 9*(color-1)))) {    //Pawn can't move in start
                    break;
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else {  //Otherwise move 8 spaces forwards
                    possibleMoves.push_back((selectedPawn + 8)%44);
                }
                break;
            case 10:
                if (selectedPawn == ((38 + (11*(color-1))))%44) {  //If pawn is eight away from safety zone
                    possibleMoves.push_back(47 + (9*(color-1)));
                    possibleMoves.push_back(selectedPawn - 1);
                }
                else if (selectedPawn == ((37 + (11*(color-1))))%44) {  //If pawn is nine away from safety zone
                    possibleMoves.push_back(48 + (9*(color-1)));
                    possibleMoves.push_back(selectedPawn - 1);
                }
                else if (selectedPawn == ((36 + (11*(color-1)))%44)) {  //If pawn is ten away from safety zone
                    possibleMoves.push_back(49 + (9*(color-1)));
                    possibleMoves.push_back(selectedPawn - 1);
                }
                else if (selectedPawn == ((39 + 11*(color-1))%44)) {    //Pawn can move to home
                    possibleMoves.push_back(findNextOpenHome(color));
                    possibleMoves.push_back(selectedPawn - 1);
                }
                else if ((selectedPawn >= (47 + 9*(color-1))) && (selectedPawn <= (48 + 9*(color-1)))) {    //Pawn in safety zone
                    possibleMoves.push_back(selectedPawn - 1);
                }
                else if (selectedPawn >= (49 + 9*(color-1))) {    //Pawn in beginning of safety zone
                    possibleMoves.push_back(1);
                }
                else if (((selectedPawn >= (40 + 11*(color-1))) && (selectedPawn <= (43 + 11*(color-1)))) || (selectedPawn == (0 + 11*(color-1))) || (selectedPawn == (1 + 11*(color-1)))) {    //Pawn too close to home to move ten
                    if (selectedPawn == 0) {
                        possibleMoves.push_back(43);
                    } else {
                        possibleMoves.push_back(selectedPawn - 1);
                    }
                }
                else if ((selectedPawn >= (50 + 9*(color-1))) && (selectedPawn <= (52 + 9*(color-1)))) {    //Pawn can't move in start
                    break;
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else {  //Otherwise move 10 spaces forwards or 1 space backwards
                    possibleMoves.push_back((selectedPawn + 10)%44);
                    possibleMoves.push_back(selectedPawn - 1);
                }
                break;
            case 11:
                for (int i = 0; i < 44; i++) {
                    if(currentLocations[i] != color && currentLocations[i] != 0) {
                        possibleMoves.push_back(i);
                    }
                }
                if (selectedPawn == ((37 + (11*(color-1))))%44) {  //If pawn is nine away from safety zone
                    possibleMoves.push_back(47 + (9*(color-1)));
                }
                else if (selectedPawn == ((36 + (11*(color-1))))%44) {  //If pawn is ten away from safety zone
                    possibleMoves.push_back(48 + (9*(color-1)));
                }
                else if (selectedPawn == ((35 + (11*(color-1)))%44)) {  //If pawn is eleven away from safety zone
                    possibleMoves.push_back(49 + (9*(color-1)));
                }
                else if (selectedPawn == ((38 + 11*(color-1))%44)) {    //Pawn can move to home
                    possibleMoves.push_back(findNextOpenHome(color));
                }
                else if (((selectedPawn >= (47 + 9*(color-1))) && (selectedPawn <= (49 + 9*(color-1)))) || (selectedPawn == (0 + 11*(color-1))) || (selectedPawn == (1 + 11*(color-1))) || ((selectedPawn >= ((39 + 11*(color-1))%44)) && (selectedPawn <= ((43 + 11*(color-1))%44)))) {    //Pawn too close to home
                    break;
                }
                else if ((selectedPawn >= (50 + 9*(color-1))) && (selectedPawn <= (52 + 9*(color-1)))) {    //Pawn can't move in start
                    break;
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else {  //Otherwise move 11 spaces forwards
                    possibleMoves.push_back((selectedPawn + 11)%44);
                }
                break;
            case 12:
                if (selectedPawn == ((36 + (11*(color-1))))%44) {  //If pawn is ten away from safety zone
                    possibleMoves.push_back(47 + (9*(color-1)));
                }
                else if (selectedPawn == ((35 + (11*(color-1))))%44) {  //If pawn is eleven away from safety zone
                    possibleMoves.push_back(48 + (9*(color-1)));
                }
                else if (selectedPawn == ((34 + (11*(color-1)))%44)) {  //If pawn is twelve away from safety zone
                    possibleMoves.push_back(49 + (9*(color-1)));
                }
                else if (selectedPawn == ((37 + 11*(color-1))%44)) {    //Pawn can move to home
                    possibleMoves.push_back(findNextOpenHome(color));
                }
                else if (((selectedPawn >= (47 + 9*(color-1))) && (selectedPawn <= (49 + 9*(color-1)))) || (selectedPawn == (0 + 11*(color-1))) || (selectedPawn == (1 + 11*(color-1))) || ((selectedPawn >= ((38 + 11*(color-1))%44)) && (selectedPawn <= ((43 + 11*(color-1))%44)))) {    //Pawn too close to home
                    break;
                }
                else if ((selectedPawn >= (50 + 9*(color-1))) && (selectedPawn <= (52 + 9*(color-1)))) {    //Pawn can't move in start
                    break;
                }
                else if ((selectedPawn >= (44 + 9*(color-1))) && (selectedPawn <= (46 + 9*(color-1)))) {    //Pawn can't move in home
                    break;
                }
                else {  //Otherwise move 12 spaces forwards
                    possibleMoves.push_back((selectedPawn + 12)%44);
                }
                break;
        }
        return possibleMoves;
    }

    int findNextOpenHome(int color) {
        switch (color) {
            case 1:
                for (int i = 44; i < 47; i++) {
                    if (currentLocations[i] == 0) {
                        return i;
                    }
                }
                break;
            case 2:
                for (int i = 53; i < 56; i++) {
                    if (currentLocations[i] == 0) {
                        return i;
                    }
                }
                break;
            case 3:
                for (int i = 62; i < 65; i++) {
                    if (currentLocations[i] == 0) {
                        return i;
                    }
                }
                break;
            case 4:
                for (int i = 71; i < 74; i++) {
                    if (currentLocations[i] == 0) {
                        return i;
                    }
                }
                break;
        }
        return -1;
    }

    //Save the current locations
    void saveCurrentLocations(std::vector<int> locations) {
        currentLocations = locations;
    }

    //Save the last locations
    void saveLastLocations(std::vector<int> locations) {
        lastLocations = locations;
    }

    //Check if all pieces are placed
    bool allPiecesPlaced() {
        int count = 0;
        for (int i = 0; i < 40; i++) {
            if (currentLocations[i]) {
                count++;
            }
        }
        return count == MAX_PIECES;
    }

    bool allPiecesOnStart() {
        int numberOfFilledAreas = 0;
        //Check if 50, 51, 52 occupied
        //If true increment numberOfFilledAreas

        //Check if 59, 60, 61 occupied
        //If true increment numberOfFilledAreas

        //Check if 68, 69, 70 occupied
        //If true increment numberOfFilledAreas

        //Check if 77, 78, 79 occupied
        //If true increment numberOfFilledAreas

        //For terminal testing
        numberOfFilledAreas = t_setStartAreas();

        if (numberOfFilledAreas >= playerCount) {
            return true;
        } else {
            return false;
        }
    }



    /////////////////////
    //Terminal funtions//
    /////////////////////

    int t_GetCard() {
        int card;
        cout << "Enter card number: ";
        cin >> card;
        return card;
    }

    int t_setStartAreas() {
        currentLocations[50] = 1;
        currentLocations[51] = 1;
        currentLocations[52] = 1;
        currentLocations[59] = 2;
        currentLocations[60] = 2;
        currentLocations[61] = 2;
        if (playerCount >= 3) {
            currentLocations[68] = 3;
            currentLocations[69] = 3;
            currentLocations[70] = 3;
        } else if (playerCount == 4) {
            currentLocations[77] = 4;
            currentLocations[78] = 4;
            currentLocations[79] = 4;
        }

        lastLocations = currentLocations;
        return playerCount;
    }

    void t_displayCardInstructions() {
        switch (lastCard) {
            case 0:
                cout << "Whoops! Take any one pawn from Start and move it directly to a square occupied by any opponent's pawn, sending that pawn back to its own Start. A Whoops! card cannot be used on an opponent's pawn in a Safety Zone or at the Home base. If there are no pawns on the player's Start, or no opponent's pawns on any space that can be moved to, the turn ends." << endl;
                break;
            case 1:
                cout << "Either move a pawn from Start or move a pawn 1 space forward." << endl;
                break;
            case 2:
                cout << "Either move a pawn from Start or move a pawn 2 spaces forward." << endl; //Maybe add draw again
                break;
            case 3:
                cout << "Move a pawn 3 spaces forward." << endl;
                break;
            case 4:
                cout << "Move a pawn 4 spaces backward." << endl;
                break;
            case 5:
                cout << "Move a pawn 5 spaces forward." << endl;
                break;
            case 7:
                cout << "Move one pawn 7 spaces forward, or split the 7 spaces between two pawns (such as 4 spaces for one pawn and 3 for another)." << endl;
                break;
            case 8:
                cout << "Move a pawn 8 spaces forward." << endl;
                break;
            case 10:
                cout << "Move a pawn 10 spaces forward or 1 space backward. If none of a player's pawns can move forward 10 spaces, then one pawn must move back 1 space." << endl;
                break;
            case 11:
                cout << "Move 11 spaces forward, or switch the places of one of the player's own pawns and an opponent's pawn. A player who cannot move 11 spaces is not forced to switch and instead can end their turn. An 11 cannot be used to switch a pawn that is in a Safety Zone." << endl;
                break;
            case 12:
                cout << "Move a pawn 12 spaces forward." << endl;
                break;
        }
        cout << endl;
    }

    void t_whereAreMyPieces() {
        cout << "Player " << currentPlayer + 1 << "'s pieces: ";
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (currentLocations[i] == currentPlayer + 1) {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    void t_selectPiece() {
        int location;
        cout << "Select a location to move " << currentPlayer + 1 << "'s piece from: ";
        cin >> location;
        while (currentLocations[location] != currentPlayer + 1) {
            cout << "Invalid piece" << endl;
            cout << "Select a piece to move: ";
            cin >> location;
        }
        currentLocations[location] = 0;
        movingFrom = location;
        setPlayerColor();
    }
}