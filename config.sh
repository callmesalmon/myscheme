#!/usr/bin/sh

STDLIB_DIR=/usr/local/share/scheme/
STDLIB_FILE=myscheme-stdlib.scm

if [ ! -d "$STDLIB_DIR" ]; then
    mkdir "$STDLIB_DIR"
fi

if [ ! -f "$STDLIB_DIR/$STDLIB_FILE" ]; then
    cp scheme/std.scm $STDLIB_DIR/$STDLIB_FILE
fi