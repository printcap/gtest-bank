# Toy Bank in C++ with Google Tests

[![Build Status](https://travis-ci.org/printcap/gtest-bank.svg?branch=master)](https://travis-ci.org/printcap/gtest-bank)

A set trival of C++ classes that implement a simple bank
and a number of unit tests using [Google Test](https://github.com/google/googletest) for illustration.
(for students of OOP2 course BTI7055).

## Build Instructions

```console
$ cd <directory-with-this-README.md>
$ mkdir obj
$ cd obj
$ cmake ..
$ make
$ make test
...
24/24 Test #24: BankAccount.WithdrawInsufficientAmountThrowsException ...   Passed    0.00 sec

100% tests passed, 0 tests failed out of 24

Total Test time (real) =   0.12 sec
```
