storeAppendPrintf(sentry, "\tDNS Lookups:          %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.dns_lookups5[i] / fct,
                          stats.dns_lookups60[i] / fct);