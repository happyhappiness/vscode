@@ -1320,17 +1320,19 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         {
             return "Wrong hostname or port for slave.";
         }
-    } else if (!strcasecmp(argv[0],"known-sentinel") && argc == 4) {
+    } else if (!strcasecmp(argv[0],"known-sentinel") &&
+               (argc == 4 || argc == 5)) {
         sentinelRedisInstance *si;
 
-        /* known-sentinel <name> <ip> <port> */
+        /* known-sentinel <name> <ip> <port> [runid] */
         ri = sentinelGetMasterByName(argv[1]);
         if (!ri) return "No such master with specified name.";
         if ((si = createSentinelRedisInstance(NULL,SRI_SENTINEL,argv[2],
                     atoi(argv[3]), ri->quorum, ri)) == NULL)
         {
             return "Wrong hostname or port for sentinel.";
         }
+        if (argc == 5) si->runid = sdsnew(argv[4]);
     } else {
         return "Unrecognized sentinel configuration statement.";
     }
@@ -1442,8 +1444,10 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
         while((de = dictNext(di2)) != NULL) {
             ri = dictGetVal(de);
             line = sdscatprintf(sdsempty(),
-                "sentinel known-sentinel %s %s %d",
-                master->name, ri->addr->ip, ri->addr->port);
+                "sentinel known-sentinel %s %s %d%s%s",
+                master->name, ri->addr->ip, ri->addr->port,
+                ri->runid ? " " : "",
+                ri->runid ? ri->runid : "");
             rewriteConfigRewriteLine(state,"sentinel",line,1);
         }
         dictReleaseIterator(di2);