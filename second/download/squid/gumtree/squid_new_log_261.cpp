storeAppendPrintf(sentry, "%5d-%5d: %9.0f %2.0f%%\n",
                          i ? (1 << (i - 1)) + 1 : 1,
                          1 << i,
                          stats.gopher_read_hist[i],
                          Math::doublePercent(stats.gopher_read_hist[i], stats.gopher_reads));