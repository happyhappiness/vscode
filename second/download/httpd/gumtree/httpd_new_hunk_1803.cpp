#endif
    printf("\n");
    printf("Document Path:          %s\n", path);
    printf("Document Length:        %" APR_SIZE_T_FMT " bytes\n", doclen);
    printf("\n");
    printf("Concurrency Level:      %d\n", concurrency);
    printf("Time taken for tests:   %.3f seconds\n", timetaken);
    printf("Complete requests:      %d\n", done);
    printf("Failed requests:        %d\n", bad);
    if (bad)
        printf("   (Connect: %d, Receive: %d, Length: %d, Exceptions: %d)\n",
            err_conn, err_recv, err_length, err_except);
    printf("Write errors:           %d\n", epipe);
    if (err_response)
        printf("Non-2xx responses:      %d\n", err_response);
    if (keepalive)
        printf("Keep-Alive requests:    %d\n", doneka);
    printf("Total transferred:      %" APR_INT64_T_FMT " bytes\n", totalread);
    if (posting > 0)
        printf("Total POSTed:           %" APR_INT64_T_FMT "\n", totalposted);
    printf("HTML transferred:       %" APR_INT64_T_FMT " bytes\n", totalbread);

    /* avoid divide by zero */
    if (timetaken && done) {
        printf("Requests per second:    %.2f [#/sec] (mean)\n",
               (double) done / timetaken);
        printf("Time per request:       %.3f [ms] (mean)\n",
               (double) concurrency * timetaken * 1000 / done);
        printf("Time per request:       %.3f [ms] (mean, across all concurrent requests)\n",
               (double) timetaken * 1000 / done);
        printf("Transfer rate:          %.2f [Kbytes/sec] received\n",
               (double) totalread / 1024 / timetaken);
        if (posting > 0) {
            printf("                        %.2f kb/s sent\n",
               (double) totalposted / timetaken / 1024);
            printf("                        %.2f kb/s total\n",
               (double) (totalread + totalposted) / timetaken / 1024);
        }
    }

    if (done > 0) {
        /* work out connection times */
        int i;
        apr_time_t totalcon = 0, total = 0, totald = 0, totalwait = 0;
        apr_time_t meancon, meantot, meand, meanwait;
        apr_interval_time_t mincon = AB_MAX, mintot = AB_MAX, mind = AB_MAX,
                            minwait = AB_MAX;
        apr_interval_time_t maxcon = 0, maxtot = 0, maxd = 0, maxwait = 0;
        apr_interval_time_t mediancon = 0, mediantot = 0, mediand = 0, medianwait = 0;
        double sdtot = 0, sdcon = 0, sdd = 0, sdwait = 0;

        for (i = 0; i < done; i++) {
            struct data *s = &stats[i];
            mincon = ap_min(mincon, s->ctime);
            mintot = ap_min(mintot, s->time);
            mind = ap_min(mind, s->time - s->ctime);
            minwait = ap_min(minwait, s->waittime);

            maxcon = ap_max(maxcon, s->ctime);
            maxtot = ap_max(maxtot, s->time);
            maxd = ap_max(maxd, s->time - s->ctime);
            maxwait = ap_max(maxwait, s->waittime);

            totalcon += s->ctime;
            total += s->time;
            totald += s->time - s->ctime;
            totalwait += s->waittime;
        }
        meancon = totalcon / done;
        meantot = total / done;
        meand = totald / done;
        meanwait = totalwait / done;

        /* calculating the sample variance: the sum of the squared deviations, divided by n-1 */
        for (i = 0; i < done; i++) {
            struct data *s = &stats[i];
            double a;
            a = ((double)s->time - meantot);
            sdtot += a * a;
            a = ((double)s->ctime - meancon);
            sdcon += a * a;
            a = ((double)s->time - (double)s->ctime - meand);
            sdd += a * a;
            a = ((double)s->waittime - meanwait);
            sdwait += a * a;
        }

        sdtot = (done > 1) ? sqrt(sdtot / (done - 1)) : 0;
        sdcon = (done > 1) ? sqrt(sdcon / (done - 1)) : 0;
        sdd = (done > 1) ? sqrt(sdd / (done - 1)) : 0;
        sdwait = (done > 1) ? sqrt(sdwait / (done - 1)) : 0;

        /*
         * XXX: what is better; this hideous cast of the compradre function; or
         * the four warnings during compile ? dirkx just does not know and
         * hates both/
         */
        qsort(stats, done, sizeof(struct data),
              (int (*) (const void *, const void *)) compradre);
        if ((done > 1) && (done % 2))
            mediancon = (stats[done / 2].ctime + stats[done / 2 + 1].ctime) / 2;
        else
            mediancon = stats[done / 2].ctime;

        qsort(stats, done, sizeof(struct data),
              (int (*) (const void *, const void *)) compri);
        if ((done > 1) && (done % 2))
            mediand = (stats[done / 2].time + stats[done / 2 + 1].time \
            -stats[done / 2].ctime - stats[done / 2 + 1].ctime) / 2;
        else
            mediand = stats[done / 2].time - stats[done / 2].ctime;

        qsort(stats, done, sizeof(struct data),
              (int (*) (const void *, const void *)) compwait);
        if ((done > 1) && (done % 2))
            medianwait = (stats[done / 2].waittime + stats[done / 2 + 1].waittime) / 2;
        else
            medianwait = stats[done / 2].waittime;

        qsort(stats, done, sizeof(struct data),
              (int (*) (const void *, const void *)) comprando);
        if ((done > 1) && (done % 2))
            mediantot = (stats[done / 2].time + stats[done / 2 + 1].time) / 2;
        else
            mediantot = stats[done / 2].time;

        printf("\nConnection Times (ms)\n");
        /*
         * Reduce stats from apr time to milliseconds
         */
        mincon     = ap_round_ms(mincon);
        mind       = ap_round_ms(mind);
        minwait    = ap_round_ms(minwait);
        mintot     = ap_round_ms(mintot);
        meancon    = ap_round_ms(meancon);
        meand      = ap_round_ms(meand);
        meanwait   = ap_round_ms(meanwait);
        meantot    = ap_round_ms(meantot);
        mediancon  = ap_round_ms(mediancon);
        mediand    = ap_round_ms(mediand);
        medianwait = ap_round_ms(medianwait);
        mediantot  = ap_round_ms(mediantot);
        maxcon     = ap_round_ms(maxcon);
        maxd       = ap_round_ms(maxd);
        maxwait    = ap_round_ms(maxwait);
        maxtot     = ap_round_ms(maxtot);
        sdcon      = ap_double_ms(sdcon);
        sdd        = ap_double_ms(sdd);
        sdwait     = ap_double_ms(sdwait);
        sdtot      = ap_double_ms(sdtot);

        if (confidence) {
#define CONF_FMT_STRING "%5" APR_TIME_T_FMT " %4" APR_TIME_T_FMT " %5.1f %6" APR_TIME_T_FMT " %7" APR_TIME_T_FMT "\n"
            printf("              min  mean[+/-sd] median   max\n");
            printf("Connect:    " CONF_FMT_STRING,
                   mincon, meancon, sdcon, mediancon, maxcon);
            printf("Processing: " CONF_FMT_STRING,
                   mind, meand, sdd, mediand, maxd);
            printf("Waiting:    " CONF_FMT_STRING,
                   minwait, meanwait, sdwait, medianwait, maxwait);
            printf("Total:      " CONF_FMT_STRING,
                   mintot, meantot, sdtot, mediantot, maxtot);
#undef CONF_FMT_STRING

#define     SANE(what,mean,median,sd) \
              { \
                double d = (double)mean - median; \
                if (d < 0) d = -d; \
