// i hope it works lol

import kotlin.system.exitProcess

var board = arrayOf(
    arrayOf(' ', ' ', ' ', ' ', ' ', ' ', ' '),
    arrayOf(' ', ' ', ' ', ' ', ' ', ' ', ' '),
    arrayOf(' ', ' ', ' ', ' ', ' ', ' ', ' '),
    arrayOf(' ', ' ', ' ', ' ', ' ', ' ', ' '),
    arrayOf(' ', ' ', ' ', ' ', ' ', ' ', ' '),
    arrayOf(' ', ' ', ' ', ' ', ' ', ' ', ' ')
)

var p1 = 'x'
var p2 = 'o'

var one = mutableListOf<Int>();
var two = mutableListOf<Int>();
var three = mutableListOf<Int>();
var four = mutableListOf<Int>();
var five = mutableListOf<Int>();
var six = mutableListOf<Int>();
var seven = mutableListOf<Int>();

fun printBoard() {
  var header = " ";
  for (i in 1..7) {
    header += i.toString();
    header += " ";
  }
  println(header);
  for (i in 0 .. 5) {
    for (j in 0 .. 6) {
      print("|" + board[i][j]);
    } 
    println("|");
  }
  println("```````````````");
}

fun emptyBoard() {
  for (row in 0..6) {
    for (col in 0..5) {
      board[col][row] = ' ';
    }
  }
  one.clear();
  two.clear();
  three.clear();
  four.clear();
  five.clear();
  six.clear();
  seven.clear();
}

fun choosePlayer(p: Char): Char {
  if (p == p1) {
    playMove(p2);
    return p2;
  }
  else if (p == p2) {
    playMove(p1);
    return p1;
  }
  return p;
}

fun playAgain() {
  var yesNo = readLine();
  if (yesNo == "y") {
      print("\u001b[H\u001b[2J");
      emptyBoard();
      printBoard();
      playMove(p1);
  } else if (yesNo == "n") {
      exitProcess(0);
  } else {
      println("Sorry, response not valid. Please enter again. ");
      playAgain();
  }
}

fun scanTemplate(playerNum: Int, p: Char): Boolean {
  var notFull = scanBoard();
  var fourInARow = scanRow(p);
  var fourInACol = scanColumn(p);
  var fourInADiag = scanDiag(p);
  if (notFull == true && fourInARow == false && fourInACol == false && fourInADiag == false) {
      printBoard();
      return true;
  } else if (notFull == false) {
      printBoard();
      println("Board is full, play again? (y/n)\n");
      playAgain();
      return false;
  } else if (fourInARow == true || fourInACol == true || fourInADiag == true) {
      printBoard();
      println("Player " + playerNum + " has won. Play again? (y/n)\n");
      playAgain();
      return false;
  }
  return false;
}

fun scanBoard(): Boolean {
    var numEmpty = 0;
    for (i in 0 .. 5) {
        for (j in 0 .. 6) {
            if (board[i][j] == ' ') {
                numEmpty++;
            }
        }
    }
    if (numEmpty > 0) {
        return true;
    } else if (numEmpty == 0) {
        return false;
    }
    return false;
}

fun scanRow(p: Char): Boolean {
  for (y in 0 .. 6) {
    for (x in 0 .. 2) {
      if (board[x][y] == p && board[x+1][y] == p && board[x+2][y] == p && board[x+3][y] == p) {
        return true;
      }
    }
  }
  return false;
}

fun scanColumn(p: Char): Boolean {
  for (y in 0 .. 3) {
    for (x in 0 .. 5) {
      if (board[x][y] == p && board[x][y+1] == p && board[x][y+2] == p && board[x][y+3] == p) {
        return true;
      }
    }
  }
  return false;
}

fun scanDiag(p: Char): Boolean {
  for (y in 3..6) {
    for (x in 0..2) {
      if (board[x][y] == p && board[x+1][y-1] == p && board[x+2][y-2] == p && board[x+3][y-3] == p) {
        return true;
      }
    }
  }

  for (y in 0 .. 3) {
    for (x in 0..2) {
      if (board[x][y] == p && board[x+1][y+1] == p && board[x+2][y+2] == p && board[x+3][y+3] == p) {
        return true;
      }
    }
  }
  return false;
}

fun playMove(p: Char) {
  var choice = -1;
  var playerNum = 0;
  if (p == 'x') {
    playerNum = 1;
  }
  else if (p == 'o') {
    playerNum = 2;
  }
  println("Player " + playerNum + ", choose column to play.")
  var theInput = readLine();

  when (theInput) {
    "1" -> {
      one.add(0);
      val maxNum: Int = one.maxOrNull() ?: 0
      one.add(maxNum + 1);
      go(maxNum, 1, p, playerNum); }
    "2" -> {
      two.add(0);
      val maxNum: Int = two.maxOrNull() ?: 0
      two.add(maxNum + 1);
      go(maxNum, 2, p, playerNum); }
    "3" -> {
      three.add(0);
      val maxNum: Int = three.maxOrNull() ?: 0
      three.add(maxNum + 1);
      go(maxNum, 3, p, playerNum); }
    "4" -> {
      four.add(0);
      val maxNum: Int = four.maxOrNull() ?: 0
      four.add(maxNum + 1);
      go(maxNum, 4, p, playerNum); }
    "5" -> {
      five.add(0);
      val maxNum: Int = five.maxOrNull() ?: 0
      five.add(maxNum + 1);
      go(maxNum, 5, p, playerNum); }
    "6" -> {
      six.add(0);
      val maxNum: Int = six.maxOrNull() ?: 0
      six.add(maxNum + 1);
      go(maxNum, 6, p, playerNum); }
    "7" -> {
      seven.add(0);
      val maxNum: Int = seven.maxOrNull() ?: 0
      seven.add(maxNum + 1);
      go(maxNum, 7, p, playerNum); }
    else -> {
        print("out of bounds");
        printBoard();
        playMove(p);
    }
  }
}

fun go(m: Int, col: Int, p: Char, pNum: Int) {
  if (m > 5) {
    print("Column full.");
    var cont = scanTemplate(pNum, p);
    if (cont == true) {
      playMove(p);
    } else if (cont == false) {
      playAgain();
    }  
  } else {
    board[5 - m][col - 1] = p;
    // clear = lambda: os.system('clear')
    // clear()
    // # print ("\n" * 100)
    var cont = scanTemplate(pNum, p)
    while (cont == true) {
      var pe = choosePlayer(p);
      playMove(pe);
      playAgain();
    }
  }
}

fun main() {
  printBoard();
  playMove(p1);
}
