#!/bin/bash

R=$1
G=$2
B=$3
MAX_VAL=255

R_TRANS=$(calc $R / $MAX_VAL | sed -e 's/[ \t]*//' )
G_TRANS=$(calc $G / $MAX_VAL | sed -e 's/[ \t]*//' )
B_TRANS=$(calc $B / $MAX_VAL | sed -e 's/[ \t]*//' )

echo "Vectorul este '('$R_TRANS, $G_TRANS, $B_TRANS')'"