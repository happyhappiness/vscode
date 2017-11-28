storeAppendPrintf(sentry, "\tCache Misses:         %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_MISS) / 1000.0,
                      statPctileSvc(0.5, 60, PCTILE_MISS) / 1000.0);