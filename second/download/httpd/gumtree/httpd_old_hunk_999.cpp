                    printf("ERROR: The median and mean for " what " are more than twice the standard\n" \
                           "       deviation apart. These results are NOT reliable.\n"); \
                else if (d > sd ) \
                    printf("WARNING: The median and mean for " what " are not within a normal deviation\n" \
                           "        These results are probably not that reliable.\n"); \
            }
        SANE("the initial connection time", meancon, mediancon, sdcon);
        SANE("the processing time", meand, mediand, sdd);
        SANE("the waiting time", meanwait, medianwait, sdwait);
        SANE("the total time", meantot, mediantot, sdtot);
	}
	else {
	    printf("              min   avg   max\n");
#define CONF_FMT_STRING "%5" APR_TIME_T_FMT " %5" APR_TIME_T_FMT "%5" APR_TIME_T_FMT "\n"
	    printf("Connect:    " CONF_FMT_STRING, 
                mincon, meancon, maxcon);
	    printf("Processing: " CONF_FMT_STRING, 
                mintot - mincon, meantot - meancon,  maxtot - maxcon);
	    printf("Total:      " CONF_FMT_STRING, 
                mintot, meantot, maxtot);
#undef CONF_FMT_STRING
	}


	/* Sorted on total connect times */
	if (percentile && (requests > 1)) {
	    printf("\nPercentage of the requests served within a certain time (ms)\n");
	    for (i = 0; i < sizeof(percs) / sizeof(int); i++)
		if (percs[i] <= 0)
		    printf(" 0%%  <0> (never)\n");
                else if (percs[i] >= 100)
		    printf(" 100%%  %5" APR_TIME_T_FMT " (longest request)\n",
                           stats[requests - 1].time);
                else
		    printf("  %d%%  %5" APR_TIME_T_FMT "\n", percs[i], 
                           stats[(int) (requests * percs[i] / 100)].time);
	}
	if (csvperc) {
	    FILE *out = fopen(csvperc, "w");
	    int i;
	    if (!out) {
		perror("Cannot open CSV output file");
