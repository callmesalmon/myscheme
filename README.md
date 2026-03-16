# MyScheme
MyScheme is a Scheme interpreter that... Definitely exists, alright.
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

sudo make
```

## Run
```sh
myscm <args>
```

## Examples
By the way, MyScheme is a *teeny* bit different than... Let's say
ChezScheme (the biggest one probably being that MyScheme... Doesn't have
lambdas), so you might be a bit confused when seeing the examples. But if
you want to, they're [here](/scheme).

## Further help
Open the repl by running `myscm` with 0 arguments
and type this:
```scheme
(help)
```