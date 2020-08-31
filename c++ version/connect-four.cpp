#include <iostream>
#include <string>
using namespace std;
//create a pointer for board
int** board[6][7];
int height = 6;
int width =7;
int player = 1;
string ply = "player";
string com = "computer";
int computer = 2;
void display(int** Board);
int** createBoard(unsigned height, unsigned width );
bool isSpaceFree(int move, int** Board);
int getPlayerMove(int** Board);
void makeMove(int sign, int move, int** Board);
bool isFull(int** Board);
bool checkWin(int sign, int** Board);
int** copyTemp(int** Board);
int getComputerMove(int** Board);
int randomPlay(int** Board, int move);
int getRandomIndex(int** Board);
int* findOpenIndex(int** currBoard);
int getBestMove(int** Board,int depth, int who);
int minimax(int** currBoard,int depth, int who,int col);
int evalMove(int** currBoard);
int checkThrees(int** Board, int sign);
int checkTwos(int** Board, int sign);



int main(){
    int** board = createBoard(height, width);
    display(board);
    bool win = false;
    int level;
    string turn;
    string answer;
    while(true){
        cout<<"Choose difficult level: 1 or 2"<<endl;
        cin>>level;
        if(level == 1 || level == 2) break;
        else cout<<"please enter 1 or 2"<<endl;

    }
    while(true){        
        cout<<"Do you want to go first? (y/n)"<<endl;
        cin>>answer;
        if(answer.compare("y") == 0|| answer.compare("yes")==0) {
            turn ="player";
            break;
        }
        else if(answer.compare("n")==0||answer.compare("no")==0){
            turn = "computer";
            break;
        } 
        else cout<<"please enter yes or no"<<endl;
    }

    int move;
    while(!win){
        if(turn.compare(ply) == 0){
            cout<<"Your turn:"<<endl;
            move = getPlayerMove(board);
            makeMove(player, move, board);
            display(board);
            if(checkWin(player,board)){
                cout<<"player win!"<<endl;
                break;
            }
            else if(isFull(board)){
                cout<<"the board is full"<<endl;
                break;
            }
            turn = "computer";
        }
        if(turn.compare(com) == 0){
            cout<<"Computer's turn"<<endl;
            if(level == 2) move = getComputerMove(board);
            else if (level == 1) move = getBestMove(board,6,computer);
            makeMove(computer,move,board);
            display(board);
            if(checkWin(computer,board)){
                cout<<"computer win!"<<endl;
                break;
            }
            else if(isFull(board)){
                cout<<"the board is full"<<endl;
                break;
            }
            turn = "player";
        }
    }

    return 0;
}





//create the board
 int** createBoard(unsigned height, unsigned width){
      int** Board = 0;
      Board = new int*[height];
      for (int h = 0; h < height; h++){
            Board[h] = new int[width];
            for (int w = 0; w < width; w++){
                  // fill in some initial values
                  // (filling in zeros would be more logic, but this is just for the example)
                  Board[h][w] = 0;
            }
      }
      return Board;
    }

//display the board
void display(int** Board){
    cout<<" 1 2 3 4 5 6 7 \n";
    for(int a = 0; a<= 5; a++){
		for(int b =0; b <= 6; b++) {
            cout<<"|"<< Board[a][b];
            if(b == 6){cout <<"|";}
            }
		cout<<'\n';
        cout<<"---------------";
        cout<<'\n';
	}
}

//check if the move place is valid
bool isSpaceFree(int move, int** Board){
    for(int i =0; i< height; i++){
        if(Board[i][move] == 0){
            return true;
        }
    }
    //cout<<"this column is full"<< endl;
    return false;
}

//ask player to go next step
int getPlayerMove(int** Board){
    int index;
    while(true){
        cout<<"what's your next move?(1-7)"<<endl;
        cin>>index;
        index = index -1;
        if(index >=0 && index <=6 && isSpaceFree(index,Board)){
            return index;
        }
        else if (!isSpaceFree(index,Board)){
            cout<<"this colmn is full"<<endl;
        }
        cout<< "please return a valid one"<<endl;
    }
}

//insert the board
void makeMove(int sign, int move, int** Board){
    for(int i = 5; i>=0; i--){
        if(Board[i][move] == 0){
            Board[i][move] = sign;
            return;
        }
    }
}

bool isFull(int** Board){
    for(int i = 0; i<=5;i++){
        for(int j= 0; j<=6;j++){
            if(Board[i][j] == 0) return false;
        }
    }
    return true;
}

bool checkWin(int sign, int** Board){
    //column win
    for(int i =0;i<3;i++){
        for(int j=0;j<=6;j++){
            int x = Board[i][j];
            if(x == sign){
                if(x == Board[i+1][j]&& x == Board[i+2][j]&& x == Board[i+3][j]) return true;
            }
        }
    }

    //row win
    for(int i = 0; i< 4;i++){
        for( int j=0;j<=5;j++){
           int x =Board[j][i];
            if(x == sign){
                if(x== Board[j][i+1] && x == Board[j][i+2] && x == Board[j][i+3]) return true;
            }
        }
    } 

    //diagonal(\)
    for(int i = 0; i<= 2; i++){
         for(int j = 0; j <= 3; j++){
            int x = Board[i][j];
            if(x == sign){
                if(x == Board[i+1][j+1] && x == Board[i+2][j+2] && x == Board[i+3][j+3]) return true;
            } 
         }
    }

    //diagonal (/)
    for(int i = 0; i <= 2; i++){
         for (int j = 6; j>=3 ;j--){
             int x =  Board[i][j];
             if(x == sign){
                 if(x == Board[i+1][j-1] && x == Board[i+2][j-2] && x == Board[i+3][j-3]) return true;
             }
         }
     }    
     return false;  
}

//copy a temp one for computer
int** copyTemp(int** Board){
    int** temp =0;
    temp= new int* [height];
    for (int h = 0; h < height; h++){
        temp[h] = new int[width];
        for (int w = 0; w < width; w++){
                  temp[h][w] = Board[h][w];
            }
      }
      return temp;
}

int getComputerMove(int** Board){
    int** temp = copyTemp(Board);
    int winTime = 0;
    int index = 0;
    int maximum = randomPlay(temp,0);
    for(int i = 0; i<=6; i++){
        if(isSpaceFree(i,temp)){
            //need to copy a new temp for try random play
            winTime = randomPlay(temp,i);
            if(winTime>= maximum){
                maximum = winTime;
                index = i;
            }
        }
    }
    return index;
}

//random play for compter play itself to calculate a maximum win time
int randomPlay(int** Board, int move){
    int score=0;
    string ran_player = "player";
    string ran_computer = "computer";   
    int ran_move;
    int** ran_temp;
    //try 100 times for moving with this step
    for(int i = 0; i<500;i++){
        //copy a new temp board
        ran_temp = copyTemp(Board);
        //move with the choosen step for computer
        makeMove(computer,move,ran_temp);
        //next turn is for player
        string turn = "player";
        while(!isFull(ran_temp)){
            if(turn.compare(ran_player)==0){
                ran_move = getRandomIndex(ran_temp);
                makeMove(player,ran_move,ran_temp);
                if(checkWin(player,ran_temp)){
                    score = score - 10;
                    break;
                }
                else if(isFull(ran_temp)){
                    score = score - 5;
                    break;
                }
                turn = "computer";
            }
            if(turn.compare(ran_computer)==0){
                ran_move = getRandomIndex(ran_temp);
                makeMove(computer,ran_move,ran_temp);
                if(checkWin(computer,ran_temp)){
                    score = score + 20;
                    break;
                }
                else if(isFull(ran_temp)){
                    score = score -5;
                    break;
                }
                turn = "player";
            }
        }
        free(ran_temp);
    }
    return score;
}

//suppose there is still free column
int getRandomIndex(int** Board){
    int index;
    while(true){
        index = rand()%7;
        if(index >=0 && index <=6 && isSpaceFree(index,Board)){
            return index;
        }
    }
}


int getBestMove(int** Board,int depth, int who) {
        int opp;
        //Get opponent for next piece
        if(who == 1) {
            opp = 2;
        } else {
            opp = 1;
        }
        int* aiOpenCols = findOpenIndex(Board);
        int length = sizeof(aiOpenCols)/sizeof(aiOpenCols[0]);
        int** temp; 
        int moves[7];
        //Drop each piece and use minimax function until depth == 0
        for(int i=0; i<length; i++) {
            temp = copyTemp(Board);
            makeMove(who,aiOpenCols[i],temp);
            moves[i] = minimax(temp,(depth - 1),opp,aiOpenCols[i]);
        }

        int bestAlpha = -100000;    //Large negative
        //Use random column if no moves are "good"
        int bestMove;// = Math.floor(Math.random() * aiOpenCols.length);
        //bestMove = +aiOpenCols[bestMove];
        //Get largest value from moves for best move
        for(int i=0; i<length; i++) {
            if(moves[i] > bestAlpha) {
                bestAlpha = moves[i];
                bestMove = aiOpenCols[i];
            }
        }

        bestMove++; //Offset by 1 due to actual drop function
        return bestMove;
    } 
int minimax(int** currBoard,int depth, int who,int col) {
    int* aiOpenCols = findOpenIndex(currBoard);
    int length = sizeof(aiOpenCols)/sizeof(aiOpenCols[0]);
    //Drop current piece, called from getBestMove function
    makeMove(who,col,currBoard);
    //Get opponent for next piece
    int opp;
    if(who == 2) {
        opp = 1;
    } 
    else{
        opp = 2;
    }   
    int** tBoard; 
    int alpha = -100000;    //Large negative
    
    //When depth == 0 return heuristic/eval of board
    if(depth == 0) {
        int ev = evalMove(currBoard);
        return ev;
    }

    //Loop through all available moves
    for(int i=0; i<length; i++) {
        tBoard = copyTemp(currBoard);
        //Continue recursive minimax until depth == 0
        int next = minimax(tBoard,(depth - 1),opp,aiOpenCols[i]);
        //Alpha = max(alpha, -minimax()) for negamax
        if(alpha < (0-next)){
            alpha = 0 - next;
        }
        free(tBoard);
    }
    return alpha;
}

//return the score for current board
//if computer won, return the larger score
//if player won, return the smaller score
//if still in game, return the score calculated by chances.
int evalMove(int** currBoard) {
    //heuristic function
    //AI = # of 4 streaks + # of 3 streaks + # of 2 streaks - # of 3 streaks opp - # of 2 streaks opp           
    if(checkWin(computer,currBoard)){
        return 100000;
    }
    else if(checkWin(player,currBoard)){
    //If opponent wins, return large negative
        return -100000;
    }
    else{     
    //If win return large positive
    int threes = checkThrees(currBoard,2) * 1000;
    int twos = checkTwos(currBoard,2) * 10;
    int PlayerThrees = checkThrees(currBoard,1) * 1000;
    int PlayerTwos = checkTwos(currBoard,1) * 10;
    int scores = threes + twos - PlayerThrees - PlayerTwos;
    return scores;
    }
}

int* findOpenIndex(int** currBoard){
    int* aiOpenCols;
    int length =0;
    int k =0;
    for (int i =0; i<7;i++){
        if(isSpaceFree(i,currBoard)){
            length++;
        }
    }
    aiOpenCols = new int[length];
    for(int j =0; j<7;j++){
        if(isSpaceFree(j,currBoard)){
            aiOpenCols[k] = j;
            k++;
        }
    }
    return aiOpenCols;
}


int checkThrees(int** Board, int sign){
    for(int i =0;i<=3;i++){
        for(int j=0;j<=6;j++){
            int x = Board[i][j];
            if(x == sign){
                //check if three together
                if(x == Board[i+1][j]&& x == Board[i+2][j]) {
                    if(i == 0){
                        if(x!=Board[i+3][j]) return 2;
                        
                    }
                    else if(i==3){
                        if(x!= Board[2][j]) return 2;
                    }
                    else{
                        if(x!= Board[i-1][j]&& x!=Board[i+3][j]) return 3;  
                    } 
                }
            }
        }
    }
    //row win
    for(int i = 0; i<= 4;i++){
        for( int j=0;j<=5;j++){
           int x =Board[j][i];
            if(x == sign){
                if(x== Board[j][i+1] && x == Board[j][i+2]){
                    if(i==0 || i == 4){
                        if(x!=Board[j][3]) return 2;
                    }
                    else {
                        if(x!=Board[j][i-1] && x!= Board[j][i+3]) return 3;
                    }
                }
            }
        }
    } 
    //diagonal(\)
    for(int i = 0; i<= 3; i++){
        if(i==0){
            for(int j = 0; j <= 3; j++){
                int x = Board[i][j];
                if(x == sign){
                    if(x == Board[i+1][j+1] && x == Board[i+2][j+2]&& x!= Board[i+3][j+3]) return 2;
                } 
            }
        }
        else if(i == 3){
            for(int j = 1; j <= 4; j++){
                int x = Board[i][j];
                if(x == sign){
                    if(x == Board[i+1][j+1] && x == Board[i+2][j+2]&& x!= Board[i+3][j+3]) return 2;
                } 
            }
        }
        else{
            int x = Board[i][0];
            if(x == Board[i+1][1] && x == Board[i+2][2]&& x!= Board[i+3][3]) return 2;

            for(int j = 1; j <= 4; j++){
                int x = Board[i][j];
                if(x == sign){
                    if(x == Board[i+1][j+1] && x == Board[i+2][j+2]&& x!= Board[i+3][j+3]&& x!=Board[i-1][j-1]) return 3;
                } 
            }
        }
    }

    //diagonal (/)
    for(int i = 0; i <= 2; i++){
         for (int j = 6; j>=3 ;j--){
             int x =  Board[i][j];
             if(x == sign){
                 if(x == Board[i+1][j-1] && x == Board[i+2][j-2]) return 2;
             }
         }
     }  
    return 0;
}


int checkTwos(int** Board, int sign){

    for(int i =0;i<=4;i++){
        for(int j=0;j<=6;j++){
            int x = Board[i][j];
            if(x == sign){
                //check if three together
                if(x == Board[i+1][j]) {
                    if(i == 0){
                        if(x!=Board[i+2][j]) return 1;
                        
                    }
                    else if(i==4){
                        if(x!= Board[3][j]) return 1;
                    }
                    else{
                        if(x!= Board[i-1][j]&& x!=Board[i+2][j]) return 1;  
                    } 
                }
            }
        }
    }
    //row win
    for(int i = 0; i<= 5;i++){
        for( int j=0;j<=5;j++){
           int x =Board[j][i];
            if(x == sign){
                if(x== Board[j][i+1]){
                    if(i==0){
                        if(x!=Board[j][2]) return 1;
                    }
                    else if(i==5){
                        if(x!= Board[j][4]) return 1;
                    }
                    else {
                        if(x!=Board[j][i-1] && x!= Board[j][i+2]) return 1;
                    }
                }
            }
        }
    } 
    //diagonal(\)
    for(int i = 0; i<= 2; i++){
         for(int j = 0; j <= 3; j++){
            int x = Board[i][j];
            if(x == sign){
                if(x == Board[i+1][j+1]) return 1;
            } 
         }
    }

    //diagonal (/)
    for(int i = 0; i <= 2; i++){
         for (int j = 6; j>=3 ;j--){
             int x =  Board[i][j];
             if(x == sign){
                 if(x == Board[i+1][j-1]) return 1;
             }
         }
     }    
    return 0;
}

