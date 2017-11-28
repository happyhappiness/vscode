storeAppendPrintf(sentry, "\tAverage ICP messages per minute since start:\t%.1f\n",
                      (statCounter.icp.pkts_sent + statCounter.icp.pkts_recv) / (runtime / 60.0));