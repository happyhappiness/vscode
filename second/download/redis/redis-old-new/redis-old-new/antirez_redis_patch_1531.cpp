@@ -1240,9 +1240,10 @@ void clusterCommand(redisClient *c) {
         clusterSaveConfigOrDie();
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"setslot") && c->argc >= 4) {
-        /* SETSLOT 10 MIGRATING <instance ID> */
-        /* SETSLOT 10 IMPORTING <instance ID> */
+        /* SETSLOT 10 MIGRATING <node ID> */
+        /* SETSLOT 10 IMPORTING <node ID> */
         /* SETSLOT 10 STABLE */
+        /* SETSLOT 10 NODE <node ID> */
         int slot;
         clusterNode *n;
 