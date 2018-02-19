# Project Darwin

## Description

This is a simple population evolution simulator. A given start population goes through a number of generations. After all changes we can see the finish population. People try to fit in the environment. Some of them die, some of them clone, some of them reproduce. Every event depends on the given environment.

This project is a documentation of my learning process about dynamic data structures. It is also an introduction to classes and object oriented programming.

If you can see some drama, some obvious bug or some bad habit tell me! I would be very glad if you do. It is all about learning.

## Example of start population

```
32 421 42 321 42 32 5 49
41 8 90 0 928 32
312
421 0 28 32 42 8 982 2
```

## How to build and run it?

1. Clone this repository.
2. `cd app`
3. `make`
4. `./main -i ../dat/test19.txt -o ../dat/output.txt -w 0.68 -r 0.89 -p 11 -k 8`

The last line is an example of the *run* command.

## Things to implement in the future:
- [ ] Make it full object oriented.
- [ ] Implement some new function as: 
  - [ ] noahsArk - Kills everyone except two the best adapted people.
  - [ ] plague - Increases death and clone factors killing most people and making multiplication almost impossible.
  - [ ] mutation - Randomly changes some part of chromosomes without hybridization.
  - [ ] climatChange - Changes the fitFunction and thus environment.
