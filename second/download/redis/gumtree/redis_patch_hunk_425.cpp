 /* This is only used after the handshake. When we connect a given IP/PORT
  * as a result of CLUSTER MEET we don't have the node name yet, so we
  * pick a random one, and will fix it when we receive the PONG request using
  * this function. */
 void clusterRenameNode(clusterNode *node, char *newname) {
     int retval;
-    sds s = sdsnewlen(node->name, REDIS_CLUSTER_NAMELEN);
+    sds s = sdsnewlen(node->name, CLUSTER_NAMELEN);
 
-    redisLog(REDIS_DEBUG,"Renaming node %.40s into %.40s",
+    serverLog(LL_DEBUG,"Renaming node %.40s into %.40s",
         node->name, newname);
     retval = dictDelete(server.cluster->nodes, s);
     sdsfree(s);
-    redisAssert(retval == DICT_OK);
-    memcpy(node->name, newname, REDIS_CLUSTER_NAMELEN);
+    serverAssert(retval == DICT_OK);
+    memcpy(node->name, newname, CLUSTER_NAMELEN);
     clusterAddNode(node);
 }
 
 /* -----------------------------------------------------------------------------
  * CLUSTER config epoch handling
  * -------------------------------------------------------------------------- */
