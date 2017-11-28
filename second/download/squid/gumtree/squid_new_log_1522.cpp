storeAppendPrintf(sentry, "  %10" PRIu64 "\t%10" PRIu64 "\t%6.2f\t%s%s\n",
                          R->stats.matchCount,
                          R->stats.matchTests,
                          xpercent(R->stats.matchCount, R->stats.matchTests),
                          (R->pattern.flags&REG_ICASE ? "-i " : ""),
                          R->pattern.c_str());