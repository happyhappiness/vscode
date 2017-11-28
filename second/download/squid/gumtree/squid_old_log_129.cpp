storeAppendPrintf(sentry, "true\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
                      stats->true_hits, xpercent(stats->true_hits, tot_count),
                      stats->true_misses, xpercent(stats->true_misses, tot_count),
                      true_count, xpercent(true_count, tot_count));