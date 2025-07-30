"use strict";

var EASY_PUZZLE = "1-58-2----9--764-52--4--819-19--73-6762-83-9-----61-5---76---3-43--2-5-16--3-89--";
var MEDIUM_PUZZLE = "-3-5--8-45-42---1---8--9---79-8-61-3-----54---5------78-----7-2---7-46--61-3--5--";
var HARD_PUZZLE = "8----------36------7--9-2---5---7-------457-----1---3---1----68--85---1--9----4--";

// Set this variable to true to publicly expose otherwise private functions inside of SudokuSolver
var TESTABLE = true;

var SudokuSolver = function (testable) {
  var solver;

  // PUBLIC FUNCTIONS
  function solve(boardString) {
    var boardArray = boardString.split("");
    if (boardIsInvalid(boardArray)) {
      return false;
    }
    // If valid, performing recursion to display all the values
    return recursiveSolve(boardString);
  }

  function solveAndPrint(boardString) {
    var solvedBoard = solve(boardString);
    console.log(toString(solvedBoard.split("")));
    return solvedBoard;
  }

  // PRIVATE FUNCTIONS
  // If user-entered values is a valid one, replacing the table cell by that value
  function recursiveSolve(boardString) {
    var boardArray = boardString.split("");
    if (boardIsSolved(boardArray)) {
      return boardArray.join("");
    }

    // Extracting all the possible values and indices to validate the value in a particular cell
    var cellPossibilities = getNextCellAndPossibilities(boardArray);
    var nextUnsolvedCellIndex = cellPossibilities.index;
    var possibilities = cellPossibilities.choices;
    // To find the values to be filled into a particular cell
    for (var i = 0; i < possibilities.length; i++) {
      boardArray[nextUnsolvedCellIndex] = possibilities[i];
      var solvedBoard = recursiveSolve(boardArray.join(""));
      if (solvedBoard) {
        return solvedBoard;
      }
    }
    return false;
  }

  function boardIsInvalid(boardArray) {
    return !boardIsValid(boardArray);
  }
  
  // To check for all the valid rows and columns and hence an entire board
  function boardIsValid(boardArray) {
    return allRowsValid(boardArray) && allColumnsValid(boardArray) && allBoxesValid(boardArray);
  }
  // To check whether all the values in the board are filled or not
  // '-' in the string would indicate that some values are not filled caused due to conflicting values(invalid)
  function boardIsSolved(boardArray) {
    for (var i = 0; i < boardArray.length; i++) {
      if (boardArray[i] === "-") {
        return false;
      }
    }
    return true;
  } 

  //  '-' in the string will indicate the missing values. So, we need to find out the values to replace '-'.
  //  For this, we specify all the possible values (1-9) and extract all the values already filled in the table
  //  at an apppropriate cell intersections.
  //  The extracted intersection values are compared with all the possible values to find out which value is missing 
  //  by using filter function. 
  function getNextCellAndPossibilities(boardArray) {
    for (var i = 0; i < boardArray.length; i++) {
      if (boardArray[i] === "-") {
        var existingValues = getAllIntersections(boardArray, i);
        var choices = ["1", "2", "3", "4", "5", "6", "7", "8", "9"].filter(function (num) {
          return existingValues.indexOf(num) < 0; 
        // This return statement returns true if we can find out a missing value to be filled into the cell.
        });
        return { index: i, choices: choices }; //dictionary
      }
    }
  }
  // To retrieve all the possible values corresponding a particular row, column and box.
  function getAllIntersections(boardArray, i) {
    return getRow(boardArray, i).concat(getColumn(boardArray, i)).concat(getBox(boardArray, i));
  }
  
  // To return all the values corresponding to individual rows by using map function.
  // Here we specify the starting indices of each and every row.
  function allRowsValid(boardArray) {
    return [0, 9, 18, 27, 36, 45, 54, 63, 72].map(function (i) {
      return getRow(boardArray, i);
    }).reduce(function (validity, row) {
      return collectionIsValid(row) && validity;
    }, true);
  }

  // To retrieve one element at a time from an entire row and returning after completing one row 
  function getRow(boardArray, i) {
    var startingEl = Math.floor(i / 9) * 9;
    // Calculating the indices of next subsequent rows.
    return boardArray.slice(startingEl, startingEl + 9);
  }

  // To return all the values corresponding to individual columns by using map function.
  // Here we specify the starting indices of each and every column.
  function allColumnsValid(boardArray) {
    return [0, 1, 2, 3, 4, 5, 6, 7, 8].map(function (i) {
      return getColumn(boardArray, i);
    }).reduce(function (validity, row) {
      return collectionIsValid(row) && validity;
    }, true);
  }

  // To retrieve one element at a time from an entire column and returning after completing one column 
  function getColumn(boardArray, i) {
    var startingEl = Math.floor(i % 9);
    return [0, 1, 2, 3, 4, 5, 6, 7, 8].map(function (num) {
      // Calculating the indices of next subsequent columns.
      return boardArray[startingEl + num * 9];
    });
  }

  // To return all the values corresponding to individual boxes by using map function.
  // Here we specify the starting indices of each and every box.
  function allBoxesValid(boardArray) {
    return [0, 3, 6, 27, 30, 33, 54, 57, 60].map(function (i) {
      return getBox(boardArray, i);
    }).reduce(function (validity, row) {
      return collectionIsValid(row) && validity;
    }, true);
  }

  // To retrieve one element at a time from an entire box and returning after completing one box
  function getBox(boardArray, i) {
    var boxCol = Math.floor(i / 3) % 3;
    var boxRow = Math.floor(i / 27);
    var startingIndex = boxCol * 3 + boxRow * 27;
    return [0, 1, 2, 9, 10, 11, 18, 19, 20].map(function (num) {
      // Calculating the indices of next subsequent boxes.
      return boardArray[startingIndex + num];
    });
  }
  // Here we indicate that each cell is visited by its value as '1' in the numCounts, as soon as it is filled in order to
  // diffrentiate it from '-'.
  function collectionIsValid(collection) {
    var numCounts = {};
    for(var i = 0; i < collection.length; i++) {
      if (collection[i] != "-") {
        if (numCounts[collection[i]] === undefined) {
          numCounts[collection[i]] = 1;
        } else {
          return false;
        }
      }
    }
    return true;
  }
  // This function is used to fill the tables with values after performing the validation using above functions.
  function toString(boardArray) {
    return [0, 9, 18, 27, 36, 45, 54, 63, 72].map(function (i) {
      return getRow(boardArray, i).join(" ");
    }).join("\n");
  }

  if (testable) {
    // These methods will be exposed publicly when testing is on.
    solver = { 
      solve: solve,
      solveAndPrint: solveAndPrint,
      recursiveSolve: recursiveSolve,
      boardIsInvalid: boardIsInvalid,
      boardIsValid: boardIsValid,
      boardIsSolved: boardIsSolved,
      getNextCellAndPossibilities: getNextCellAndPossibilities,
      getAllIntersections: getAllIntersections,
      allRowsValid: allRowsValid,
      getRow: getRow,
      allColumnsValid: allColumnsValid,
      getColumn: getColumn,
      allBoxesValid: allBoxesValid,
      getBox: getBox,
      collectionIsValid: collectionIsValid,
      toString: toString };
  } else {
    // These will be the only public methods when testing is off.
    solver = { solve: solve,
      solveAndPrint: solveAndPrint };
  }

  return solver;
}(TESTABLE);
