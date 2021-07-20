DATADIR=data
OUTPUTDIR=output_data/
LIST="08676 08677 08678 08679 08680 08681 08682 08683 08684 08685 08686 08687 08688 08689"
VERSION=v3.2.0

for RUN in $LIST ; do
    echo "Run $RUN" ; date
    { date
      install -d $OUTPUTDIR/$RUN
      bash scripts/process_multi_events_compiled.sh \
	   "$DATADIR/${RUN}/${RUN}_recon.root" \
	   output_data/${RUN}/${RUN}_${VERSION}_wSlabs_wDigits_new_tof_calib_4ns.root
      date ; } &> logs/processing_${VERSION}_newcalib_4ns_${RUN}.log
done
