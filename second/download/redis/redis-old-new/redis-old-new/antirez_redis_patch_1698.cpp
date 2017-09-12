@@ -1,13 +1,16 @@
 #include "redis.h"
 
 #include <arpa/inet.h>
+#include <fcntl.h>
+#include <unistd.h>
 
 void clusterAcceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void clusterSendPing(clusterLink *link, int type);
 void clusterSendFail(char *nodename);
 void clusterUpdateState(void);
 int clusterNodeGetSlotBit(clusterNode *n, int slot);
+sds clusterGenNodesDescription(void);
 
 /* -----------------------------------------------------------------------------
  * Initialization
@@ -31,7 +34,8 @@ void clusterGetRandomName(char *p) {
 
 int clusterLoadConfig(char *filename) {
     FILE *fp = fopen(filename,"r");
-    
+   
+    return REDIS_ERR;
     if (fp == NULL) return REDIS_ERR;
     fclose(fp);
 
@@ -45,6 +49,25 @@ int clusterLoadConfig(char *filename) {
     exit(1);
 }
 
+/* Cluster node configuration is exactly the same as CLUSTER NODES output.
+ *
+ * This function writes the node config and returns 0, on error -1
+ * is returned. */
+int clusterSaveConfig(char *filename) {
+    sds ci = clusterGenNodesDescription();
+    int fd;
+    
+    if ((fd = open(filename,O_WRONLY|O_CREAT,0644)) == -1) goto err;
+    if (write(fd,ci,sdslen(ci)) != (ssize_t)sdslen(ci)) goto err;
+    close(fd);
+    sdsfree(ci);
+    return 0;
+
+err:
+    sdsfree(ci);
+    return -1;
+}
+
 void clusterInit(void) {
     server.cluster.myself = createClusterNode(NULL,REDIS_NODE_MYSELF);
     server.cluster.state = REDIS_CLUSTER_FAIL;
@@ -61,6 +84,10 @@ void clusterInit(void) {
          * by the createClusterNode() function. */
         redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
             server.cluster.myself->name);
+        if (clusterSaveConfig("cluster.conf") == -1) {
+            redisLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
+            exit(1);
+        }
     }
     clusterAddNode(server.cluster.myself);
     /* We need a listening TCP port for our cluster messaging needs */
@@ -874,6 +901,48 @@ void clusterUpdateState(void) {
  * CLUSTER command
  * -------------------------------------------------------------------------- */
 
+sds clusterGenNodesDescription(void) {
+    sds ci = sdsempty();
+    dictIterator *di;
+    dictEntry *de;
+
+    di = dictGetIterator(server.cluster.nodes);
+    while((de = dictNext(di)) != NULL) {
+        clusterNode *node = dictGetEntryVal(de);
+
+        /* Node coordinates */
+        ci = sdscatprintf(ci,"%.40s %s:%d ",
+            node->name,
+            node->ip,
+            node->port);
+
+        /* Flags */
+        if (node->flags == 0) ci = sdscat(ci,"noflags,");
+        if (node->flags & REDIS_NODE_MYSELF) ci = sdscat(ci,"myself,");
+        if (node->flags & REDIS_NODE_MASTER) ci = sdscat(ci,"master,");
+        if (node->flags & REDIS_NODE_SLAVE) ci = sdscat(ci,"slave,");
+        if (node->flags & REDIS_NODE_PFAIL) ci = sdscat(ci,"fail?,");
+        if (node->flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
+        if (node->flags & REDIS_NODE_HANDSHAKE) ci =sdscat(ci,"handshake,");
+        if (node->flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
+        if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
+
+        /* Slave of... or just "-" */
+        if (node->slaveof)
+            ci = sdscatprintf(ci,"%.40s ",node->slaveof->name);
+        else
+            ci = sdscatprintf(ci,"- ");
+
+        /* Latency from the POV of this node, link status */
+        ci = sdscatprintf(ci,"%ld %ld %s\n",
+            (long) node->ping_sent,
+            (long) node->pong_received,
+            node->link ? "connected" : "disconnected");
+    }
+    dictReleaseIterator(di);
+    return ci;
+}
+
 void clusterCommand(redisClient *c) {
     if (server.cluster_enabled == 0) {
         addReplyError(c,"This instance has cluster support disabled");
@@ -905,45 +974,9 @@ void clusterCommand(redisClient *c) {
         clusterAddNode(n);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"nodes") && c->argc == 2) {
-        sds ci = sdsempty();
-        dictIterator *di;
-        dictEntry *de;
         robj *o;
+        sds ci = clusterGenNodesDescription();
 
-        di = dictGetIterator(server.cluster.nodes);
-        while((de = dictNext(di)) != NULL) {
-            clusterNode *node = dictGetEntryVal(de);
-
-            /* Node coordinates */
-            ci = sdscatprintf(ci,"%.40s %s:%d ",
-                node->name,
-                node->ip,
-                node->port);
-
-            /* Flags */
-            if (node->flags == 0) ci = sdscat(ci,"noflags,");
-            if (node->flags & REDIS_NODE_MYSELF) ci = sdscat(ci,"myself,");
-            if (node->flags & REDIS_NODE_MASTER) ci = sdscat(ci,"master,");
-            if (node->flags & REDIS_NODE_SLAVE) ci = sdscat(ci,"slave,");
-            if (node->flags & REDIS_NODE_PFAIL) ci = sdscat(ci,"fail?,");
-            if (node->flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
-            if (node->flags & REDIS_NODE_HANDSHAKE) ci =sdscat(ci,"handshake,");
-            if (node->flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
-            if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
-
-            /* Slave of... or just "-" */
-            if (node->slaveof)
-                ci = sdscatprintf(ci,"%.40s ",node->slaveof->name);
-            else
-                ci = sdscatprintf(ci,"- ");
-
-            /* Latency from the POV of this node, link status */
-            ci = sdscatprintf(ci,"%ld %ld %s\n",
-                (long) node->ping_sent,
-                (long) node->pong_received,
-                node->link ? "connected" : "disconnected");
-        }
-        dictReleaseIterator(di);
         o = createObject(REDIS_STRING,ci);
         addReplyBulk(c,o);
         decrRefCount(o);