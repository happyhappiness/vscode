static void output_results(void)
{
    apr_interval_time_t timetakenusec;
    float timetaken;

    endtime = apr_time_now();
    timetakenusec = endtime - start;
    timetaken = ((float)apr_time_sec(timetakenusec)) +
        ((float)apr_time_usec(timetakenusec)) / 1000000.0F;
    
    printf("\n\n");
    printf("Server Software:        %s\n", servername);
    printf("Server Hostname:        %s\n", hostname);
    printf("Server Port:            %hd\n", port);
    printf("\n");
    printf("Document Path:          %s\n", path);
    printf("Document Length:        %" APR_SIZE_T_FMT " bytes\n", doclen);
    printf("\n");
    printf("Concurrency Level:      %d\n", concurrency);
    printf("Time taken for tests:   %ld.%03ld seconds\n",
           (long) apr_time_sec(timetakenusec),
           (long) apr_time_usec(timetakenusec));
    printf("Complete requests:      %ld\n", done);
    printf("Failed requests:        %ld\n", bad);
    if (bad)
	printf("   (Connect: %d, Length: %d, Exceptions: %d)\n",
	       err_conn, err_length, err_except);
    printf("Write errors:           %ld\n", epipe);
    if (err_response)
	printf("Non-2xx responses:      %d\n", err_response);
    if (keepalive)
	printf("Keep-Alive requests:    %ld\n", doneka);
    printf("Total transferred:      %ld bytes\n", totalread);
    if (posting > 0)
	printf("Total POSTed:           %ld\n", totalposted);
    printf("HTML transferred:       %ld bytes\n", totalbread);

    /* avoid divide by zero */
    if (timetaken) {
	printf("Requests per second:    %.2f [#/sec] (mean)\n", 
               (float) (done / timetaken));
	printf("Time per request:       %.3f [ms] (mean)\n", 
               (float) (1000 * concurrency * timetaken / done));
	printf("Time per request:       %.3f [ms] (mean, across all concurrent requests)\n",
	       (float) (1000 * timetaken / done));
	printf("Transfer rate:          %.2f [Kbytes/sec] received\n",
	       (float) (totalread / 1024 / timetaken));
	if (posting > 0) {
	    printf("                        %.2f kb/s sent\n",
		   (float) (totalposted / timetaken / 1024));
	    printf("                        %.2f kb/s total\n",
		   (float) ((totalread + totalposted) / timetaken / 1024));
	}
    }

    if (requests) {
	/* work out connection times */
	long i;
	apr_time_t totalcon = 0, total = 0, totald = 0, totalwait = 0;
        apr_interval_time_t mincon = AB_MAX, mintot = AB_MAX, mind = AB_MAX, 
                            minwait = AB_MAX;
        apr_interval_time_t maxcon = 0, maxtot = 0, maxd = 0, maxwait = 0;
        apr_interval_time_t meancon = 0, meantot = 0, meand = 0, meanwait = 0;
        double sdtot = 0, sdcon = 0, sdd = 0, sdwait = 0;

	for (i = 0; i < requests; i++) {
	    struct data s = stats[i];
	    mincon = ap_min(mincon, s.ctime);
	    mintot = ap_min(mintot, s.time);
	    mind = ap_min(mind, s.time - s.ctime);
	    minwait = ap_min(minwait, s.waittime);

	    maxcon = ap_max(maxcon, s.ctime);
	    maxtot = ap_max(maxtot, s.time);
	    maxd = ap_max(maxd, s.time - s.ctime);
	    maxwait = ap_max(maxwait, s.waittime);

	    totalcon += s.ctime;
	    total += s.time;
	    totald += s.time - s.ctime;
	    totalwait += s.waittime;
	}
	totalcon /= requests;
	total /= requests;
	totald /= requests;
	totalwait /= requests;

	for (i = 0; i < requests; i++) {
	    struct data s = stats[i];
            double a;
            a = ((double)s.time - total);
            sdtot += a * a;
	    a = ((double)s.ctime - totalcon);
	    sdcon += a * a;
	    a = ((double)s.time - (double)s.ctime - totald);
	    sdd += a * a;
	    a = ((double)s.waittime - totalwait);
	    sdwait += a * a;
	}

	sdtot = (requests > 1) ? sqrt(sdtot / (requests - 1)) : 0;
	sdcon = (requests > 1) ? sqrt(sdcon / (requests - 1)) : 0;
	sdd = (requests > 1) ? sqrt(sdd / (requests - 1)) : 0;
	sdwait = (requests > 1) ? sqrt(sdwait / (requests - 1)) : 0;

	if (gnuplot) {
	    FILE *out = fopen(gnuplot, "w");
	    long i;
	    apr_time_t sttime;
	    char tmstring[1024];/* XXXX */
	    if (!out) {
		perror("Cannot open gnuplot output file");
		exit(1);
	    }
	    fprintf(out, "starttime\tseconds\tctime\tdtime\tttime\twait\n");
	    for (i = 0; i < requests; i++) {
                apr_time_t diff = stats[i].time - stats[i].ctime;

		sttime = stats[i].starttime;
		(void) apr_ctime(tmstring, sttime);
		fprintf(out, "%s\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\n",
			tmstring,
			sttime,
			stats[i].ctime,
			diff,
			stats[i].time,
			stats[i].waittime);
	    }
	    fclose(out);
	}
    /*
     * XXX: what is better; this hideous cast of the compradre function; or
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
		exit(1);
	    }
	    fprintf(out, "" "Percentage served" "," "Time in ms" "\n");
	    for (i = 0; i < 100; i++) {
		apr_time_t t;
		if (i == 0)
		    t = stats[0].time;
		else if (i == 100)
		    t = stats[requests - 1].time;
		else
		    t = stats[(int) (0.5 + requests * i / 100.0)].time;
		fprintf(out, "%d,%e\n", i, (double)t);
	    }
	    fclose(out);
        }

    }
}