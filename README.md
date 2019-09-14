# Brainfuck ![issues](https://img.shields.io/github/issues/antony-jr/updatedeployqt.svg?style=flat-square) ![forks](https://img.shields.io/github/forks/antony-jr/brainfuck.svg?style=flat-square) ![stars](https://img.shields.io/github/stars/antony-jr/brainfuck.svg?style=flat-square) ![license](https://img.shields.io/github/license/TheFutureShell/updatedeployqt.svg?style=flat-square)


This is a very simple interpreter for **brainfuck** with a python interpreter like interface.
This can execute a brainfuck program directly from a file or interpret just like python.
**This was made just for fun but a little bit optimized, I will be adding more optimizations 
in the future to make this even faster.**

# Installation

### Linux 

You don't need to compile this from source, simply download the latest AppImage from releases and make it
executable and you are ready to go.

```
 $ chmod +x brainfuck-continuous-x86_64.AppImage
 $ ./brainfuck-continuous-x86_64.AppImage # starts the interpreter
```


# Usage

*You can use this interpreter just like how you use the python interpreter, if you give a file, it simply 
executes it or if no arguments are given then it acts as a interpreter very similar to python interpreter.*

**You can also use shebangs if you want execute brainfuck programs directly from the terminal.** 

Take this program for example.

```
#!/usr/bin/env brainfuck-continuous-x86_64.AppImage
>++++++++[-<+++++++++>]<.>>+>-[+]++
>++>+++[>[->+++<<+++>]<<]>-----.>->
+++..+++.>-.<<+[>[+>+]>>]<---------
-----.>>.+++.------.--------.>+.>+.
```

Execute it like this...

```
 $ chmod +x Hello.b
 $ PATH=/path/to/brainfuck-appimage/ ./Hello.b
 $ # or, this if you have the interpreter in your path
 $ ./Hello.b
```


# License

BSD 3-Clause License

Copyright (c) 2019, Antony Jr. 
