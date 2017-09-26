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

/* --------------------------------------------------------- */
