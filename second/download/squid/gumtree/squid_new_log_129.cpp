storeAppendPrintf(sentry, "true\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
                      stats->trueHits, xpercent(stats->trueHits, tot_count),
                      stats->trueMisses, xpercent(stats->trueMisses, tot_count),
                      true_count, xpercent(true_count, tot_count));