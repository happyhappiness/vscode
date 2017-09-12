@@ -88,7 +88,7 @@ void replicationFeedMonitors(list *monitors, int dictid, robj **argv, int argc)
     struct timeval tv;
 
     gettimeofday(&tv,NULL);
-    cmdrepr = sdscatprintf(cmdrepr,"%ld.%ld ",(long)tv.tv_sec,(long)tv.tv_usec);
+    cmdrepr = sdscatprintf(cmdrepr,"%ld.%06ld ",(long)tv.tv_sec,(long)tv.tv_usec);
     if (dictid != 0) cmdrepr = sdscatprintf(cmdrepr,"(db %d) ", dictid);
 
     for (j = 0; j < argc; j++) {