#!/usr/bin/sh

STDLIB_DIR=/usr/local/share/scheme/
STDLIB_FILE=myscheme-stdlib.scm

if [ ! -d "$STDLIB_DIR" ]; then
    mkdir "$STDLIB_DIR"
fi

cp scheme/stdlib.scm $STDLIB_DIR/$STDLIB_FILE