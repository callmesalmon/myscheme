# MyScheme
MyScheme is a Scheme interpreter for UNIX-like systems that... Definitely exists, alright.
It gets the basics done but it doesn't include *everything*, per se.
But if you want to, you could install it, I guess. I made a
[blog post](https://callmesalmon.github.io/ramblings/2025/01/07/scheme.html) about it.

## Prerequisites
* git
* make
* clang (or gcc)
* python3

## Install
```sh
git clone https://github.com/callmesalmon/myscheme scm
cd scm

## NOTE: You may need to run with ``sudo``
## due to this script trying to access /usr/local/share/scheme
## to install the standard library
./config.sh

make # or ``sudo make install`` for
     # installation to ``/usr/local/bin
```

## Run
```sh
myscm <args>
```

## Examples
Examples found [here](/scheme/examples)

(By the way, MyScheme is a *teeny* bit different than... Let's say
ChezScheme, so you might be a bit confused when seeing the examples...)

## Further help
Open the repl by running `myscm` with 0 arguments
and type this:
```scheme
(help)
```

## Big problems
- All functions are evaluated before they are called, which causes some problems. Take:
```scheme
(define (hello-world) (writeln "Hello World"))

(hello-world)
```
This will print: ``Hello World<newline>Hello World<newline>`` because it prints hello world
when evaluated. Fun.
- User input just doesn't work in REPL