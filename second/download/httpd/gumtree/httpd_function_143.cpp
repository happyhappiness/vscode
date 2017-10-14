static void output_html_results(void)
{
    long timetaken;

    endtime = apr_time_now();
    timetaken = (long)((endtime - start) / 1000);

    printf("\n\n<table %s>\n", tablestring);
    printf("<tr %s><th colspan=2 %s>Server Software:</th>"
	   "<td colspan=2 %s>%s</td></tr>\n",
	   trstring, tdstring, tdstring, servername);
    printf("<tr %s><th colspan=2 %s>Server Hostname:</th>"
	   "<td colspan=2 %s>%s</td></tr>\n",
	   trstring, tdstring, tdstring, hostname);
    printf("<tr %s><th colspan=2 %s>Server Port:</th>"
	   "<td colspan=2 %s>%hd</td></tr>\n",
	   trstring, tdstring, tdstring, port);
    printf("<tr %s><th colspan=2 %s>Document Path:</th>"
	   "<td colspan=2 %s>%s</td></tr>\n",
	   trstring, tdstring, tdstring, path);
    printf("<tr %s><th colspan=2 %s>Document Length:</th>"
	   "<td colspan=2 %s>%" APR_SIZE_T_FMT " bytes</td></tr>\n",
	   trstring, tdstring, tdstring, doclen);
    printf("<tr %s><th colspan=2 %s>Concurrency Level:</th>"
	   "<td colspan=2 %s>%d</td></tr>\n",
	   trstring, tdstring, tdstring, concurrency);
    printf("<tr %s><th colspan=2 %s>Time taken for tests:</th>"
	   "<td colspan=2 %s>%qd.%03ld seconds</td></tr>\n",
	   trstring, tdstring, tdstring, apr_time_sec(timetaken),
           (long)apr_time_usec(timetaken));
    printf("<tr %s><th colspan=2 %s>Complete requests:</th>"
	   "<td colspan=2 %s>%ld</td></tr>\n",
	   trstring, tdstring, tdstring, done);
    printf("<tr %s><th colspan=2 %s>Failed requests:</th>"
	   "<td colspan=2 %s>%ld</td></tr>\n",
	   trstring, tdstring, tdstring, bad);
    if (bad)
	printf("<tr %s><td colspan=4 %s >   (Connect: %d, Length: %d, Exceptions: %d)</td></tr>\n",
	       trstring, tdstring, err_conn, err_length, err_except);
    if (err_response)
	printf("<tr %s><th colspan=2 %s>Non-2xx responses:</th>"
	       "<td colspan=2 %s>%d</td></tr>\n",
	       trstring, tdstring, tdstring, err_response);
    if (keepalive)
	printf("<tr %s><th colspan=2 %s>Keep-Alive requests:</th>"
	       "<td colspan=2 %s>%ld</td></tr>\n",
	       trstring, tdstring, tdstring, doneka);
    printf("<tr %s><th colspan=2 %s>Total transferred:</th>"
	   "<td colspan=2 %s>%ld bytes</td></tr>\n",
	   trstring, tdstring, tdstring, totalread);
    if (posting > 0)
	printf("<tr %s><th colspan=2 %s>Total POSTed:</th>"
	       "<td colspan=2 %s>%ld</td></tr>\n",
	       trstring, tdstring, tdstring, totalposted);
    printf("<tr %s><th colspan=2 %s>HTML transferred:</th>"
	   "<td colspan=2 %s>%ld bytes</td></tr>\n",
	   trstring, tdstring, tdstring, totalbread);

    /* avoid divide by zero */
    if (timetaken) {
	printf("<tr %s><th colspan=2 %s>Requests per second:</th>"
	       "<td colspan=2 %s>%.2f</td></tr>\n",
	   trstring, tdstring, tdstring, 1000 * (float) (done) / timetaken);
	printf("<tr %s><th colspan=2 %s>Transfer rate:</th>"
	       "<td colspan=2 %s>%.2f kb/s received</td></tr>\n",
	     trstring, tdstring, tdstring, (float) (totalread) / timetaken);
	if (posting > 0) {
	    printf("<tr %s><td colspan=2 %s>&nbsp;</td>"
		   "<td colspan=2 %s>%.2f kb/s sent</td></tr>\n",
		   trstring, tdstring, tdstring,
		   (float) (totalposted) / timetaken);
	    printf("<tr %s><td colspan=2 %s>&nbsp;</td>"
		   "<td colspan=2 %s>%.2f kb/s total</td></tr>\n",
		   trstring, tdstring, tdstring,
		   (float) (totalread + totalposted) / timetaken);
	}
    } {
	/* work out connection times */
	long i;
	apr_interval_time_t totalcon = 0, total = 0;
	apr_interval_time_t mincon = AB_MAX, mintot = AB_MAX;
	apr_interval_time_t maxcon = 0, maxtot = 0;

	for (i = 0; i < requests; i++) {
	    struct data s = stats[i];
	    mincon = ap_min(mincon, s.ctime);
	    mintot = ap_min(mintot, s.time);
	    maxcon = ap_max(maxcon, s.ctime);
	    maxtot = ap_max(maxtot, s.time);
	    totalcon += s.ctime;
	    total += s.time;
	}

	if (requests > 0) {	/* avoid division by zero (if 0 requests) */
	    printf("<tr %s><th %s colspan=4>Connnection Times (ms)</th></tr>\n",
		   trstring, tdstring);
	    printf("<tr %s><th %s>&nbsp;</th> <th %s>min</th>   <th %s>avg</th>   <th %s>max</th></tr>\n",
		   trstring, tdstring, tdstring, tdstring, tdstring);
	    printf("<tr %s><th %s>Connect:</th>"
		   "<td %s>%5" APR_TIME_T_FMT "</td>"
		   "<td %s>%5" APR_TIME_T_FMT "</td>"
		   "<td %s>%5" APR_TIME_T_FMT "</td></tr>\n",
		   trstring, tdstring, tdstring, mincon, tdstring, totalcon / requests, tdstring, maxcon);
	    printf("<tr %s><th %s>Processing:</th>"
		   "<td %s>%5" APR_TIME_T_FMT "</td>"
		   "<td %s>%5" APR_TIME_T_FMT "</td>"
		   "<td %s>%5" APR_TIME_T_FMT "</td></tr>\n",
		   trstring, tdstring, tdstring, mintot - mincon, tdstring,
		   (total / requests) - (totalcon / requests), tdstring, maxtot - maxcon);
	    printf("<tr %s><th %s>Total:</th>"
		   "<td %s>%5" APR_TIME_T_FMT "</td>"
		   "<td %s>%5" APR_TIME_T_FMT "</td>"
		   "<td %s>%5" APR_TIME_T_FMT "</td></tr>\n",
		   trstring, tdstring, tdstring, mintot, tdstring, total / requests, tdstring, maxtot);
	}
	printf("</table>\n");
    }
}