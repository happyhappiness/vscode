     * the four warnings during compile ? dirkx just does not know and
     * hates both/
     */
	qsort(stats, requests, sizeof(struct data),
	      (int (*) (const void *, const void *)) compradre);
	if ((requests > 1) && (requests % 2))
	    meancon = (stats[requests / 2].ctime + stats[requests / 2 + 1].ctime) / 2;
	else
	    meancon = stats[requests / 2].ctime;

	qsort(stats, requests, sizeof(struct data),
	      (int (*) (const void *, const void *)) compri);
	if ((requests > 1) && (requests % 2))
	    meand = (stats[requests / 2].time + stats[requests / 2 + 1].time \
	    -stats[requests / 2].ctime - stats[requests / 2 + 1].ctime) / 2;
	else
	    meand = stats[requests / 2].time - stats[requests / 2].ctime;

	qsort(stats, requests, sizeof(struct data),
	      (int (*) (const void *, const void *)) compwait);
	if ((requests > 1) && (requests % 2))
	    meanwait = (stats[requests / 2].waittime + stats[requests / 2 + 1].waittime) / 2;
	else
	    meanwait = stats[requests / 2].waittime;

	qsort(stats, requests, sizeof(struct data),
	      (int (*) (const void *, const void *)) comprando);
	if ((requests > 1) && (requests % 2))
	    meantot = (stats[requests / 2].time + stats[requests / 2 + 1].time) / 2;
	else
	    meantot = stats[requests / 2].time;

	printf("\nConnection Times (ms)\n");

	if (confidence) {
#define CONF_FMT_STRING "%5" APR_TIME_T_FMT " %4d %5.1f %6" APR_TIME_T_FMT " %7" APR_TIME_T_FMT "\n"
	    printf("              min  mean[+/-sd] median   max\n");
	    printf("Connect:    " CONF_FMT_STRING, 
                   mincon, (int) (totalcon + 0.5), sdcon, meancon, maxcon);
	    printf("Processing: " CONF_FMT_STRING,
		   mind, (int) (totald + 0.5), sdd, meand, maxd);
	    printf("Waiting:    " CONF_FMT_STRING,
	           minwait, (int) (totalwait + 0.5), sdwait, meanwait, maxwait);
	    printf("Total:      " CONF_FMT_STRING,
		   mintot, (int) (total + 0.5), sdtot, meantot, maxtot);
#undef CONF_FMT_STRING

#define     SANE(what,avg,mean,sd) \
              { \
                double d = (double)avg - mean; \
                if (d < 0) d = -d; \
                if (d > 2 * sd ) \
                    printf("ERROR: The median and mean for " what " are more than twice the standard\n" \
                           "       deviation apart. These results are NOT reliable.\n"); \
                else if (d > sd ) \
                    printf("WARNING: The median and mean for " what " are not within a normal deviation\n" \
                           "        These results are probably not that reliable.\n"); \
            }
	    SANE("the initial connection time", totalcon, meancon, sdcon);
	    SANE("the processing time", totald, meand, sdd);
	    SANE("the waiting time", totalwait, meanwait, sdwait);
	    SANE("the total time", total, meantot, sdtot);
	}
	else {
	    printf("              min   avg   max\n");
#define CONF_FMT_STRING "%5" APR_TIME_T_FMT " %5" APR_TIME_T_FMT "%5" APR_TIME_T_FMT "\n"
	    printf("Connect:    " CONF_FMT_STRING, 
                   mincon, totalcon / requests, maxcon);
	    printf("Processing: " CONF_FMT_STRING, mintot - mincon, 
                   (total / requests) - (totalcon / requests), 
                   maxtot - maxcon);
	    printf("Total:      " CONF_FMT_STRING, 
                   mintot, total / requests, maxtot);
#undef CONF_FMT_STRING
	}


	/* Sorted on total connect times */
	if (percentile && (requests > 1)) {
