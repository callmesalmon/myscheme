# MyScheme
MyScheme is a Scheme interpreter that... Definitely exists, alright.
It gets the basics done but it doesn't include *everything*, per se.
But if you want to, you could install it, I guess.

## Prerequisites
* git
* make
* g++

## Install
```sh
git clone https://github.com/ElisStaaf/myscheme scm
cd scm

./configure # Prebuild
sudo make   # To build

# NOTE: To exclude different functions
#       of the interpreter, do:
./configure --exclude debug # To exclude debugging
./configure --exclude std   # To exclude stdlib loading

# NOTE: To compile with only repl, do:
./configure --repl

# NOTE: To compile with clang or change
#       the cflags, do:
./configure --clang          # To compile with clang
./configure --cflags <flags> # To change cflags
```
Note: To run with a C++ compiler
other than g++, run make like this:
```sh
make CC=<compiler>
```

## Run
```sh
myscm <args>
```

## Examples
By the way, MyScheme is a *teeny* bit different than... Let's say
ChezScheme, so you might be a bit confused when seeing the
examples. But if you want to, they're [here](/scheme).

## Further help
Open the repl in the source directory 
by running `myscm` with 0 arguments
and type this:
```scm
(help)
```