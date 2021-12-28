from time import sleep
import sys
import os

def make_board():
  board = [[' ', ' ', ' ', ' ', ' ', ' '], 
          [' ', ' ', ' ', ' ', ' ', ' '], 
          [' ', ' ', ' ', ' ', ' ', ' '], 
          [' ', ' ', ' ', ' ', ' ', ' '], 
          [' ', ' ', ' ', ' ', ' ', ' '], 
          [' ', ' ', ' ', ' ', ' ', ' '], 
          [' ', ' ', ' ', ' ', ' ', ' ']]
  return board

p1 = 'x'
p2 = 'o'

board = make_board()

one = [];
two = [];
three = [];
four = [];
five = [];
six = [];
seven = [];

def empty():
  for row in range(len(board[0])):
    for col in range(len(board)):
      board[col][row] = " "

def initialize():
  header = ' '
  for num in range(1, len(board) + 1):
    header += ' '+ str(num) +'  '
  print(header)

  print('+---' * (len(board)) + '+')

  # Printing each row of the board
  for row in range(len(board[0])):
    row_with_items = ''
    for col in range(len(board)):
      row_with_items += ('| '+str(board[col][row])) + ' '
    print(row_with_items + '|')
    print('+---' * (len(board)) + '+')

def scanTemplate(playerNum, p):
  notFull = scanBoard()
  fourInARow = scanRow(p)
  fourInACol = scanColumn(p)
  fourInADiag = scanDiag(p)
  if (notFull == True and fourInARow == False and fourInACol == False and fourInADiag == False):
    initialize()
    return True
  elif (fourInARow == True or fourInACol == True or fourInADiag or True):
    initialize()
    print("Player " + playerNum + " has won.")
    sleep(1)
    playAgain()  
    return False
  elif notFull == False:
    initialize()
    print("Board is full")
    sleep(1);
    playAgain()  
    return False

def playAgain():
  print("Play again?")
  yn = input()
  yesno = yn.lower()
  if (yesno == "yes"):
    clear = lambda: os.system('clear')
    clear()
    empty()
    initialize()
    playMove(p1)
  else:
    sys.exit("~~yeet~~")

def scanBoard():
  numEmpty = 0;
  for j in range(5):
    for i in range(6):
      if board[i-1][j-1] == " ":
        numEmpty += 1
  if numEmpty > 0:
    return True
  elif numEmpty == 0:
    return False

def scanRow(p):
  for y in range(len(board[0])):
    for x in range(len(board) - 3):
      if (board[x][y] == p and board[x+1][y] == p and board[x+2][y] == p and board[x+3][y] == p):
        return True
  return False

def scanColumn(p):
  for x in range(len(board)):
    for y in range(len(board[0]) - 3):
      if (board[x][y] == p and board[x][y+1] == p and board[x][y+2] == p and board[x][y+3] == p):
        return True
  return False

def scanDiag(p):
  for x in range(len(board) - 3):
    for y in range(3, len(board[0])):
      if board[x][y] == p and board[x+1][y-1] == p and board[x+2][y-2] == p and board[x+3][y-3] == p:
        return True
  return False

  for x in range(len(board) - 3):
    for y in range(len(board[0]) - 3):
      if board[x][y] == p and board[x+1][y+1] == p and board[x+2][y+2] == p and board[x+3][y+3] == p:
        return True
  return False

def choosePlayer(p):
  if p == p1:
    p = p2
    playMove(p)
    return p
  elif (p == p2):
    p = p1;
    playMove(p)
    return p

def playMove(p):
  choice = -1
  theInput = ""
  playerNum = 0
  if (p == 'x'):
    playerNum = "one"
  elif (p == 'o'):
    playerNum = "two"
  print("Player " + playerNum + ", choose column to play.")
  theInput = input()

  try:
    val = int(theInput)
  except ValueError:
    print("not an int")
    sleep(0.50)
    clear = lambda: os.system('clear')
    clear()
    # print ("\n" * 100)
    initialize();
    playMove(p);

  choice = int(theInput)

  if (choice == 1):
    one.append(0)
    maxNum = max(one)
    one.append(maxNum + 1)
    go(maxNum, 1, p, playerNum)
  elif (choice == 2):
    two.append(0)
    maxNum = max(two)
    two.append(maxNum + 1)
    go(maxNum, 2, p, playerNum)
  elif (choice == 3):
    three.append(0)
    maxNum = max(three)
    three.append(maxNum + 1)
    go(maxNum, 3, p, playerNum)
  elif (choice == 4):
    four.append(0)
    maxNum = max(four)
    four.append(maxNum + 1)
    go(maxNum, 4, p, playerNum)
  elif (choice == 5):
    five.append(0)
    maxNum = max(five)
    five.append(maxNum + 1)
    go(maxNum, 5, p, playerNum)
  elif (choice == 6):
    six.append(0)
    maxNum = max(six)
    six.append(maxNum + 1)
    go(maxNum, 6, p, playerNum)
  elif (choice == 7):
    seven.append(0)
    maxNum = max(seven)
    seven.append(maxNum + 1)
    go(maxNum, 7, p, playerNum)
  else:
    print("out of bounds")
    sleep(0.50)
    clear = lambda: os.system('clear')
    clear()
    # print ("\n" * 100)
    initialize();
    playMove(p);

def go(m, col, p, pNum):
  if (m > 5):
    print("Column full.")
    sleep(0.50)
    clear = lambda: os.system('clear')
    clear()
    # print ("\n" * 100)
    cont = scanTemplate(pNum, p)
    if (cont == True):
      playMove(p)
    elif (cont == False):
      playAgain()  
  else:
    board[col - 1][5 - m] = p;
    clear = lambda: os.system('clear')
    clear()
    # print ("\n" * 100)
    cont = scanTemplate(pNum, p)
    while (cont == True):
      p = choosePlayer(p)
      playMove(p)
    playAgain()
    sys.exit("~~yeet~~")  

initialize()
playMove(p1)
