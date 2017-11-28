storeAppendPrintf(e, "%2d\t %-25s\t %5d\t %6.3f\t %6.3f\n",
                          Http::HeaderLookupTable.lookup(h).id,
                          Http::HeaderLookupTable.lookup(h).name,
                          stats.aliveCount,
                          xpercent(stats.errCount, stats.parsCount),
                          xpercent(stats.repCount, stats.seenCount));