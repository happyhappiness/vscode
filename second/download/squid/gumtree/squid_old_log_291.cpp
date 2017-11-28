storeAppendPrintf(sentry, "\tDNS Lookups:          %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_DNS) / 1000.0,
                      statPctileSvc(0.5, 60, PCTILE_DNS) / 1000.0);