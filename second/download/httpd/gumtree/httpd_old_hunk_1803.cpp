#endif
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
        apr_time_t meancon, meantot, meand, meanwait;
        apr_interval_time_t mincon = AB_MAX, mintot = AB_MAX, mind = AB_MAX,
                            minwait = AB_MAX;
        apr_interval_time_t maxcon = 0, maxtot = 0, maxd = 0, maxwait = 0;
        apr_interval_time_t mediancon = 0, mediantot = 0, mediand = 0, medianwait = 0;
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
        meancon = totalcon / requests;
        meantot = total / requests;
        meand = totald / requests;
        meanwait = totalwait / requests;

        /* calculating the sample variance: the sum of the squared deviations, divided by n-1 */
        for (i = 0; i < requests; i++) {
            struct data s = stats[i];
            double a;
            a = ((double)s.time - meantot);
            sdtot += a * a;
            a = ((double)s.ctime - meancon);
            sdcon += a * a;
            a = ((double)s.time - (double)s.ctime - meand);
            sdd += a * a;
            a = ((double)s.waittime - meanwait);
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
            mediancon = (stats[requests / 2].ctime + stats[requests / 2 + 1].ctime) / 2;
        else
            mediancon = stats[requests / 2].ctime;

        qsort(stats, requests, sizeof(struct data),
              (int (*) (const void *, const void *)) compri);
        if ((requests > 1) && (requests % 2))
            mediand = (stats[requests / 2].time + stats[requests / 2 + 1].time \
            -stats[requests / 2].ctime - stats[requests / 2 + 1].ctime) / 2;
        else
            mediand = stats[requests / 2].time - stats[requests / 2].ctime;

        qsort(stats, requests, sizeof(struct data),
              (int (*) (const void *, const void *)) compwait);
        if ((requests > 1) && (requests % 2))
            medianwait = (stats[requests / 2].waittime + stats[requests / 2 + 1].waittime) / 2;
        else
            medianwait = stats[requests / 2].waittime;

        qsort(stats, requests, sizeof(struct data),
              (int (*) (const void *, const void *)) comprando);
        if ((requests > 1) && (requests % 2))
            mediantot = (stats[requests / 2].time + stats[requests / 2 + 1].time) / 2;
        else
            mediantot = stats[requests / 2].time;

        printf("\nConnection Times (ms)\n");

        if (confidence) {
#define CONF_FMT_STRING "%5" APR_TIME_T_FMT " %4d %5.1f %6" APR_TIME_T_FMT " %7" APR_TIME_T_FMT "\n"
            printf("              min  mean[+/-sd] median   max\n");
            printf("Connect:    " CONF_FMT_STRING,
                       mincon, (int) (meancon + 0.5), sdcon, mediancon, maxcon);
            printf("Processing: " CONF_FMT_STRING,
               mind, (int) (meand + 0.5), sdd, mediand, maxd);
            printf("Waiting:    " CONF_FMT_STRING,
                   minwait, (int) (meanwait + 0.5), sdwait, medianwait, maxwait);
            printf("Total:      " CONF_FMT_STRING,
               mintot, (int) (meantot + 0.5), sdtot, mediantot, maxtot);
#undef CONF_FMT_STRING

#define     SANE(what,mean,median,sd) \
              { \
                double d = (double)mean - median; \
                if (d < 0) d = -d; \
