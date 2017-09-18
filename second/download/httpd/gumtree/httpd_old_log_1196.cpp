printf("<tr %s><th colspan=2 %s>Time taken for tests:</th>"
	   "<td colspan=2 %s>%qd.%03qd seconds</td></tr>\n",
	   trstring, tdstring, tdstring, timetaken / APR_USEC_PER_SEC, timetaken % APR_USEC_PER_SEC);