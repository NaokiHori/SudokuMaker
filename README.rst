############
Sudoku Maker
############

|License|_ |LastCommit|_ |CI|_

.. |License| image:: https://img.shields.io/github/license/NaokiHori/SudokuMaker
.. _License: https://opensource.org/license/MIT

.. |LastCommit| image:: https://img.shields.io/github/last-commit/NaokiHori/SudokuMaker/main
.. _LastCommit: https://github.com/NaokiHori/SudokuMaker/commits/main

.. |CI| image:: https://github.com/NaokiHori/SudokuMaker/actions/workflows/ci.yml/badge.svg?branch=main
.. _CI: https://github.com/NaokiHori/SudokuMaker/actions/workflows/ci.yml

********
Overview
********

This project aims to create Sudoku puzzles with a unique solution using the backtracking algorithm.

It also contains a Sudoku solver and a tool to check the uniqueness of the solution.

**********
Dependency
**********

* C compiler

***********
Quick start
***********

#. Prepare workspace

   .. code-block:: console

      mkdir -p /path/to/your/directory
      cd       /path/to/your/directory

#. Fetch source

   .. code-block:: console

      git clone https://github.com/NaokiHori/SudokuMaker

#. Build

   .. code-block:: console

      make all

#. Run

   .. code-block:: console

      ./a.out 16384

   This gives the following output:

   .. code-block:: text

      seed: 16384
      answer:
       8  9  3  7  2  5  1  6  4
       1  7  4  9  6  3  5  2  8
       6  5  2  1  4  8  9  7  3
       9  8  7  6  3  4  2  5  1
       5  2  1  8  9  7  4  3  6
       4  3  6  5  1  2  7  8  9
       2  6  9  3  5  1  8  4  7
       7  1  5  4  8  6  3  9  2
       3  4  8  2  7  9  6  1  5
      question:
          9  3  7  2  5
                9           2
                               3
                      4     5  1
       5     1        7
       4                       9
                3     1  8  4
          1                    2
          4              6     5

   The first argument (optional) is adopted as a seed of ``srand``, which is used to change the outcome randomly.

*********
Reference
*********

* `Sudoku solving algorithms - Backtracking <https://en.wikipedia.org/wiki/Sudoku_solving_algorithms#Backtracking>`_

