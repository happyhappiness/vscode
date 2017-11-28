                           head->flags.icase ? " -i" : null_string,
                           head->pattern,
                           (int) head->min / 60,
                           (int) (100.0 * head->pct + 0.5),
                           (int) head->max / 60);
 
+        if (head->max_stale >= 0)
+            storeAppendPrintf(entry, " max-stale=%d", head->max_stale);
+
         if (head->flags.refresh_ims)
             storeAppendPrintf(entry, " refresh-ims");
 
-#if HTTP_VIOLATIONS
+        if (head->flags.store_stale)
+            storeAppendPrintf(entry, " store-stale");
+
+#if USE_HTTP_VIOLATIONS
 
         if (head->flags.override_expire)
             storeAppendPrintf(entry, " override-expire");
 
         if (head->flags.override_lastmod)
             storeAppendPrintf(entry, " override-lastmod");
