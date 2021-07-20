#!/bin/bash

# NSPILLS=0
# if [[ -n $2 ]] ; then
#     NSPILLS=$2
# fi

root -l -b -q "$(dirname $0)/process.C+ (\"$1\", \"$2\")"
