storeAppendPrintf(sentry, "false\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
                      stats->falseHits, xpercent(stats->falseHits, tot_count),
                      stats->falseMisses, xpercent(stats->falseMisses, tot_count),
                      false_count, xpercent(false_count, tot_count));