import random

player = 'X'
randomPlayer ='X'
computer = 'O'
randomComputer = 'O'




def drawBoard(board):
    # "board" is a list of 10 strings representing the board (ignore index 0)
    #print('   |   |')
    print(' ' + board[1] + ' | ' + board[2] + ' | ' + board[3])
    #print('   |   |')
    print('-----------')
    #print('   |   |')
    print(' ' + board[4] + ' | ' + board[5] + ' | ' + board[6])
    #print('   |   |')
    print('-----------')
    #print('   |   |')
    print(' ' + board[7] + ' | ' + board[8] + ' | ' + board[9])
    #print('   |   |')

def whoGoesFirst():
    # Randomly choose the player who goes first.
    print('Do you want to go first?(yes/no)')

    if input().lower().startswith('y'):
        return 'player'
    else:
        return 'computer'

def getPlayerMove(board):
        # Let the player type in his move.
    move = ' '
    #made sure the place is movable
    while move not in '1 2 3 4 5 6 7 8 9'.split() or not isSpaceFree(board, int(move)):
        print('What is your next move? (1-9)')
        move = input()

    # if move == ' ':
    #     return None
    # else:
    return int(move)

def isSpaceFree(board, move):
    #if board == ' ', then it is free
    return board[move] == ' '

def makeMove(board, Letter, move):
    board[move] = Letter
    
def isWinner(bo, le):
    # Given a board and a player's letter, this function returns True if that player has won.
    # We use bo instead of board and le instead of letter so we don't have to type as much.
    return ((bo[7] == le and bo[8] == le and bo[9] == le) or # across the top
    (bo[4] == le and bo[5] == le and bo[6] == le) or # across the middle
    (bo[1] == le and bo[2] == le and bo[3] == le) or # across the bottom
    (bo[7] == le and bo[4] == le and bo[1] == le) or # down the left side
    (bo[8] == le and bo[5] == le and bo[2] == le) or # down the middle
    (bo[9] == le and bo[6] == le and bo[3] == le) or # down the right side
    (bo[7] == le and bo[5] == le and bo[3] == le) or # diagonal
    (bo[9] == le and bo[5] == le and bo[1] == le)) # diagonal


def playAgain():
    # This function returns True if the player wants to play again, otherwise it returns False.
    print('Do you want to play again? (yes or no)')
    return input().lower().startswith('y')

def getBoardCopy(board):
    # Make a duplicate of the board list and return it the duplicate.
    dupeBoard = []

    for i in board:
        dupeBoard.append(i)

    return dupeBoard

def isBoardFull(board):
    # Return True if every space on the board has been taken. Otherwise return False.
    for i in range(1, 10):
        if isSpaceFree(board, i):
            return False
    return True

#checked
def LegalMoves(board):
    # Returns a valid move list
    # Returns None if there is no valid move.
    possibleMoves = []
    for i in range(1,len(board)):
        if isSpaceFree(board, i):
            possibleMoves.append(i)

    if len(possibleMoves) != 0:
        return possibleMoves
    else:
        return None


def getComputerMove(board):
    # Given a board and the computer's letter, determine where to move and return that move.

    movable = LegalMoves(board)
    # find all movable places    
    if movable == None:
        return False

    if len(movable) == 1:
        return movable[0]

    else:
        #index that win most times
        max_win_time = 0
        #the chosen move index
        next_move = movable[0]
        temp = 0
        #for every movable places:
        for i in range(len(movable)):
            #copy a board for testing every possible move 
            copy = getBoardCopy(board)
            #make a move in the copy place
            makeMove(copy,computer,movable[i])
            #calculate the win rate for moving in i-th place
            #in random play, it should sum the total win times 
            temp = random_play(copy)
            #if the win rate is larger than the current win rate, replace
            if temp > max_win_time:
                max_win_time = temp
                next_move = movable[i]
    
        return next_move


def getRandomMove(board):
    movable = LegalMoves(board)
    if movable == None:
        return False       
    return random.choice(movable)



def random_play (board):
    win_time = 0
    for i in range(500):
        #copy again, for 500 times independent testing
        copy2 = getBoardCopy(board)
        turn = 'randomPlayer'
        while True:
            if turn == 'randomPlayer':
                # randomPlayer turn.
                move = getRandomMove(copy2)
                if move == False:
                    break
                else:
                    makeMove(copy2, randomPlayer, move)
                #if random wins
                if isWinner(copy2, randomPlayer):
                    win_time -= 10
                    break
                else:
                    if isBoardFull(copy2):
                        win_time -= 5
                        break
                    else:
                        turn = 'randomComputer'

            else:
             # Computer's turn.
                move = getRandomMove(copy2)
                if move == False:
                    print("no place for randomCopumet")
                    break
                else:
                    makeMove(copy2, randomComputer, move)

                if isWinner(copy2, randomComputer):
                    win_time+= 20
                    break
                else:
                    if isBoardFull(copy2):
                        win_time -= 5
                        break
                    else:
                        turn = 'randomPlayer'
    return win_time

#board = [' ',' ','X',' ',' ',' ',' ',' ',' ',' x']
# board = [' ',' x','X','x ','x ',' x','x ',' x','x ',' x']

# print (getRandomMove(board))



# print (getComputerMove(board, 'x'))






def play_a_new_game():
    print('Welcome to Tic Tac Toe!')
    while True:
        # Reset the board
        theBoard = [' '] * 10
        turn = whoGoesFirst( )
        print('The ' + turn + ' will go first.')
        gameIsPlaying = True
        while gameIsPlaying:
            print("\n")
            if turn == 'player':
                # Player's turn.
                move = getPlayerMove(theBoard)
                makeMove(theBoard, player, move)
                drawBoard(theBoard)
                if isWinner(theBoard, player):
                    print('Hooray! You have won the game!')
                    gameIsPlaying = False
                else:
                    if isBoardFull(theBoard):
                        print('The game is a tie!')
                        break
                    else:
                        turn = 'computer'
            else:
                print("computer's turn")
                # Computer's turn.
                move = getComputerMove(theBoard)
                if move == False:
                    print("computer cannot choose!")
                    break
                else:
                    makeMove(theBoard, computer, move)
                    drawBoard(theBoard)

                if isWinner(theBoard, computer):
                    
                    print('The computer has beaten you! You lose.')
                    gameIsPlaying = False
                else:
                    if isBoardFull(theBoard):
                
                        print('The game is a tie!')
                        break
                    else:
                        turn = 'player'

        if not playAgain():
            break

play_a_new_game()

