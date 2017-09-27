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
        apr_time_t meancon, meantot, meand, meanwait;
        apr_interval_time_t mincon = AB_MAX, mintot = AB_MAX, mind = AB_MAX, 
                            minwait = AB_MAX;
        apr_interval_time_t maxcon = 0, maxtot = 0, maxd = 0, maxwait = 0;
        apr_interval_time_t mediancon = 0, mediantot = 0, mediand = 0, medianwait = 0;
        double sdtot = 0, sdcon = 0, sdd = 0, sdwait = 0;

	for (i = 0; i < requests; i++) {
