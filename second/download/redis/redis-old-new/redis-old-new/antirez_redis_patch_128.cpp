@@ -936,6 +936,12 @@ struct redisMemOverhead *getMemoryOverheadData(void) {
 
     mh->overhead_total = mem_total;
     mh->dataset = zmalloc_used - mem_total;
+
+    size_t net_usage = 1;
+    if (zmalloc_used > mh->startup_allocated)
+        net_usage = zmalloc_used - mh->startup_allocated;
+    mh->dataset_perc = (float)mh->dataset*100/net_usage;
+
     return mh;
 }
 
@@ -974,7 +980,7 @@ void memoryCommand(client *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"overhead") && c->argc == 2) {
         struct redisMemOverhead *mh = getMemoryOverheadData();
 
-        addReplyMultiBulkLen(c,(8+mh->num_dbs)*2);
+        addReplyMultiBulkLen(c,(9+mh->num_dbs)*2);
 
         addReplyBulkCString(c,"total.allocated");
         addReplyLongLong(c,mh->total_allocated);
@@ -1010,11 +1016,20 @@ void memoryCommand(client *c) {
         addReplyBulkCString(c,"overhead.total");
         addReplyLongLong(c,mh->overhead_total);
 
-        addReplyBulkCString(c,"dataset");
+        addReplyBulkCString(c,"dataset.bytes");
         addReplyLongLong(c,mh->dataset);
 
+        addReplyBulkCString(c,"dataset.percentage");
+        addReplyDouble(c,mh->dataset_perc);
+
         freeMemoryOverheadData(mh);
+    } else if (!strcasecmp(c->argv[1]->ptr,"help") && c->argc == 2) {
+        addReplyMultiBulkLen(c,2);
+        addReplyBulkCString(c,
+        "MEMORY USAGE <key> [SAMPLES <count>] - Estimate memory usage of key");
+        addReplyBulkCString(c,
+        "MEMORY OVERHEAD                      - Show memory usage details");
     } else {
-        addReplyError(c,"Syntax error. Try MEMORY [usage <key>] | [overhead]");
+        addReplyError(c,"Syntax error. Try MEMORY HELP");
     }
 }