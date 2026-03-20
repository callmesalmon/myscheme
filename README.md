# MyScheme
MyScheme is a half-baked scheme implementation written in C (not C++, the C++ compiler is just a bit more lenient
so we use it as a clever workaround). It is functioning enough to write a [calculator](/scheme/examples/6-calc.scm)
in it, at the very least. At this moment it will not compile on W\*ndows.

## Prerequisites
* make
* clang

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
Examples found [here](/scheme/examples).

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
- If literally ANYTHING out-of-the-ordinary happens, it WILL segfault.
- ``if`` statements are broken beyond belief.