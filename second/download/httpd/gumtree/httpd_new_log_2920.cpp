printf("<tr %s><th %s>Processing:</th>"
               "<td %s>%5" APR_TIME_T_FMT "</td>"
               "<td %s>%5" APR_TIME_T_FMT "</td>"
               "<td %s>%5" APR_TIME_T_FMT "</td></tr>\n",
               trstring, tdstring, tdstring, mintot - mincon, tdstring,
               (total / done) - (totalcon / done), tdstring, maxtot - maxcon);