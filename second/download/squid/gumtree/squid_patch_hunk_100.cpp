     }
 
     storeAppendPrintf(sentry, "Digest guesses stats for %s:\n", label);
     storeAppendPrintf(sentry, "guess\t hit\t\t miss\t\t total\t\t\n");
     storeAppendPrintf(sentry, " \t #\t %%\t #\t %%\t #\t %%\t\n");
     storeAppendPrintf(sentry, "true\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
-                      stats->true_hits, xpercent(stats->true_hits, tot_count),
-                      stats->true_misses, xpercent(stats->true_misses, tot_count),
+                      stats->trueHits, xpercent(stats->trueHits, tot_count),
+                      stats->trueMisses, xpercent(stats->trueMisses, tot_count),
                       true_count, xpercent(true_count, tot_count));
     storeAppendPrintf(sentry, "false\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
-                      stats->false_hits, xpercent(stats->false_hits, tot_count),
-                      stats->false_misses, xpercent(stats->false_misses, tot_count),
+                      stats->falseHits, xpercent(stats->falseHits, tot_count),
+                      stats->falseMisses, xpercent(stats->falseMisses, tot_count),
                       false_count, xpercent(false_count, tot_count));
     storeAppendPrintf(sentry, "all\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
                       hit_count, xpercent(hit_count, tot_count),
                       miss_count, xpercent(miss_count, tot_count),
                       tot_count, xpercent(tot_count, tot_count));
     storeAppendPrintf(sentry, "\tclose_hits: %d ( %d%%) /* cd said hit, doc was in the peer cache, but we got a miss */\n",
-                      stats->close_hits, xpercentInt(stats->close_hits, stats->false_hits));
+                      stats->closeHits, xpercentInt(stats->closeHits, stats->falseHits));
 }
 
 void
 cacheDigestReport(CacheDigest * cd, const char *label, StoreEntry * e)
 {
     CacheDigestStats stats;
