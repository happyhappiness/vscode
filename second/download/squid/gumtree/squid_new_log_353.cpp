storeAppendPrintf(sentry, "\tSelect loop called: %.0f times, %0.3f ms avg\n",
                      stats.select_loops, stats.avg_loop_time / fct);