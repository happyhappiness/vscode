storeAppendPrintf(sentry, "\tTotal accounted:       %6.0f KB %3.0f%%\n",
                      stats.total_accounted / 1024, Math::doublePercent(stats.total_accounted, t));