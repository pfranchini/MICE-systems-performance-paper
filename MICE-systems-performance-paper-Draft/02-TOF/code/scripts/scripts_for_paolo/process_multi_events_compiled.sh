#!/bin/bash

NSPILLS=0
if [[ -n $3 ]] ; then
    NSPILLS=$3
fi

echo "mauslibs();
.x  scripts/process_multi_events.C+ (\"$1\", \"$2\", $NSPILLS)" | root -l -b

#root -l -b -q "scripts/TOFcheck/check_tof_rec_evts.C+ (\"$1\",$NSPILLS)"
