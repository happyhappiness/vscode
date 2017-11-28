                       time_frame
                      );
 
     storeAppendPrintf(sentry,
                       "Probe Name\t  Events\t cumulated time \t best case \t average \t worst case\t Rate / sec \t %% in int\n");
 
-    for (i = 0; i < XPROF_LAST; i++) {
+    for (i = 0; i < XPROF_LAST; ++i) {
         if (!hist[i]->name)
             continue;
 
         show = &hist[i]->hist;
 
         if (!show->count)
