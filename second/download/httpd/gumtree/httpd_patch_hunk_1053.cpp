 
     endtime = apr_time_now();
     timetaken = (long)((endtime - start) / 1000);
 
     printf("\n\n<table %s>\n", tablestring);
     printf("<tr %s><th colspan=2 %s>Server Software:</th>"
-	   "<td colspan=2 %s>%s</td></tr>\n",
-	   trstring, tdstring, tdstring, servername);
+       "<td colspan=2 %s>%s</td></tr>\n",
+       trstring, tdstring, tdstring, servername);
     printf("<tr %s><th colspan=2 %s>Server Hostname:</th>"
-	   "<td colspan=2 %s>%s</td></tr>\n",
-	   trstring, tdstring, tdstring, hostname);
+       "<td colspan=2 %s>%s</td></tr>\n",
+       trstring, tdstring, tdstring, hostname);
     printf("<tr %s><th colspan=2 %s>Server Port:</th>"
-	   "<td colspan=2 %s>%hd</td></tr>\n",
-	   trstring, tdstring, tdstring, port);
+       "<td colspan=2 %s>%hd</td></tr>\n",
+       trstring, tdstring, tdstring, port);
     printf("<tr %s><th colspan=2 %s>Document Path:</th>"
-	   "<td colspan=2 %s>%s</td></tr>\n",
-	   trstring, tdstring, tdstring, path);
+       "<td colspan=2 %s>%s</td></tr>\n",
+       trstring, tdstring, tdstring, path);
     printf("<tr %s><th colspan=2 %s>Document Length:</th>"
-	   "<td colspan=2 %s>%" APR_SIZE_T_FMT " bytes</td></tr>\n",
-	   trstring, tdstring, tdstring, doclen);
+       "<td colspan=2 %s>%" APR_SIZE_T_FMT " bytes</td></tr>\n",
+       trstring, tdstring, tdstring, doclen);
     printf("<tr %s><th colspan=2 %s>Concurrency Level:</th>"
-	   "<td colspan=2 %s>%d</td></tr>\n",
-	   trstring, tdstring, tdstring, concurrency);
+       "<td colspan=2 %s>%d</td></tr>\n",
+       trstring, tdstring, tdstring, concurrency);
     printf("<tr %s><th colspan=2 %s>Time taken for tests:</th>"
-	   "<td colspan=2 %s>%" APR_INT64_T_FMT ".%03ld seconds</td></tr>\n",
-	   trstring, tdstring, tdstring, apr_time_sec(timetaken),
+       "<td colspan=2 %s>%" APR_INT64_T_FMT ".%03ld seconds</td></tr>\n",
+       trstring, tdstring, tdstring, apr_time_sec(timetaken),
            (long)apr_time_usec(timetaken));
     printf("<tr %s><th colspan=2 %s>Complete requests:</th>"
-	   "<td colspan=2 %s>%ld</td></tr>\n",
-	   trstring, tdstring, tdstring, done);
+       "<td colspan=2 %s>%ld</td></tr>\n",
+       trstring, tdstring, tdstring, done);
     printf("<tr %s><th colspan=2 %s>Failed requests:</th>"
-	   "<td colspan=2 %s>%ld</td></tr>\n",
-	   trstring, tdstring, tdstring, bad);
+       "<td colspan=2 %s>%ld</td></tr>\n",
+       trstring, tdstring, tdstring, bad);
     if (bad)
 	printf("<tr %s><td colspan=4 %s >   (Connect: %d, Length: %d, Exceptions: %d)</td></tr>\n",
-	       trstring, tdstring, err_conn, err_length, err_except);
+           trstring, tdstring, err_conn, err_length, err_except);
     if (err_response)
 	printf("<tr %s><th colspan=2 %s>Non-2xx responses:</th>"
-	       "<td colspan=2 %s>%d</td></tr>\n",
-	       trstring, tdstring, tdstring, err_response);
+           "<td colspan=2 %s>%d</td></tr>\n",
+           trstring, tdstring, tdstring, err_response);
     if (keepalive)
 	printf("<tr %s><th colspan=2 %s>Keep-Alive requests:</th>"
-	       "<td colspan=2 %s>%ld</td></tr>\n",
-	       trstring, tdstring, tdstring, doneka);
+           "<td colspan=2 %s>%ld</td></tr>\n",
+           trstring, tdstring, tdstring, doneka);
     printf("<tr %s><th colspan=2 %s>Total transferred:</th>"
-	   "<td colspan=2 %s>%ld bytes</td></tr>\n",
-	   trstring, tdstring, tdstring, totalread);
+       "<td colspan=2 %s>%ld bytes</td></tr>\n",
+       trstring, tdstring, tdstring, totalread);
     if (posting > 0)
 	printf("<tr %s><th colspan=2 %s>Total POSTed:</th>"
-	       "<td colspan=2 %s>%ld</td></tr>\n",
-	       trstring, tdstring, tdstring, totalposted);
+           "<td colspan=2 %s>%ld</td></tr>\n",
+           trstring, tdstring, tdstring, totalposted);
     printf("<tr %s><th colspan=2 %s>HTML transferred:</th>"
-	   "<td colspan=2 %s>%ld bytes</td></tr>\n",
-	   trstring, tdstring, tdstring, totalbread);
+       "<td colspan=2 %s>%ld bytes</td></tr>\n",
+       trstring, tdstring, tdstring, totalbread);
 
     /* avoid divide by zero */
     if (timetaken) {
 	printf("<tr %s><th colspan=2 %s>Requests per second:</th>"
-	       "<td colspan=2 %s>%.2f</td></tr>\n",
+           "<td colspan=2 %s>%.2f</td></tr>\n",
 	   trstring, tdstring, tdstring, 1000 * (float) (done) / timetaken);
 	printf("<tr %s><th colspan=2 %s>Transfer rate:</th>"
-	       "<td colspan=2 %s>%.2f kb/s received</td></tr>\n",
-	     trstring, tdstring, tdstring, (float) (totalread) / timetaken);
+           "<td colspan=2 %s>%.2f kb/s received</td></tr>\n",
+           trstring, tdstring, tdstring, (float) (totalread) / timetaken);
 	if (posting > 0) {
 	    printf("<tr %s><td colspan=2 %s>&nbsp;</td>"
-		   "<td colspan=2 %s>%.2f kb/s sent</td></tr>\n",
-		   trstring, tdstring, tdstring,
-		   (float) (totalposted) / timetaken);
+               "<td colspan=2 %s>%.2f kb/s sent</td></tr>\n",
+               trstring, tdstring, tdstring,
+               (float) (totalposted) / timetaken);
 	    printf("<tr %s><td colspan=2 %s>&nbsp;</td>"
-		   "<td colspan=2 %s>%.2f kb/s total</td></tr>\n",
-		   trstring, tdstring, tdstring,
-		   (float) (totalread + totalposted) / timetaken);
+               "<td colspan=2 %s>%.2f kb/s total</td></tr>\n",
+               trstring, tdstring, tdstring,
+               (float) (totalread + totalposted) / timetaken);
 	}
-    } {
+    }
+    {
 	/* work out connection times */
 	long i;
 	apr_interval_time_t totalcon = 0, total = 0;
 	apr_interval_time_t mincon = AB_MAX, mintot = AB_MAX;
 	apr_interval_time_t maxcon = 0, maxtot = 0;
 
