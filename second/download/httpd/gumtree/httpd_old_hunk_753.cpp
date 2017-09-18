                double d = (double)avg - mean; \
                if (d < 0) d = -d; \
                if (d > 2 * sd ) \
                    printf("ERROR: The median and mean for " what " are more than twice the standard\n" \
                           "       deviation apart. These results are NOT reliable.\n"); \
                else if (d > sd ) \
                    printf("WARING: The median and mean for " what " are not within a normal deviation\n" \
                           "        These results are probably not that reliable.\n"); \
            }
	    SANE("the initial connection time", totalcon, meancon, sdcon);
	    SANE("the processing time", totald, meand, sdd);
	    SANE("the waiting time", totalwait, meanwait, sdwait);
	    SANE("the total time", total, meantot, sdtot);
