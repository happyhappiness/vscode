#if STAT_GRAPHS
/*
 * urgh, i don't like these, but they do cut the amount of code down immensely
 */

#define GRAPH_PER_MIN(Y) \
    for (i=0;i<(N_COUNT_HIST-2);i++) { \
	dt = tvSubDsec(CountHist[i+1].timestamp, CountHist[i].timestamp); \
	if (dt <= 0.0) \
	    break; \
	storeAppendPrintf(e, "%lu,%0.2f:", \
	    CountHist[i].timestamp.tv_sec, \
	    ((CountHist[i].Y - CountHist[i+1].Y) / dt)); \
    }

#define GRAPH_PER_HOUR(Y) \
    for (i=0;i<(N_COUNT_HOUR_HIST-2);i++) { \
	dt = tvSubDsec(CountHourHist[i+1].timestamp, CountHourHist[i].timestamp); \
	if (dt <= 0.0) \
	    break; \
	storeAppendPrintf(e, "%lu,%0.2f:", \
	    CountHourHist[i].timestamp.tv_sec, \
	    ((CountHourHist[i].Y - CountHourHist[i+1].Y) / dt)); \
