DATADIR=data
OUTPUTDIR=output_data/
LIST="10204 10205 10246 10248 10249 10253 10254 10256 10258 10259 10260"


for RUN in $LIST ; do
    echo "Run $RUN" ; date
    { date
      install -d $OUTPUTDIR/$RUN
      bash scripts/process_multi_events_compiled.sh \
	   "$DATADIR/${RUN}/${RUN}_recon.root" \
	   output_data/${RUN}/${RUN}_v3.1.2_wSlabs_wDigits_new_tof_calib_4ns.root
      date ; } &> logs/processing_v3.1.2_newcalib_4ns_${RUN}.log
done
