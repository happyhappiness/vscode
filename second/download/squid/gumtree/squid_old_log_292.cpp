storeAppendPrintf(sentry, "\tICP Queries:          %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_ICP_QUERY) / 1000000.0,
                      statPctileSvc(0.5, 60, PCTILE_ICP_QUERY) / 1000000.0);