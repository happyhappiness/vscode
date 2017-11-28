storeAppendPrintf(sentry, "\tHTTP Requests (All):  %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.http_requests5[i] / fct,
                          stats.http_requests60[i] / fct);