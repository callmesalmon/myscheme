# MyScheme
MyScheme is a Scheme interpreter that... Definitely exists, alright.
It gets the basics done but it doesn't include *everything*, per se.
But if you want to, you could install it, I guess.

## Prerequisites
* git
* make
* g++

## Install
```console
git clone https://github.com/ElisStaaf/myscheme scm
cd scm
sudo make
```
Note: To run with a C++ compiler
other than g++, run make like this:
```console
make CC=<compiler>
```

## Run
```console
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
(load "scheme/help.scm")
```
