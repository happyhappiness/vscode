@@ -88,8 +88,8 @@ int clusterLoadConfig(char *filename) {
             p = strchr(s,',');
             if (p) *p = '\0';
             if (!strcasecmp(s,"myself")) {
-                redisAssert(server.cluster.myself == NULL);
-                server.cluster.myself = n;
+                redisAssert(server.cluster->myself == NULL);
+                server.cluster->myself = n;
                 n->flags |= REDIS_NODE_MYSELF;
             } else if (!strcasecmp(s,"master")) {
                 n->flags |= REDIS_NODE_MASTER;
@@ -149,9 +149,9 @@ int clusterLoadConfig(char *filename) {
                     clusterAddNode(cn);
                 }
                 if (direction == '>') {
-                    server.cluster.migrating_slots_to[slot] = cn;
+                    server.cluster->migrating_slots_to[slot] = cn;
                 } else {
-                    server.cluster.importing_slots_from[slot] = cn;
+                    server.cluster->importing_slots_from[slot] = cn;
                 }
                 continue;
             } else if ((p = strchr(argv[j],'-')) != NULL) {
@@ -170,9 +170,9 @@ int clusterLoadConfig(char *filename) {
     fclose(fp);
 
     /* Config sanity check */
-    redisAssert(server.cluster.myself != NULL);
+    redisAssert(server.cluster->myself != NULL);
     redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s",
-        server.cluster.myself->name);
+        server.cluster->myself->name);
     clusterUpdateState();
     return REDIS_OK;
 
@@ -190,7 +190,7 @@ int clusterSaveConfig(void) {
     sds ci = clusterGenNodesDescription();
     int fd;
     
-    if ((fd = open(server.cluster.configfile,O_WRONLY|O_CREAT|O_TRUNC,0644))
+    if ((fd = open(server.cluster_configfile,O_WRONLY|O_CREAT|O_TRUNC,0644))
         == -1) goto err;
     if (write(fd,ci,sdslen(ci)) != (ssize_t)sdslen(ci)) goto err;
     close(fd);
@@ -212,23 +212,24 @@ void clusterSaveConfigOrDie(void) {
 void clusterInit(void) {
     int saveconf = 0;
 
-    server.cluster.myself = NULL;
-    server.cluster.state = REDIS_CLUSTER_FAIL;
-    server.cluster.nodes = dictCreate(&clusterNodesDictType,NULL);
-    server.cluster.node_timeout = 15;
-    memset(server.cluster.migrating_slots_to,0,
-        sizeof(server.cluster.migrating_slots_to));
-    memset(server.cluster.importing_slots_from,0,
-        sizeof(server.cluster.importing_slots_from));
-    memset(server.cluster.slots,0,
-        sizeof(server.cluster.slots));
-    if (clusterLoadConfig(server.cluster.configfile) == REDIS_ERR) {
+    server.cluster = zmalloc(sizeof(clusterState));
+    server.cluster->myself = NULL;
+    server.cluster->state = REDIS_CLUSTER_FAIL;
+    server.cluster->nodes = dictCreate(&clusterNodesDictType,NULL);
+    server.cluster->node_timeout = 15;
+    memset(server.cluster->migrating_slots_to,0,
+        sizeof(server.cluster->migrating_slots_to));
+    memset(server.cluster->importing_slots_from,0,
+        sizeof(server.cluster->importing_slots_from));
+    memset(server.cluster->slots,0,
+        sizeof(server.cluster->slots));
+    if (clusterLoadConfig(server.cluster_configfile) == REDIS_ERR) {
         /* No configuration found. We will just use the random name provided
          * by the createClusterNode() function. */
-        server.cluster.myself = createClusterNode(NULL,REDIS_NODE_MYSELF);
+        server.cluster->myself = createClusterNode(NULL,REDIS_NODE_MYSELF);
         redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
-            server.cluster.myself->name);
-        clusterAddNode(server.cluster.myself);
+            server.cluster->myself->name);
+        clusterAddNode(server.cluster->myself);
         saveconf = 1;
     }
     if (saveconf) clusterSaveConfigOrDie();
@@ -241,7 +242,7 @@ void clusterInit(void) {
     }
     if (aeCreateFileEvent(server.el, server.cfd, AE_READABLE,
         clusterAcceptHandler, NULL) == AE_ERR) redisPanic("Unrecoverable error creating Redis Cluster file event.");
-    server.cluster.slots_to_keys = zslCreate();
+    server.cluster->slots_to_keys = zslCreate();
 }
 
 /* -----------------------------------------------------------------------------
@@ -373,7 +374,7 @@ void freeClusterNode(clusterNode *n) {
     sds nodename;
     
     nodename = sdsnewlen(n->name, REDIS_CLUSTER_NAMELEN);
-    redisAssert(dictDelete(server.cluster.nodes,nodename) == DICT_OK);
+    redisAssert(dictDelete(server.cluster->nodes,nodename) == DICT_OK);
     sdsfree(nodename);
     if (n->slaveof) clusterNodeRemoveSlave(n->slaveof, n);
     if (n->link) freeClusterLink(n->link);
@@ -384,7 +385,7 @@ void freeClusterNode(clusterNode *n) {
 int clusterAddNode(clusterNode *node) {
     int retval;
     
-    retval = dictAdd(server.cluster.nodes,
+    retval = dictAdd(server.cluster->nodes,
             sdsnewlen(node->name,REDIS_CLUSTER_NAMELEN), node);
     return (retval == DICT_OK) ? REDIS_OK : REDIS_ERR;
 }
@@ -394,7 +395,7 @@ clusterNode *clusterLookupNode(char *name) {
     sds s = sdsnewlen(name, REDIS_CLUSTER_NAMELEN);
     struct dictEntry *de;
 
-    de = dictFind(server.cluster.nodes,s);
+    de = dictFind(server.cluster->nodes,s);
     sdsfree(s);
     if (de == NULL) return NULL;
     return dictGetVal(de);
@@ -410,7 +411,7 @@ void clusterRenameNode(clusterNode *node, char *newname) {
    
     redisLog(REDIS_DEBUG,"Renaming node %.40s into %.40s",
         node->name, newname);
-    retval = dictDelete(server.cluster.nodes, s);
+    retval = dictDelete(server.cluster->nodes, s);
     sdsfree(s);
     redisAssert(retval == DICT_OK);
     memcpy(node->name, newname, REDIS_CLUSTER_NAMELEN);
@@ -664,11 +665,11 @@ int clusterProcessPacket(clusterLink *link) {
             if (newslots) {
                 for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
                     if (clusterNodeGetSlotBit(sender,j)) {
-                        if (server.cluster.slots[j] == sender) continue;
-                        if (server.cluster.slots[j] == NULL ||
-                            server.cluster.slots[j]->flags & REDIS_NODE_FAIL)
+                        if (server.cluster->slots[j] == sender) continue;
+                        if (server.cluster->slots[j] == NULL ||
+                            server.cluster->slots[j]->flags & REDIS_NODE_FAIL)
                         {
-                            server.cluster.slots[j] = sender;
+                            server.cluster->slots[j] = sender;
                             update_state = update_config = 1;
                         }
                     }
@@ -811,7 +812,7 @@ void clusterBroadcastMessage(void *buf, size_t len) {
     dictIterator *di;
     dictEntry *de;
 
-    di = dictGetIterator(server.cluster.nodes);
+    di = dictGetIterator(server.cluster->nodes);
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
 
@@ -828,16 +829,16 @@ void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
 
     memset(hdr,0,sizeof(*hdr));
     hdr->type = htons(type);
-    memcpy(hdr->sender,server.cluster.myself->name,REDIS_CLUSTER_NAMELEN);
-    memcpy(hdr->myslots,server.cluster.myself->slots,
+    memcpy(hdr->sender,server.cluster->myself->name,REDIS_CLUSTER_NAMELEN);
+    memcpy(hdr->myslots,server.cluster->myself->slots,
         sizeof(hdr->myslots));
     memset(hdr->slaveof,0,REDIS_CLUSTER_NAMELEN);
-    if (server.cluster.myself->slaveof != NULL) {
-        memcpy(hdr->slaveof,server.cluster.myself->slaveof->name,
+    if (server.cluster->myself->slaveof != NULL) {
+        memcpy(hdr->slaveof,server.cluster->myself->slaveof->name,
                                     REDIS_CLUSTER_NAMELEN);
     }
     hdr->port = htons(server.port);
-    hdr->state = server.cluster.state;
+    hdr->state = server.cluster->state;
     memset(hdr->configdigest,0,32); /* FIXME: set config digest */
 
     if (type == CLUSTERMSG_TYPE_FAIL) {
@@ -860,22 +861,22 @@ void clusterSendPing(clusterLink *link, int type) {
      * message to). Every time we add a node we decrement the counter, so when
      * it will drop to <= zero we know there is no more gossip info we can
      * send. */
-    int freshnodes = dictSize(server.cluster.nodes)-2;
+    int freshnodes = dictSize(server.cluster->nodes)-2;
 
     if (link->node && type == CLUSTERMSG_TYPE_PING)
         link->node->ping_sent = time(NULL);
     clusterBuildMessageHdr(hdr,type);
         
     /* Populate the gossip fields */
     while(freshnodes > 0 && gossipcount < 3) {
-        struct dictEntry *de = dictGetRandomKey(server.cluster.nodes);
+        struct dictEntry *de = dictGetRandomKey(server.cluster->nodes);
         clusterNode *this = dictGetVal(de);
         clusterMsgDataGossip *gossip;
         int j;
 
         /* Not interesting to gossip about ourself.
          * Nor to send gossip info about HANDSHAKE state nodes (zero info). */
-        if (this == server.cluster.myself ||
+        if (this == server.cluster->myself ||
             this->flags & REDIS_NODE_HANDSHAKE) {
                 freshnodes--; /* otherwise we may loop forever. */
                 continue;
@@ -988,7 +989,7 @@ void clusterCron(void) {
     clusterNode *min_ping_node = NULL;
 
     /* Check if we have disconnected nodes and re-establish the connection. */
-    di = dictGetIterator(server.cluster.nodes);
+    di = dictGetIterator(server.cluster->nodes);
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
 
@@ -1024,7 +1025,7 @@ void clusterCron(void) {
     /* Ping some random node. Check a few random nodes and ping the one with
      * the oldest ping_sent time */
     for (j = 0; j < 5; j++) {
-        de = dictGetRandomKey(server.cluster.nodes);
+        de = dictGetRandomKey(server.cluster->nodes);
         clusterNode *this = dictGetVal(de);
 
         if (this->link == NULL) continue;
@@ -1040,7 +1041,7 @@ void clusterCron(void) {
     }
 
     /* Iterate nodes to check if we need to flag something as failing */
-    di = dictGetIterator(server.cluster.nodes);
+    di = dictGetIterator(server.cluster->nodes);
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
         int delay;
@@ -1054,7 +1055,7 @@ void clusterCron(void) {
             node->ping_sent <= node->pong_received) continue;
 
         delay = time(NULL) - node->pong_received;
-        if (delay < server.cluster.node_timeout) {
+        if (delay < server.cluster->node_timeout) {
             /* The PFAIL condition can be reversed without external
              * help if it is not transitive (that is, if it does not
              * turn into a FAIL state).
@@ -1119,19 +1120,19 @@ int clusterNodeGetSlotBit(clusterNode *n, int slot) {
 int clusterAddSlot(clusterNode *n, int slot) {
     if (clusterNodeSetSlotBit(n,slot) != 0)
         return REDIS_ERR;
-    server.cluster.slots[slot] = n;
+    server.cluster->slots[slot] = n;
     return REDIS_OK;
 }
 
 /* Delete the specified slot marking it as unassigned.
  * Returns REDIS_OK if the slot was assigned, otherwise if the slot was
  * already unassigned REDIS_ERR is returned. */
 int clusterDelSlot(int slot) {
-    clusterNode *n = server.cluster.slots[slot];
+    clusterNode *n = server.cluster->slots[slot];
 
     if (!n) return REDIS_ERR;
     redisAssert(clusterNodeClearSlotBit(n,slot) == 1);
-    server.cluster.slots[slot] = NULL;
+    server.cluster->slots[slot] = NULL;
     return REDIS_OK;
 }
 
@@ -1143,21 +1144,21 @@ void clusterUpdateState(void) {
     int j;
 
     for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
-        if (server.cluster.slots[j] == NULL ||
-            server.cluster.slots[j]->flags & (REDIS_NODE_FAIL))
+        if (server.cluster->slots[j] == NULL ||
+            server.cluster->slots[j]->flags & (REDIS_NODE_FAIL))
         {
             ok = 0;
             break;
         }
     }
     if (ok) {
-        if (server.cluster.state == REDIS_CLUSTER_NEEDHELP) {
-            server.cluster.state = REDIS_CLUSTER_NEEDHELP;
+        if (server.cluster->state == REDIS_CLUSTER_NEEDHELP) {
+            server.cluster->state = REDIS_CLUSTER_NEEDHELP;
         } else {
-            server.cluster.state = REDIS_CLUSTER_OK;
+            server.cluster->state = REDIS_CLUSTER_OK;
         }
     } else {
-        server.cluster.state = REDIS_CLUSTER_FAIL;
+        server.cluster->state = REDIS_CLUSTER_FAIL;
     }
 }
 
@@ -1171,7 +1172,7 @@ sds clusterGenNodesDescription(void) {
     dictEntry *de;
     int j, start;
 
-    di = dictGetIterator(server.cluster.nodes);
+    di = dictGetIterator(server.cluster->nodes);
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
 
@@ -1230,12 +1231,12 @@ sds clusterGenNodesDescription(void) {
          * instances. */
         if (node->flags & REDIS_NODE_MYSELF) {
             for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
-                if (server.cluster.migrating_slots_to[j]) {
+                if (server.cluster->migrating_slots_to[j]) {
                     ci = sdscatprintf(ci," [%d->-%.40s]",j,
-                        server.cluster.migrating_slots_to[j]->name);
-                } else if (server.cluster.importing_slots_from[j]) {
+                        server.cluster->migrating_slots_to[j]->name);
+                } else if (server.cluster->importing_slots_from[j]) {
                     ci = sdscatprintf(ci," [%d-<-%.40s]",j,
-                        server.cluster.importing_slots_from[j]->name);
+                        server.cluster->importing_slots_from[j]->name);
                 }
             }
         }
@@ -1311,11 +1312,11 @@ void clusterCommand(redisClient *c) {
                 zfree(slots);
                 return;
             }
-            if (del && server.cluster.slots[slot] == NULL) {
+            if (del && server.cluster->slots[slot] == NULL) {
                 addReplyErrorFormat(c,"Slot %d is already unassigned", slot);
                 zfree(slots);
                 return;
-            } else if (!del && server.cluster.slots[slot]) {
+            } else if (!del && server.cluster->slots[slot]) {
                 addReplyErrorFormat(c,"Slot %d is already busy", slot);
                 zfree(slots);
                 return;
@@ -1333,11 +1334,11 @@ void clusterCommand(redisClient *c) {
 
                 /* If this slot was set as importing we can clear this 
                  * state as now we are the real owner of the slot. */
-                if (server.cluster.importing_slots_from[j])
-                    server.cluster.importing_slots_from[j] = NULL;
+                if (server.cluster->importing_slots_from[j])
+                    server.cluster->importing_slots_from[j] = NULL;
 
                 retval = del ? clusterDelSlot(j) :
-                               clusterAddSlot(server.cluster.myself,j);
+                               clusterAddSlot(server.cluster->myself,j);
                 redisAssertWithInfo(c,NULL,retval == REDIS_OK);
             }
         }
@@ -1356,7 +1357,7 @@ void clusterCommand(redisClient *c) {
         if ((slot = getSlotOrReply(c,c->argv[2])) == -1) return;
 
         if (!strcasecmp(c->argv[3]->ptr,"migrating") && c->argc == 5) {
-            if (server.cluster.slots[slot] != server.cluster.myself) {
+            if (server.cluster->slots[slot] != server.cluster->myself) {
                 addReplyErrorFormat(c,"I'm not the owner of hash slot %u",slot);
                 return;
             }
@@ -1365,9 +1366,9 @@ void clusterCommand(redisClient *c) {
                     (char*)c->argv[4]->ptr);
                 return;
             }
-            server.cluster.migrating_slots_to[slot] = n;
+            server.cluster->migrating_slots_to[slot] = n;
         } else if (!strcasecmp(c->argv[3]->ptr,"importing") && c->argc == 5) {
-            if (server.cluster.slots[slot] == server.cluster.myself) {
+            if (server.cluster->slots[slot] == server.cluster->myself) {
                 addReplyErrorFormat(c,
                     "I'm already the owner of hash slot %u",slot);
                 return;
@@ -1377,11 +1378,11 @@ void clusterCommand(redisClient *c) {
                     (char*)c->argv[3]->ptr);
                 return;
             }
-            server.cluster.importing_slots_from[slot] = n;
+            server.cluster->importing_slots_from[slot] = n;
         } else if (!strcasecmp(c->argv[3]->ptr,"stable") && c->argc == 4) {
             /* CLUSTER SETSLOT <SLOT> STABLE */
-            server.cluster.importing_slots_from[slot] = NULL;
-            server.cluster.migrating_slots_to[slot] = NULL;
+            server.cluster->importing_slots_from[slot] = NULL;
+            server.cluster->migrating_slots_to[slot] = NULL;
         } else if (!strcasecmp(c->argv[3]->ptr,"node") && c->argc == 5) {
             /* CLUSTER SETSLOT <SLOT> NODE <NODE ID> */
             clusterNode *n = clusterLookupNode(c->argv[4]->ptr);
@@ -1390,8 +1391,8 @@ void clusterCommand(redisClient *c) {
                 (char*)c->argv[4]->ptr);
             /* If this hash slot was served by 'myself' before to switch
              * make sure there are no longer local keys for this hash slot. */
-            if (server.cluster.slots[slot] == server.cluster.myself &&
-                n != server.cluster.myself)
+            if (server.cluster->slots[slot] == server.cluster->myself &&
+                n != server.cluster->myself)
             {
                 int numkeys;
                 robj **keys;
@@ -1407,14 +1408,14 @@ void clusterCommand(redisClient *c) {
             /* If this node was the slot owner and the slot was marked as
              * migrating, assigning the slot to another node will clear
              * the migratig status. */
-            if (server.cluster.slots[slot] == server.cluster.myself &&
-                server.cluster.migrating_slots_to[slot])
-                server.cluster.migrating_slots_to[slot] = NULL;
+            if (server.cluster->slots[slot] == server.cluster->myself &&
+                server.cluster->migrating_slots_to[slot])
+                server.cluster->migrating_slots_to[slot] = NULL;
 
             /* If this node was importing this slot, assigning the slot to
              * itself also clears the importing status. */
-            if (n == server.cluster.myself && server.cluster.importing_slots_from[slot])
-                server.cluster.importing_slots_from[slot] = NULL;
+            if (n == server.cluster->myself && server.cluster->importing_slots_from[slot])
+                server.cluster->importing_slots_from[slot] = NULL;
 
             clusterDelSlot(slot);
             clusterAddSlot(n,slot);
@@ -1430,7 +1431,7 @@ void clusterCommand(redisClient *c) {
         int j;
 
         for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
-            clusterNode *n = server.cluster.slots[j];
+            clusterNode *n = server.cluster->slots[j];
 
             if (n == NULL) continue;
             slots_assigned++;
@@ -1450,12 +1451,12 @@ void clusterCommand(redisClient *c) {
             "cluster_slots_pfail:%d\r\n"
             "cluster_slots_fail:%d\r\n"
             "cluster_known_nodes:%lu\r\n"
-            , statestr[server.cluster.state],
+            , statestr[server.cluster->state],
             slots_assigned,
             slots_ok,
             slots_pfail,
             slots_fail,
-            dictSize(server.cluster.nodes)
+            dictSize(server.cluster->nodes)
         );
         addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
             (unsigned long)sdslen(info)));
@@ -1922,7 +1923,7 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
     if (cmd->proc == execCommand) {
         /* If REDIS_MULTI flag is not set EXEC is just going to return an
          * error. */
-        if (!(c->flags & REDIS_MULTI)) return server.cluster.myself;
+        if (!(c->flags & REDIS_MULTI)) return server.cluster->myself;
         ms = &c->mstate;
     } else {
         /* In order to have a single codepath create a fake Multi State
@@ -1956,7 +1957,7 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
                 firstkey = margv[keyindex[j]];
 
                 slot = keyHashSlot((char*)firstkey->ptr, sdslen(firstkey->ptr));
-                n = server.cluster.slots[slot];
+                n = server.cluster->slots[slot];
                 redisAssertWithInfo(c,firstkey,n != NULL);
             } else {
                 /* If it is not the first key, make sure it is exactly
@@ -1973,27 +1974,27 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
     if (ask) *ask = 0; /* This is the default. Set to 1 if needed later. */
     /* No key at all in command? then we can serve the request
      * without redirections. */
-    if (n == NULL) return server.cluster.myself;
+    if (n == NULL) return server.cluster->myself;
     if (hashslot) *hashslot = slot;
     /* This request is about a slot we are migrating into another instance?
      * Then we need to check if we have the key. If we have it we can reply.
      * If instead is a new key, we pass the request to the node that is
      * receiving the slot. */
-    if (n == server.cluster.myself &&
-        server.cluster.migrating_slots_to[slot] != NULL)
+    if (n == server.cluster->myself &&
+        server.cluster->migrating_slots_to[slot] != NULL)
     {
         if (lookupKeyRead(&server.db[0],firstkey) == NULL) {
             if (ask) *ask = 1;
-            return server.cluster.migrating_slots_to[slot];
+            return server.cluster->migrating_slots_to[slot];
         }
     }
     /* Handle the case in which we are receiving this hash slot from
      * another instance, so we'll accept the query even if in the table
      * it is assigned to a different node, but only if the client
      * issued an ASKING command before. */
-    if (server.cluster.importing_slots_from[slot] != NULL &&
+    if (server.cluster->importing_slots_from[slot] != NULL &&
         c->flags & REDIS_ASKING) {
-        return server.cluster.myself;
+        return server.cluster->myself;
     }
     /* It's not a -ASK case. Base case: just return the right node. */
     return n;