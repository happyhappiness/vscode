storeAppendPrintf(sentry, "\tCache Hits:           %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_HIT) / 1000.0,
                      statPctileSvc(0.5, 60, PCTILE_HIT) / 1000.0);