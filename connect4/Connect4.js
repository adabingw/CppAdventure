// node.js

require('events').EventEmitter.prototype._maxListeners = 100;
require('events').defaultMaxListeners = 100;

process.on('warning', function (err) {
  if ( 'MaxListenersExceededWarning' == err.name ) {
    console.log('hehe i\'m in trouble');
    // write to log function
    process.exit(1); // its up to you what then in my case script was hang
  }
}); // for more listeners

var ptemplate1 = [" ", " ", " ", " ", " ", " ", " ", " "];
var ptemplate2 = [" ", " ", " ", " ", " ", " ", " ", " "];
var ptemplate3 = [" ", " ", " ", " ", " ", " ", " ", " "];
var ptemplate4 = [" ", " ", " ", " ", " ", " ", " ", " "];
var ptemplate5 = [" ", " ", " ", " ", " ", " ", " ", " "];
var ptemplate6 = [" ", " ", " ", " ", " ", " ", " ", " "];
var ptemplate = [ptemplate1, ptemplate2, ptemplate3, ptemplate4, ptemplate5, ptemplate6]

var arr = [0, 0, 0, 0, 0, 0, 0];

var p1 = 'x';
var p2 = 'o';

initialize(); // prints the empty board
playMove(p1);

function initialize() {
    var h = " ";
    for (var i = 0; i < 7; i++) {
        h = h + (i + 1) + "  ";
    }
    console.log(h);
    for (var j = 0; j < 6; j++) {
      var s = "";
        for (var i = 0; i < 8; i++) {
            s += "| " + ptemplate[j][i];
        } console.log(s);
    }
    console.log("``````````````````````");
}

function scanTemplate(playerNum, p) {
    var notFull = scanBoard();
    var fourInARow = scanRow(p);
    var fourInACol = scanColumn(p);
    var fourInADiag = scanDiag(p);
    if (notFull === true && fourInARow === false && fourInACol === false && fourInADiag === false) { // no wins / not full
        initialize();
        return true;
    } else if (notFull == false) {
        initialize();
        console.log("Board is full");
        return false;
    } else if (fourInARow == true || fourInACol == true || fourInADiag == true) {
        console.clear();
        initialize();
        console.log("Player " + playerNum + " has won.");
        return false;
    }
}

function scanBoard() {
    var numEmpty = 0;
    for (var i = 0; i < 6; i++) {
        for (var j = 0; j < 7; j++) {
            if (ptemplate[i][j] == " ") {
                numEmpty++;
            }
        }
    }
    if (numEmpty > 0) {
        return true;
    } else if (numEmpty == 0) {
        return false;
    }
}

function scanRow(p) {
  for (var y = 0; y < 7; y++) {
    for (var x = 0; x < 3; x++) {
      if (ptemplate[x][y] == p && ptemplate[x+1][y] == p && ptemplate[x+2][y] == p && ptemplate[x+3][y] == p) {
        return true;
      }
    }
  }
  return false;
}

function scanColumn(p) {
    for (var y = 0; y < 4; y++) {
      for (var x = 0; x < 6; x++) {
        if (ptemplate[x][y] == p && ptemplate[x][y+1] == p && ptemplate[x][y+2] == p && ptemplate[x][y+3] == p) {
          return true;
        }
      }
    }
    return false;
}

function scanDiag(p) {
  for (var y = 3; y < 7; y++) {
    for (var x = 0; x < 3; x++) {
      if (ptemplate[x][y] == p && ptemplate[x+1][y-1] == p && ptemplate[x+2][y-2] == p && ptemplate[x+3][y-3] == p) {
        return true;
      }
    }
  }

  for (var y = 0; y < 4; y++) {
    for (var x = 0; x < 3; x++) {
      if (ptemplate[x][y] == p && ptemplate[x+1][y+1] == p && ptemplate[x+2][y+2] == p && ptemplate[x+3][y+3] == p) {
        return true;
      }
    }
  }
  return false;
}

function choosePlayer(p) {
    if (p === p1) {
        playMove(p2);
    } else if (p === p2) {
        playMove(p1);
    }
}

function playMove(p) {
    var playerNum;

    switch(p) {
        case 'x':
            playerNum = "one";
            break;
        case 'o':
            playerNum = "two";
            break;
    }

    // console.log("Player " + playerNum + ", choose column to play.");

    const readline = require('readline').createInterface({
      input: process.stdin,
      output: process.stdout,
      terminal: false
    });

    readline.question("Player " + playerNum + ", choose column to play.\n", name => {
      num = Number(name);
      if (0 < num && num < 8) {
        arr[num-1]++;
        go(arr[num-1], num, p, playerNum);
      } else {
          console.log("ERROR: invalid column number.");
          console.clear();
          initialize();
          playMove(p);
      }
      // choices(name, p, playerNum);
    //   readline.close();
    });
}

function go(m, col, p, pNum) {
    if (m > 6){
        console.log("Column full.");
        console.clear();
        var cont = scanTemplate(pNum, p); // checks if board is full/there's a win
        if (cont === true){
            playMove(p);
        } else if (cont === false) {
            exit(0);
        }
    } else {
        ptemplate[6 - m][col-1] = p;
        var cont = scanTemplate(pNum, p);
        if (cont === true){
            console.clear();
            initialize();
            choosePlayer(p); // next player
        } else if (cont === false) {
            process.exit(1);
        } // new board will be printed
    }
}
