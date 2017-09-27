 	   "<td colspan=2 %s>%" APR_SIZE_T_FMT " bytes</td></tr>\n",
 	   trstring, tdstring, tdstring, doclen);
     printf("<tr %s><th colspan=2 %s>Concurrency Level:</th>"
 	   "<td colspan=2 %s>%d</td></tr>\n",
 	   trstring, tdstring, tdstring, concurrency);
     printf("<tr %s><th colspan=2 %s>Time taken for tests:</th>"
-	   "<td colspan=2 %s>%qd.%03ld seconds</td></tr>\n",
+	   "<td colspan=2 %s>%" APR_INT64_T_FMT ".%03ld seconds</td></tr>\n",
 	   trstring, tdstring, tdstring, apr_time_sec(timetaken),
            (long)apr_time_usec(timetaken));
     printf("<tr %s><th colspan=2 %s>Complete requests:</th>"
 	   "<td colspan=2 %s>%ld</td></tr>\n",
 	   trstring, tdstring, tdstring, done);
     printf("<tr %s><th colspan=2 %s>Failed requests:</th>"
