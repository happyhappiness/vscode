 	    for (i = 0; i < requests; i++) {
                 apr_time_t diff = stats[i].time - stats[i].ctime;
 
 		sttime = stats[i].starttime;
 		(void) apr_ctime(tmstring, sttime);
 		fprintf(out, "%s\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\t%" APR_TIME_T_FMT "\n",
-			tmstring,
-			sttime,
-			stats[i].ctime,
-			diff,
-			stats[i].time,
-			stats[i].waittime);
+                tmstring,
+                sttime,
+                stats[i].ctime,
+                diff,
+                stats[i].time,
+                stats[i].waittime);
 	    }
 	    fclose(out);
 	}
-    /*
-     * XXX: what is better; this hideous cast of the compradre function; or
-     * the four warnings during compile ? dirkx just does not know and
-     * hates both/
-     */
+        /*
+         * XXX: what is better; this hideous cast of the compradre function; or
+         * the four warnings during compile ? dirkx just does not know and
+         * hates both/
+         */
 	qsort(stats, requests, sizeof(struct data),
 	      (int (*) (const void *, const void *)) compradre);
 	if ((requests > 1) && (requests % 2))
-        mediancon = (stats[requests / 2].ctime + stats[requests / 2 + 1].ctime) / 2;
+            mediancon = (stats[requests / 2].ctime + stats[requests / 2 + 1].ctime) / 2;
 	else
-        mediancon = stats[requests / 2].ctime;
+            mediancon = stats[requests / 2].ctime;
 
 	qsort(stats, requests, sizeof(struct data),
 	      (int (*) (const void *, const void *)) compri);
 	if ((requests > 1) && (requests % 2))
-        mediand = (stats[requests / 2].time + stats[requests / 2 + 1].time \
+            mediand = (stats[requests / 2].time + stats[requests / 2 + 1].time \
 	    -stats[requests / 2].ctime - stats[requests / 2 + 1].ctime) / 2;
 	else
-        mediand = stats[requests / 2].time - stats[requests / 2].ctime;
+            mediand = stats[requests / 2].time - stats[requests / 2].ctime;
 
 	qsort(stats, requests, sizeof(struct data),
 	      (int (*) (const void *, const void *)) compwait);
 	if ((requests > 1) && (requests % 2))
-        medianwait = (stats[requests / 2].waittime + stats[requests / 2 + 1].waittime) / 2;
+            medianwait = (stats[requests / 2].waittime + stats[requests / 2 + 1].waittime) / 2;
 	else
-        medianwait = stats[requests / 2].waittime;
+            medianwait = stats[requests / 2].waittime;
 
 	qsort(stats, requests, sizeof(struct data),
 	      (int (*) (const void *, const void *)) comprando);
 	if ((requests > 1) && (requests % 2))
-        mediantot = (stats[requests / 2].time + stats[requests / 2 + 1].time) / 2;
+            mediantot = (stats[requests / 2].time + stats[requests / 2 + 1].time) / 2;
 	else
-        mediantot = stats[requests / 2].time;
+            mediantot = stats[requests / 2].time;
 
 	printf("\nConnection Times (ms)\n");
 
 	if (confidence) {
 #define CONF_FMT_STRING "%5" APR_TIME_T_FMT " %4d %5.1f %6" APR_TIME_T_FMT " %7" APR_TIME_T_FMT "\n"
 	    printf("              min  mean[+/-sd] median   max\n");
-	    printf("Connect:    " CONF_FMT_STRING, 
-                   mincon, (int) (meancon + 0.5), sdcon, mediancon, maxcon);
+            printf("Connect:    " CONF_FMT_STRING,
+                       mincon, (int) (meancon + 0.5), sdcon, mediancon, maxcon);
 	    printf("Processing: " CONF_FMT_STRING,
-		   mind, (int) (meand + 0.5), sdd, mediand, maxd);
+               mind, (int) (meand + 0.5), sdd, mediand, maxd);
 	    printf("Waiting:    " CONF_FMT_STRING,
 	           minwait, (int) (meanwait + 0.5), sdwait, medianwait, maxwait);
 	    printf("Total:      " CONF_FMT_STRING,
-		   mintot, (int) (meantot + 0.5), sdtot, mediantot, maxtot);
+               mintot, (int) (meantot + 0.5), sdtot, mediantot, maxtot);
 #undef CONF_FMT_STRING
 
 #define     SANE(what,mean,median,sd) \
               { \
                 double d = (double)mean - median; \
                 if (d < 0) d = -d; \
