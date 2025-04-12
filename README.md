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

./configure # Prebuild
sudo make   # To build

# NOTE: To exclude different functions
#       of the interpreter, do:
./configure --exclude debug # To exclude debugging
./configure --exclude std   # To exclude stdlib loading

# NOTE: To compile with only repl, do:
./configure --repl

# NOTE: To compile with gcc or change
#       the cflags, do:
./configure --gcc            # To compile with gcc
./configure --cflags <flags> # To change cflags
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
Open the repl by running `myscm` with 0 arguments
and type this:
```scheme
(help)
```