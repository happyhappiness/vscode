	else
	    meantot = stats[requests / 2].time;

	printf("\nConnection Times (ms)\n");

	if (confidence) {
#define CONF_FMT_STRING "%" APR_TIME_T_FMT " %5d %6.1f %" APR_TIME_T_FMT " %" APR_TIME_T_FMT "\n"
	    printf("            min  mean[+/-sd] median   max\n");
	    printf("Connect:    " CONF_FMT_STRING, 
                   mincon, (int) (totalcon + 0.5), sdcon, meancon, maxcon);
	    printf("Processing: " CONF_FMT_STRING,
		   mind, (int) (totald + 0.5), sdd, meand, maxd);
	    printf("Waiting:    " CONF_FMT_STRING,
	           minwait, (int) (totalwait + 0.5), sdwait, meanwait, maxwait);
