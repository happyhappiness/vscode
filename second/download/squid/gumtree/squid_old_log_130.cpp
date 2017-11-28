storeAppendPrintf(sentry, "false\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
                      stats->false_hits, xpercent(stats->false_hits, tot_count),
                      stats->false_misses, xpercent(stats->false_misses, tot_count),
                      false_count, xpercent(false_count, tot_count));