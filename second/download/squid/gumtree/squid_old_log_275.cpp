storeAppendPrintf(sentry, "\tSelect loop called: %ld times, %0.3f ms avg\n",
                      statCounter.select_loops, 1000.0 * runtime / statCounter.select_loops);