@@ -853,6 +853,120 @@ void objectCommand(client *c) {
     }
 }
 
+/* This structure is returned by the getMemoryOverheadData() function in
+ * order to return memory overhead information. */
+struct memoh {
+    size_t total_allocated;
+    size_t startup_allocated;
+    size_t repl_backlog;
+    size_t clients_slaves;
+    size_t clients_normal;
+    size_t aof_buffer;
+    size_t overhead_total;
+    size_t dataset;
+    size_t num_dbs;
+    struct {
+        size_t dbid;
+        size_t overhead_ht_main;
+        size_t overhead_ht_expires;
+    } *db;
+};
+
+/* Release data obtained with getMemoryOverheadData(). */
+void freeMemoryOverheadData(struct memoh *mh) {
+    zfree(mh->db);
+    zfree(mh);
+}
+
+/* Return a struct memoh filled with memory overhead information used
+ * for the MEMORY OVERHEAD and INFO command. The returned structure
+ * pointer should be freed calling freeMemoryOverheadData(). */
+struct memoh *getMemoryOverheadData(void) {
+    int j;
+    size_t mem_total = 0;
+    size_t mem = 0;
+    size_t zmalloc_used = zmalloc_used_memory();
+    struct memoh *mh = zcalloc(sizeof(*mh));
+
+    mh->total_allocated = zmalloc_used;
+    mh->startup_allocated = server.initial_memory_usage;
+    mem_total += server.initial_memory_usage;
+
+    mem = 0;
+    if (server.repl_backlog)
+        mem += zmalloc_size(server.repl_backlog);
+    mh->repl_backlog = mem;
+    mem_total += mem;
+
+    mem = 0;
+    if (listLength(server.slaves)) {
+        listIter li;
+        listNode *ln;
+
+        listRewind(server.slaves,&li);
+        while((ln = listNext(&li))) {
+            client *client = listNodeValue(ln);
+            mem += getClientOutputBufferMemoryUsage(client);
+            mem += sdsAllocSize(client->querybuf);
+            mem += sizeof(client);
+        }
+    }
+    mh->clients_slaves = mem;
+    mem_total+=mem;
+
+    mem = 0;
+    if (listLength(server.clients)) {
+        listIter li;
+        listNode *ln;
+
+        listRewind(server.clients,&li);
+        while((ln = listNext(&li))) {
+            client *client = listNodeValue(ln);
+            if (client->flags & CLIENT_SLAVE)
+                continue;
+            mem += getClientOutputBufferMemoryUsage(client);
+            mem += sdsAllocSize(client->querybuf);
+            mem += sizeof(client);
+        }
+    }
+    mh->clients_normal = mem;
+    mem_total+=mem;
+
+    mem = 0;
+    if (server.aof_state != AOF_OFF) {
+        mem += sdslen(server.aof_buf);
+        mem += aofRewriteBufferSize();
+    }
+    mh->aof_buffer = mem;
+    mem_total+=mem;
+
+    for (j = 0; j < server.dbnum; j++) {
+        redisDb *db = server.db+j;
+        long long keyscount = dictSize(db->dict);
+        if (keyscount==0) continue;
+
+        mh->db = zrealloc(mh->db,sizeof(mh->db[0])*(mh->num_dbs+1));
+        mh->db[mh->num_dbs].dbid = j;
+
+        mem = dictSize(db->dict) * sizeof(dictEntry) +
+              dictSlots(db->dict) * sizeof(dictEntry*) +
+              dictSize(db->dict) * sizeof(robj);
+        mh->db[mh->num_dbs].overhead_ht_main = mem;
+        mem_total+=mem;
+
+        mem = dictSize(db->expires) * sizeof(dictEntry) +
+              dictSlots(db->expires) * sizeof(dictEntry*);
+        mh->db[mh->num_dbs].overhead_ht_expires = mem;
+        mem_total+=mem;
+
+        mh->num_dbs++;
+    }
+
+    mh->overhead_total = mem_total;
+    mh->dataset = zmalloc_used - mem_total;
+    return mh;
+}
+
 /* The memory command will eventually be a complete interface for the
  * memory introspection capabilities of Redis.
  *
@@ -868,105 +982,48 @@ void memoryCommand(client *c) {
         usage += sizeof(dictEntry);
         addReplyLongLong(c,usage);
     } else if (!strcasecmp(c->argv[1]->ptr,"overhead") && c->argc == 2) {
-        int j;
-        size_t mem_total = 0;
-        size_t mem = 0;
-        size_t zmalloc_used = zmalloc_used_memory();
+        struct memoh *mh = getMemoryOverheadData();
 
-        int toplevel_keys = 8;
-        void *tlk = addDeferredMultiBulkLength(c);
+        addReplyMultiBulkLen(c,(8+mh->num_dbs)*2);
 
         addReplyBulkCString(c,"total.allocated");
-        addReplyLongLong(c,zmalloc_used);
+        addReplyLongLong(c,mh->total_allocated);
 
         addReplyBulkCString(c,"startup.allocated");
-        addReplyLongLong(c,server.initial_memory_usage);
-        mem_total += server.initial_memory_usage;
+        addReplyLongLong(c,mh->startup_allocated);
 
-        mem = 0;
-        if (server.repl_backlog)
-            mem += zmalloc_size(server.repl_backlog);
         addReplyBulkCString(c,"replication.backlog");
-        addReplyLongLong(c,mem);
-        mem_total += mem;
-
-        mem = 0;
-        if (listLength(server.slaves)) {
-            listIter li;
-            listNode *ln;
-
-            listRewind(server.slaves,&li);
-            while((ln = listNext(&li))) {
-                client *client = listNodeValue(ln);
-                mem += getClientOutputBufferMemoryUsage(client);
-                mem += sdsAllocSize(client->querybuf);
-                mem += sizeof(client);
-            }
-        }
+        addReplyLongLong(c,mh->repl_backlog);
+
         addReplyBulkCString(c,"clients.slaves");
-        addReplyLongLong(c,mem);
-        mem_total+=mem;
+        addReplyLongLong(c,mh->clients_slaves);
 
-        mem = 0;
-        if (listLength(server.clients)) {
-            listIter li;
-            listNode *ln;
-
-            listRewind(server.clients,&li);
-            while((ln = listNext(&li))) {
-                client *client = listNodeValue(ln);
-                if (client->flags & CLIENT_SLAVE)
-                    continue;
-                mem += getClientOutputBufferMemoryUsage(client);
-                mem += sdsAllocSize(client->querybuf);
-                mem += sizeof(client);
-            }
-        }
         addReplyBulkCString(c,"clients.normal");
-        addReplyLongLong(c,mem);
-        mem_total+=mem;
+        addReplyLongLong(c,mh->clients_normal);
 
-        mem = 0;
-        if (server.aof_state != AOF_OFF) {
-            mem += sdslen(server.aof_buf);
-            mem += aofRewriteBufferSize();
-        }
         addReplyBulkCString(c,"aof.buffer");
-        addReplyLongLong(c,mem);
-        mem_total+=mem;
-
-        for (j = 0; j < server.dbnum; j++) {
-            redisDb *db = server.db+j;
-            long long keyscount = dictSize(db->dict);
-            if (keyscount==0) continue;
+        addReplyLongLong(c,mh->aof_buffer);
 
+        for (size_t j = 0; j < mh->num_dbs; j++) {
             char dbname[32];
-            toplevel_keys++;
-            snprintf(dbname,sizeof(dbname),"db.%d",j);
+            snprintf(dbname,sizeof(dbname),"db.%zd",mh->db[j].dbid);
             addReplyBulkCString(c,dbname);
             addReplyMultiBulkLen(c,4);
 
-            mem = dictSize(db->dict) * sizeof(dictEntry) +
-                  dictSlots(db->dict) * sizeof(dictEntry*) +
-                  dictSize(db->dict) * sizeof(robj);
             addReplyBulkCString(c,"overhead.hashtable.main");
-            addReplyLongLong(c,mem);
-            mem_total+=mem;
+            addReplyLongLong(c,mh->db[j].overhead_ht_main);
 
-            mem = dictSize(db->expires) * sizeof(dictEntry) +
-                  dictSlots(db->expires) * sizeof(dictEntry*);
             addReplyBulkCString(c,"overhead.hashtable.expires");
-            addReplyLongLong(c,mem);
-            mem_total+=mem;
+            addReplyLongLong(c,mh->db[j].overhead_ht_expires);
         }
 
         addReplyBulkCString(c,"overhead.total");
-        addReplyLongLong(c,mem_total);
+        addReplyLongLong(c,mh->overhead_total);
 
         addReplyBulkCString(c,"dataset");
-        addReplyLongLong(c,zmalloc_used - mem_total);
+        addReplyLongLong(c,mh->dataset);
 
-        setDeferredMultiBulkLength(c,tlk,toplevel_keys*2);
+        freeMemoryOverheadData(mh);
     } else {
         addReplyError(c,"Syntax error. Try MEMORY [usage <key>] | [overhead]");
     }