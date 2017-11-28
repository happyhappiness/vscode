                           xpercent(sd_stats.add_coll_count, sd_stats.add_count),
                           xpercent(sd_stats.rej_coll_count, sd_stats.rej_count));
     } else {
         storeAppendPrintf(e, "store digest: disabled.\n");
     }
 
-#endif
+#endif //USE_CACHE_DIGESTS
 }
 
 /*
  * LOCAL FUNCTIONS
  */
 
