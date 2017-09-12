@@ -68,7 +68,7 @@ double R_Zero, R_PosInf, R_NegInf, R_Nan;
 /* Global vars */
 struct redisServer server; /* server global state */
 struct redisCommand *commandTable;
-struct redisCommand readonlyCommandTable[] = {
+struct redisCommand redisCommandTable[] = {
     {"get",getCommand,2,0,NULL,1,1,1,0,0},
     {"set",setCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
     {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
@@ -936,17 +936,29 @@ void initServer() {
  * we have on top of redis.c file. */
 void populateCommandTable(void) {
     int j;
-    int numcommands = sizeof(readonlyCommandTable)/sizeof(struct redisCommand);
+    int numcommands = sizeof(redisCommandTable)/sizeof(struct redisCommand);
 
     for (j = 0; j < numcommands; j++) {
-        struct redisCommand *c = readonlyCommandTable+j;
+        struct redisCommand *c = redisCommandTable+j;
         int retval;
 
         retval = dictAdd(server.commands, sdsnew(c->name), c);
         assert(retval == DICT_OK);
     }
 }
 
+void resetCommandTableStats(void) {
+    int numcommands = sizeof(redisCommandTable)/sizeof(struct redisCommand);
+    int j;
+
+    for (j = 0; j < numcommands; j++) {
+        struct redisCommand *c = redisCommandTable+j;
+
+        c->microseconds = 0;
+        c->calls = 0;
+    }
+}
+
 /* ====================== Commands lookup and execution ===================== */
 
 struct redisCommand *lookupCommand(sds name) {
@@ -1405,13 +1417,15 @@ sds genRedisInfoString(char *section) {
     if (allsections || !strcasecmp(section,"commandstats")) {
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info, "# Commandstats\r\n");
-        numcommands = sizeof(readonlyCommandTable)/sizeof(struct redisCommand);
+        numcommands = sizeof(redisCommandTable)/sizeof(struct redisCommand);
         for (j = 0; j < numcommands; j++) {
-            struct redisCommand *c = readonlyCommandTable+j;
+            struct redisCommand *c = redisCommandTable+j;
 
-            if (!c->microseconds) continue;
-            info = sdscatprintf(info,"cmdstat_%s:calls=%lld,usec=%lld\r\n",
-                c->name, c->calls, c->microseconds);
+            if (!c->calls) continue;
+            info = sdscatprintf(info,
+                "cmdstat_%s:calls=%lld,usec=%lld,usec_per_call=%.2f\r\n",
+                c->name, c->calls, c->microseconds,
+                (c->calls == 0) ? 0 : ((float)c->microseconds/c->calls));
         }
     }
 