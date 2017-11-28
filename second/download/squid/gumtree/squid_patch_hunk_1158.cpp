         storeAppendPrintf(sentry, " closest-only");
 
 #if USE_HTCP
     if (p->options.htcp) {
         storeAppendPrintf(sentry, " htcp");
         if (p->options.htcp_oldsquid || p->options.htcp_no_clr || p->options.htcp_no_purge_clr || p->options.htcp_only_clr) {
-            int doneopts=0;
-            if (p->options.htcp_oldsquid)
-                storeAppendPrintf(sentry, "%soldsquid",(doneopts++>0?",":"="));
-            if (p->options.htcp_no_clr)
-                storeAppendPrintf(sentry, "%sno-clr",(doneopts++>0?",":"="));
-            if (p->options.htcp_no_purge_clr)
-                storeAppendPrintf(sentry, "%sno-purge-clr",(doneopts++>0?",":"="));
-            if (p->options.htcp_only_clr)
-                storeAppendPrintf(sentry, "%sonly-clr",(doneopts++>0?",":"="));
+            bool doneopts = false;
+            if (p->options.htcp_oldsquid) {
+                storeAppendPrintf(sentry, "oldsquid");
+                doneopts = true;
+            }
+            if (p->options.htcp_no_clr) {
+                storeAppendPrintf(sentry, "%sno-clr",(doneopts?",":"="));
+                doneopts = true;
+            }
+            if (p->options.htcp_no_purge_clr) {
+                storeAppendPrintf(sentry, "%sno-purge-clr",(doneopts?",":"="));
+                doneopts = true;
+            }
+            if (p->options.htcp_only_clr) {
+                storeAppendPrintf(sentry, "%sonly-clr",(doneopts?",":"="));
+                //doneopts = true; // uncomment if more opts are added
+            }
         }
     }
 #endif
 
     if (p->options.no_netdb_exchange)
         storeAppendPrintf(sentry, " no-netdb-exchange");
