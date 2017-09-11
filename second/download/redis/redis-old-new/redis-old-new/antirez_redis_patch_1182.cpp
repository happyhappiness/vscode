@@ -1543,6 +1543,7 @@ void clusterCommand(redisClient *c) {
     }
 
     if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
+        /* CLUSTER MEET <ip> <port> */
         clusterNode *n;
         struct sockaddr_in sa;
         long port;
@@ -1567,6 +1568,7 @@ void clusterCommand(redisClient *c) {
         clusterAddNode(n);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"nodes") && c->argc == 2) {
+        /* CLUSTER NODES */
         robj *o;
         sds ci = clusterGenNodesDescription();
 
@@ -1699,6 +1701,7 @@ void clusterCommand(redisClient *c) {
         clusterSaveConfigOrDie();
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
+        /* CLUSTER INFO */
         char *statestr[] = {"ok","fail","needhelp"};
         int slots_assigned = 0, slots_ok = 0, slots_pfail = 0, slots_fail = 0;
         int j;
@@ -1738,10 +1741,12 @@ void clusterCommand(redisClient *c) {
         addReplySds(c,info);
         addReply(c,shared.crlf);
     } else if (!strcasecmp(c->argv[1]->ptr,"keyslot") && c->argc == 3) {
+        /* CLUSTER KEYSLOT <key> */
         sds key = c->argv[2]->ptr;
 
         addReplyLongLong(c,keyHashSlot(key,sdslen(key)));
     } else if (!strcasecmp(c->argv[1]->ptr,"countkeysinslot") && c->argc == 3) {
+        /* CLUSTER COUNTKEYSINSLOT <slot> */
         long long slot;
 
         if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != REDIS_OK)
@@ -1752,6 +1757,7 @@ void clusterCommand(redisClient *c) {
         }
         addReplyLongLong(c,countKeysInSlot(slot));
     } else if (!strcasecmp(c->argv[1]->ptr,"getkeysinslot") && c->argc == 4) {
+        /* CLUSTER GETKEYSINSLOT <slot> <count> */
         long long maxkeys, slot;
         unsigned int numkeys, j;
         robj **keys;