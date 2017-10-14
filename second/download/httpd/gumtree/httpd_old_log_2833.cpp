printf("<tr %s><th colspan=2 %s>Requests per second:</th>"
           "<td colspan=2 %s>%.2f</td></tr>\n",
           trstring, tdstring, tdstring, 1000 * (float) (done) / timetaken);