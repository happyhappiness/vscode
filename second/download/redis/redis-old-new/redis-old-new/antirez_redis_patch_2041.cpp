@@ -91,7 +91,7 @@ void replicationFeedMonitors(list *monitors, int dictid, robj **argv, int argc)
 
     for (j = 0; j < argc; j++) {
         if (argv[j]->encoding == REDIS_ENCODING_INT) {
-            cmdrepr = sdscatprintf(cmdrepr, "%ld", (long)argv[j]->ptr);
+            cmdrepr = sdscatprintf(cmdrepr, "\"%ld\"", (long)argv[j]->ptr);
         } else {
             cmdrepr = sdscatrepr(cmdrepr,(char*)argv[j]->ptr,
                         sdslen(argv[j]->ptr));