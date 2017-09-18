
    /* avoid divide by zero */
    if (timetaken) {
	printf("Requests per second:    %.2f [#/sec] (mean)\n", 
               (float) (done / timetaken));
	printf("Time per request:       %.3f [ms] (mean)\n", 
               (float) (concurrency * timetaken / done));
	printf("Time per request:       %.3f [ms] (mean, across all concurrent requests)\n",
	       (float) (timetaken / done));
	printf("Transfer rate:          %.2f [Kbytes/sec] received\n",
	       (float) (totalread / 1024 / timetaken));
	if (posting > 0) {
	    printf("                        %.2f kb/s sent\n",
		   (float) (totalposted / timetaken / 1024));
	    printf("                        %.2f kb/s total\n",
