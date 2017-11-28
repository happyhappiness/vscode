     struct mstats ms = mstats();
     fprintf(debug_log, "\ttotal space in arena:  %6d KB\n",
             (int) (ms.bytes_total >> 10));
     fprintf(debug_log, "\tTotal free:            %6d KB %d%%\n",
             (int) (ms.bytes_free >> 10),
             Math::intPercent(ms.bytes_free, ms.bytes_total));
-#elif HAVE_MALLINFO && HAVE_STRUCT_MALLINFO
-
-    struct mallinfo mp;
-    int t;
-
-    if (!do_mallinfo)
-        return;
-
-    mp = mallinfo();
-
-    fprintf(debug_log, "Memory usage for " APP_SHORTNAME " via mallinfo():\n");
-
-    fprintf(debug_log, "\ttotal space in arena:  %6ld KB\n",
-            (long)mp.arena >> 10);
-
-    fprintf(debug_log, "\tOrdinary blocks:       %6ld KB %6ld blks\n",
-            (long)mp.uordblks >> 10, (long)mp.ordblks);
-
-    fprintf(debug_log, "\tSmall blocks:          %6ld KB %6ld blks\n",
-            (long)mp.usmblks >> 10, (long)mp.smblks);
-
-    fprintf(debug_log, "\tHolding blocks:        %6ld KB %6ld blks\n",
-            (long)mp.hblkhd >> 10, (long)mp.hblks);
-
-    fprintf(debug_log, "\tFree Small blocks:     %6ld KB\n",
-            (long)mp.fsmblks >> 10);
-
-    fprintf(debug_log, "\tFree Ordinary blocks:  %6ld KB\n",
-            (long)mp.fordblks >> 10);
-
-    t = mp.uordblks + mp.usmblks + mp.hblkhd;
-
-    fprintf(debug_log, "\tTotal in use:          %6d KB %d%%\n",
-            t >> 10, Math::intPercent(t, mp.arena));
-
-    t = mp.fsmblks + mp.fordblks;
-
-    fprintf(debug_log, "\tTotal free:            %6d KB %d%%\n",
-            t >> 10, Math::intPercent(t, mp.arena));
-
-#if HAVE_STRUCT_MALLINFO_MXFAST
-
-    fprintf(debug_log, "\tmax size of small blocks:\t%d\n",
-            mp.mxfast);
-
-    fprintf(debug_log, "\tnumber of small blocks in a holding block:\t%d\n",
-            mp.nlblks);
-
-    fprintf(debug_log, "\tsmall block rounding factor:\t%d\n",
-            mp.grain);
-
-    fprintf(debug_log, "\tspace (including overhead) allocated in ord. blks:\t%d\n",
-            mp.uordbytes);
-
-    fprintf(debug_log, "\tnumber of ordinary blocks allocated:\t%d\n",
-            mp.allocated);
-
-    fprintf(debug_log, "\tbytes used in maintaining the free tree:\t%d\n",
-            mp.treeoverhead);
-
-#endif /* HAVE_STRUCT_MALLINFO_MXFAST */
-#endif /* HAVE_MALLINFO */
+#endif
 }
 
 void
 squid_getrusage(struct rusage *r)
 {
     memset(r, '\0', sizeof(struct rusage));
