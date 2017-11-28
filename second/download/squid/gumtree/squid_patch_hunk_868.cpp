                       stats.ms_bytes_total / 1024);
 
     storeAppendPrintf(sentry, "\tTotal free:            %6.0f KB %.0f%%\n",
                       stats.ms_bytes_free / 1024,
                       Math::doublePercent(stats.ms_bytes_free, stats.ms_bytes_total));
 
-#elif HAVE_MALLINFO && HAVE_STRUCT_MALLINFO
-
-    storeAppendPrintf(sentry, "Memory usage for %s via mallinfo():\n",APP_SHORTNAME);
-
-    storeAppendPrintf(sentry, "\tTotal space in arena:  %6.0f KB\n",
-                      stats.mp_arena / 1024);
-
-    storeAppendPrintf(sentry, "\tOrdinary blocks:       %6.0f KB %6.0f blks\n",
-                      stats.mp_uordblks / 1024, stats.mp_ordblks);
-
-    storeAppendPrintf(sentry, "\tSmall blocks:          %6.0f KB %6.0f blks\n",
-                      stats.mp_usmblks / 1024, stats.mp_smblks);
-
-    storeAppendPrintf(sentry, "\tHolding blocks:        %6.0f KB %6.0f blks\n",
-                      stats.mp_hblkhd / 1024, stats.mp_hblks);
-
-    storeAppendPrintf(sentry, "\tFree Small blocks:     %6.0f KB\n",
-                      stats.mp_fsmblks / 1024);
-
-    storeAppendPrintf(sentry, "\tFree Ordinary blocks:  %6.0f KB\n",
-                      stats.mp_fordblks / 1024);
-
-    double t = stats.mp_fsmblks + stats.mp_fordblks;
-
-    storeAppendPrintf(sentry, "\tTotal in use:          %6.0f KB %.0f%%\n",
-                      t / 1024, Math::doublePercent(t, stats.mp_arena + stats.mp_hblkhd));
-
-    t = stats.mp_fsmblks + stats.mp_fordblks;
-
-    storeAppendPrintf(sentry, "\tTotal free:            %6.0f KB %.0f%%\n",
-                      t / 1024, Math::doublePercent(t, stats.mp_arena + stats.mp_hblkhd));
-
-    t = stats.mp_arena + stats.mp_hblkhd;
-
-    storeAppendPrintf(sentry, "\tTotal size:            %6.0f KB\n",
-                      t / 1024);
-
-#if HAVE_STRUCT_MALLINFO_MXFAST
-
-    storeAppendPrintf(sentry, "\tmax size of small blocks:\t%.0f\n", stats.mp_mxfast);
-
-    storeAppendPrintf(sentry, "\tnumber of small blocks in a holding block:\t%.0f\n",
-                      stats.mp_nlblks);
-
-    storeAppendPrintf(sentry, "\tsmall block rounding factor:\t%.0f\n", stats.mp_grain);
-
-    storeAppendPrintf(sentry, "\tspace (including overhead) allocated in ord. blks:\t%.0f\n"
-                      ,stats.mp_uordbytes);
-
-    storeAppendPrintf(sentry, "\tnumber of ordinary blocks allocated:\t%.0f\n",
-                      stats.mp_allocated);
-
-    storeAppendPrintf(sentry, "\tbytes used in maintaining the free tree:\t%.0f\n",
-                      stats.mp_treeoverhead);
-
-#endif /* HAVE_STRUCT_MALLINFO_MXFAST */
-#endif /* HAVE_MALLINFO */
+#endif
 
     storeAppendPrintf(sentry, "Memory accounted for:\n");
-
-#if !(HAVE_MSTATS && HAVE_GNUMALLOC_H) && HAVE_MALLINFO && HAVE_STRUCT_MALLINFO
-
-    storeAppendPrintf(sentry, "\tTotal accounted:       %6.0f KB %3.0f%%\n",
-                      stats.total_accounted / 1024, Math::doublePercent(stats.total_accounted, t));
-
-#else
-
     storeAppendPrintf(sentry, "\tTotal accounted:       %6.0f KB\n",
                       stats.total_accounted / 1024);
-
-#endif
     {
         MemPoolGlobalStats mp_stats;
         memPoolGetGlobalStats(&mp_stats);
-#if !(HAVE_MSTATS && HAVE_GNUMALLOC_H) && HAVE_MALLINFO && HAVE_STRUCT_MALLINFO
-
-        storeAppendPrintf(sentry, "\tmemPool accounted:     %6.0f KB %3.0f%%\n",
-                          stats.mem_pool_allocated / 1024,
-                          Math::doublePercent(stats.mem_pool_allocated, t));
-
-        const double iFree = max(0.0, t - stats.mem_pool_allocated);
-        storeAppendPrintf(sentry, "\tmemPool unaccounted:   %6.0f KB %3.0f%%\n",
-                          (t - stats.mem_pool_allocated) / 1024,
-                          Math::doublePercent(iFree, t));
-#endif
-
         storeAppendPrintf(sentry, "\tmemPoolAlloc calls: %9.0f\n",
                           stats.gb_saved_count);
         storeAppendPrintf(sentry, "\tmemPoolFree calls:  %9.0f\n",
                           stats.gb_freed_count);
     }
 
