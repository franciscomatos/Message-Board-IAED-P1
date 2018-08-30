# Message Board

This project consists on a program for managing and monitoring a message board. More specifically, the user interaction with the program occurs through a set of lines composed by a letter (the command itself) and eventually one or two arguments.

##Commands Available

Command | Description
------------ | -------------
A | Adds a message.
L | Shows all the messages.
U | Shows all the messages added by a certain user.
O | Shows the longest messages.
T | Shows the most active user.
S | Shows all the messages in alphabetical order.
C | Displays the number of occurrences of a given word.
X | Closes the program.

## Getting Started

###Prerequisites

You will need the gcc compiler installed in your machine.

###Compiling

Download the .zip and compile the 'main.c' file using the following options:

```
$ gcc -Wall -o proj1 main.c

```
which should create the executable file 'proj1'.


##Running the Tests

Make sure the executable file is in the same directory as the input files contained in 'Exemplos'.
The program should be executed in the following way:

```
$ ./proj1 < teste01.in > teste01.myout
```

Afterwards you can compare your output with the foressen output using:

```
$ diff teste01.out teste01.myout
```

## Authors

* Francisco Matos

##Evaluation

17/20
