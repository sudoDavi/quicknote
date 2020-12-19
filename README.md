# quicknote

## Table of Contents
+ [About](#about)
+ [Getting Started](#getting_started)
+ [Usage](#usage)
+ [Contributing](#contributing)

## About <a name = "about"></a>

A simple software to save notes to a file and read them.
You can also create different note files to save your notes.

## Getting Started <a name = "getting_started"></a>

Just clone the repository and fire away.

### Prerequisites

You'll need a modern C++ compiler, the code is ISO complaint so any compiler should do the trick
as long as it is C++17 capable.

### Installing

**A build system is in the works.**

The way you'll use the compiler will vary from compiler to compiler, but to build it
all you need is to compile the three cpp files using the C++17 standard.

Here is the g++ example:
```
g++ quicknote.cpp notesfile.cpp configparser.cpp -pedantic-errors -Wall -Wextra -std=c++17 -ggdb -o qn
```

## Usage <a name = "usage"></a>

To use the program, all you need is to pass in what you want when calling it.

Here's an example of how to add a new note:
```
qn All this text is going to be saved into a note
```
To read all the notes saved into the currently used note file:
```
qn -r
```
## Contributing <a name = "contributing"></a>

1. Fork it (https://github.com/sudoDavi/quicknote/fork)
1. Create your feature branch (git checkout -b feature)
1. Commit your changes (git commit -am 'Add some feature')
1. Push to the branch (git push origin feature)
1. Create a new Pull Request
