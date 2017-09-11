@@ -2,6 +2,9 @@
 
 #include <signal.h>
 
+void SlotToKeyAdd(robj *key);
+void SlotToKeyDel(robj *key);
+
 /*-----------------------------------------------------------------------------
  * C-level DB API
  *----------------------------------------------------------------------------*/
@@ -131,6 +134,7 @@ int dbAdd(redisDb *db, robj *key, robj *val) {
         sds copy = sdsdup(key->ptr);
         dictAdd(db->dict, copy, val);
         if (server.ds_enabled) cacheSetKeyMayExist(db,key);
+        if (server.cluster_enabled) SlotToKeyAdd(key);
         return REDIS_OK;
     }
 }
@@ -146,6 +150,7 @@ int dbReplace(redisDb *db, robj *key, robj *val) {
     if ((oldval = dictFetchValue(db->dict,key->ptr)) == NULL) {
         sds copy = sdsdup(key->ptr);
         dictAdd(db->dict, copy, val);
+        if (server.cluster_enabled) SlotToKeyAdd(key);
         retval = 1;
     } else {
         dictReplace(db->dict, key->ptr, val);
@@ -198,7 +203,12 @@ int dbDelete(redisDb *db, robj *key) {
     /* Deleting an entry from the expires dict will not free the sds of
      * the key, because it is shared with the main dictionary. */
     if (dictSize(db->expires) > 0) dictDelete(db->expires,key->ptr);
-    return dictDelete(db->dict,key->ptr) == DICT_OK;
+    if (dictDelete(db->dict,key->ptr) == DICT_OK) {
+        if (server.cluster_enabled) SlotToKeyDel(key);
+        return 1;
+    } else {
+        return 0;
+    }
 }
 
 /* Empty the whole database.
@@ -307,6 +317,10 @@ void existsCommand(redisClient *c) {
 void selectCommand(redisClient *c) {
     int id = atoi(c->argv[1]->ptr);
 
+    if (server.cluster_enabled && id != 0) {
+        addReplyError(c,"SELECT is not allowed in cluster mode");
+        return;
+    }
     if (selectDb(c,id) == REDIS_ERR) {
         addReplyError(c,"invalid DB index");
     } else {
@@ -428,6 +442,11 @@ void moveCommand(redisClient *c) {
     redisDb *src, *dst;
     int srcid;
 
+    if (server.cluster_enabled) {
+        addReplyError(c,"MOVE is not allowed in cluster mode");
+        return;
+    }
+
     /* Obtain source and target DB pointers */
     src = c->db;
     srcid = c->db->id;
@@ -616,3 +635,108 @@ void persistCommand(redisClient *c) {
         }
     }
 }
+
+/* -----------------------------------------------------------------------------
+ * API to get key arguments from commands
+ * ---------------------------------------------------------------------------*/
+
+int *getKeysUsingCommandTable(struct redisCommand *cmd,robj **argv, int argc, int *numkeys) {
+    int j, i = 0, last, *keys;
+    REDIS_NOTUSED(argv);
+
+    if (cmd->firstkey == 0) {
+        *numkeys = 0;
+        return NULL;
+    }
+    last = cmd->lastkey;
+    if (last < 0) last = argc+last;
+    keys = zmalloc(sizeof(int)*((last - cmd->firstkey)+1));
+    for (j = cmd->firstkey; j <= last; j += cmd->keystep) {
+        redisAssert(j < argc);
+        keys[i++] = j;
+    }
+    *numkeys = i;
+    return keys;
+}
+
+int *getKeysFromCommand(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
+    if (cmd->getkeys_proc) {
+        return cmd->getkeys_proc(cmd,argv,argc,numkeys,flags);
+    } else {
+        return getKeysUsingCommandTable(cmd,argv,argc,numkeys);
+    }
+}
+
+void getKeysFreeResult(int *result) {
+    zfree(result);
+}
+
+int *noPreloadGetKeys(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
+    if (flags & REDIS_GETKEYS_PRELOAD) {
+        *numkeys = 0;
+        return NULL;
+    } else {
+        return getKeysUsingCommandTable(cmd,argv,argc,numkeys);
+    }
+}
+
+int *renameGetKeys(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
+    if (flags & REDIS_GETKEYS_PRELOAD) {
+        int *keys = zmalloc(sizeof(int));
+        *numkeys = 1;
+        keys[0] = 1;
+        return keys;
+    } else {
+        return getKeysUsingCommandTable(cmd,argv,argc,numkeys);
+    }
+}
+
+int *zunionInterGetKeys(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
+    int i, num, *keys;
+    REDIS_NOTUSED(cmd);
+    REDIS_NOTUSED(flags);
+
+    num = atoi(argv[2]->ptr);
+    /* Sanity check. Don't return any key if the command is going to
+     * reply with syntax error. */
+    if (num > (argc-3)) {
+        *numkeys = 0;
+        return NULL;
+    }
+    keys = zmalloc(sizeof(int)*num);
+    for (i = 0; i < num; i++) keys[i] = 3+i;
+    *numkeys = num;
+    return keys;
+}
+
+/* Slot to Key API. This is used by Redis Cluster in order to obtain in
+ * a fast way a key that belongs to a specified hash slot. This is useful
+ * while rehashing the cluster. */
+void SlotToKeyAdd(robj *key) {
+    unsigned int hashslot = keyHashSlot(key->ptr,sdslen(key->ptr));
+
+    zslInsert(server.cluster.slots_to_keys,hashslot,key);
+    incrRefCount(key);
+}
+
+void SlotToKeyDel(robj *key) {
+    unsigned int hashslot = keyHashSlot(key->ptr,sdslen(key->ptr));
+
+    zslDelete(server.cluster.slots_to_keys,hashslot,key);
+}
+
+unsigned int GetKeysInSlot(unsigned int hashslot, robj **keys, unsigned int count) {
+    zskiplistNode *n;
+    zrangespec range;
+    int j = 0;
+
+    range.min = range.max = hashslot;
+    range.minex = range.maxex = 0;
+    
+    n = zslFirstInRange(server.cluster.slots_to_keys, range);
+    while(n && n->score == hashslot && count--) {
+        keys[j++] = n->obj;
+        n = n->level[0].forward;
+    }
+    return j;
+}