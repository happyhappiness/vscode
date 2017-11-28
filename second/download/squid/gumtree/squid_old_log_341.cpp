storeAppendPrintf(sentry, "\tICP Queries:          %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_ICP_QUERY) / 1000000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_ICP_QUERY) / 1000000.0);