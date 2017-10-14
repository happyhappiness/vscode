printf("<tr %s><th colspan=2 %s>Time taken for tests:</th>"
	   "<td colspan=2 %s>%" APR_INT64_T_FMT ".%03ld seconds</td></tr>\n",
	   trstring, tdstring, tdstring, apr_time_sec(timetaken),
           (long)apr_time_usec(timetaken));