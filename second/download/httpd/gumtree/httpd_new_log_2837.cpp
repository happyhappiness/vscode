printf("<tr %s><th %s>Connect:</th>"
               "<td %s>%5" APR_TIME_T_FMT "</td>"
               "<td %s>%5" APR_TIME_T_FMT "</td>"
               "<td %s>%5" APR_TIME_T_FMT "</td></tr>\n",
               trstring, tdstring, tdstring, mincon, tdstring, totalcon / done, tdstring, maxcon);