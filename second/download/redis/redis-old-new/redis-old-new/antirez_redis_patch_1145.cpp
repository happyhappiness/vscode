@@ -1381,7 +1381,9 @@ void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
     sds line, flags;
 
     flags = keyspaceEventsFlagsToString(server.notify_keyspace_events);
-    line = sdscatprintf(sdsempty(),"%s %s", option, flags);
+    line = sdsnew(option);
+    line = sdscatlen(line, " ", 1);
+    line = sdscatrepr(line, flags, sdslen(flags));
     sdsfree(flags);
     rewriteConfigRewriteLine(state,option,line,force);
 }