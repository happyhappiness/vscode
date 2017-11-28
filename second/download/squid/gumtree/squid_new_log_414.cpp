storeAppendPrintf(sentry, "\tICP Queries:          %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.icp_queries5[i] / fct,
                          stats.icp_queries60[i] / fct);