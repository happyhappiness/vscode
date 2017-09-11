@@ -811,6 +811,8 @@ struct redisMemOverhead *getMemoryOverheadData(void) {
     mh->total_allocated = zmalloc_used;
     mh->startup_allocated = server.initial_memory_usage;
     mh->peak_allocated = server.stat_peak_memory;
+    mh->fragmentation =
+        zmalloc_get_fragmentation_ratio(server.resident_set_size);
     mem_total += server.initial_memory_usage;
 
     mem = 0;
@@ -866,6 +868,7 @@ struct redisMemOverhead *getMemoryOverheadData(void) {
         long long keyscount = dictSize(db->dict);
         if (keyscount==0) continue;
 
+        mh->total_keys += keyscount;
         mh->db = zrealloc(mh->db,sizeof(mh->db[0])*(mh->num_dbs+1));
         mh->db[mh->num_dbs].dbid = j;
 
@@ -885,12 +888,15 @@ struct redisMemOverhead *getMemoryOverheadData(void) {
 
     mh->overhead_total = mem_total;
     mh->dataset = zmalloc_used - mem_total;
+    mh->peak_perc = (float)zmalloc_used*100/mh->peak_allocated;
 
+    /* Metrics computed after subtracting the startup memory from
+     * the total memory. */
     size_t net_usage = 1;
     if (zmalloc_used > mh->startup_allocated)
         net_usage = zmalloc_used - mh->startup_allocated;
     mh->dataset_perc = (float)mh->dataset*100/net_usage;
-    mh->peak_perc = (float)zmalloc_used*100/mh->peak_allocated;
+    mh->bytes_per_key = mh->total_keys ? (net_usage / mh->total_keys) : 0;
 
     return mh;
 }
@@ -903,6 +909,80 @@ void inputCatSds(void *result, const char *str) {
     *info = sdscat(*info, str);
 }
 
+/* This implements MEMORY DOCTOR. An human readable analysis of the Redis
+ * memory condition. */
+sds getMemoryDoctorReport(void) {
+    int empty = 0;          /* Instance is empty or almost empty. */
+    int big_peak = 0;       /* Memory peak is much larger than used mem. */
+    int high_frag = 0;      /* High fragmentation. */
+    int big_slave_buf = 0;  /* Slave buffers are too big. */
+    int big_client_buf = 0; /* Client buffers are too big. */
+    int num_reports = 0;
+    struct redisMemOverhead *mh = getMemoryOverheadData();
+
+    if (mh->total_allocated < (1024*1024*5)) {
+        empty = 1;
+        num_reports++;
+    } else {
+        /* Peak is > 150% of current used memory? */
+        if (((float)mh->peak_allocated / mh->total_allocated) > 1.5) {
+            big_peak = 1;
+            num_reports++;
+        }
+
+        /* Fragmentation is higher than 1.4? */
+        if (mh->fragmentation > 1.4) {
+            high_frag = 1;
+            num_reports++;
+        }
+
+        /* Clients using more than 200k each average? */
+        long numslaves = listLength(server.slaves);
+        long numclients = listLength(server.clients)-numslaves;
+        if (mh->clients_normal / numclients > (1024*200)) {
+            big_client_buf = 1;
+            num_reports++;
+        }
+
+        /* Slaves using more than 10 MB each? */
+        if (mh->clients_slaves / numslaves > (1024*1024*10)) {
+            big_slave_buf = 1;
+            num_reports++;
+        }
+    }
+
+    sds s;
+    if (num_reports == 0) {
+        s = sdsnew(
+        "Hi Sam, I can't find any memory issue in your instnace. "
+        "I can only account for what occurs on this base.");
+    } else if (empty == 1) {
+        s = sdsnew(
+        "Hi Sam, this instance is empty or is using very little memory, "
+        "my issues detector can't be used in these conditions. "
+        "Please, leave for your mission on Earth and fill it with some data. "
+        "The new Sam and I will be back to our programming as soon as I "
+        "finished rebooting.");
+    } else {
+        s = sdsnew("Sam, I detected a few issues in this Redis instance memory implants:\n\n");
+        if (big_peak) {
+            s = sdscat(s," * Peak memory: In the past this instance used more than 150% the memory that is currently using. The allocator is normally not able to release memory after a peak, so you can expect to see a big fragmentation ratio, however this is actually harmless and is only due to the memory peak, and if the Redis instance Resident Set Size (RSS) is currently bigger than expected, the memory will be used as soon as you fill the Redis instance with more data. If the memory peak was only occasional and you want to try to reclaim memory, please try the MEMORY PURGE command, otherwise the only other option is to shutdown and restart the instance.\n\n");
+        }
+        if (high_frag) {
+            s = sdscatprintf(s," * High fragmentation: This instance has a memory fragmentation greater than 1.4 (this means that the Resident Set Size of the Redis process is much larger than the sum of the logical allocations Redis performed). This problem is usually due either to a large peak memory (check if there is a peak memory entry above in the report) or may result from a workload that causes the allocator to fragment memory a lot. If the problem is a large peak memory, then there is no issue. Otherwise, make sure you are using the Jemalloc allocator and not the default libc malloc. Note: The currently used allocator is: %s\n\n", ZMALLOC_LIB);
+        }
+        if (big_slave_buf) {
+            s = sdscat(s," * Big slave buffers: The slave output buffers in this instance are greater than 10MB for each slave (on average). This likely means that there is some slave instance that is struggling receiving data, either because it is too slow or because of networking issues. As a result, data piles on the master output buffers. Please try to identify what slave is not receiving data correctly and why. You can use the INFO output in order to check the slaves delays and the CLIENT LIST command to check the output buffers of each slave.\n\n");
+        }
+        if (big_client_buf) {
+            s = sdscat(s," * Big client buffers: The clients output buffers in this instance are greater than 200K per client (on average). This may result from different causes, like Pub/Sub clients subscribed to channels bot not receiving data fast enough, so that data piles on the Redis instance output buffer, or clients sending commands with large replies or very large sequences of commands in the same pipeline. Please use the CLIENT LIST command in order to investigate the issue if it causes problems in your instance, or to understand better why certain clients are using a big amount of memory.\n\n");
+        }
+        s = sdscat(s,"I'm here to keep you safe, Sam. I want to help you.\n");
+    }
+    freeMemoryOverheadData(mh);
+    return s;
+}
+
 /* ======================= The OBJECT and MEMORY commands =================== */
 
 /* This is a helper function for the OBJECT command. We need to lookup keys
@@ -987,10 +1067,10 @@ void memoryCommand(client *c) {
         usage += sdsAllocSize(c->argv[1]->ptr);
         usage += sizeof(dictEntry);
         addReplyLongLong(c,usage);
-    } else if (!strcasecmp(c->argv[1]->ptr,"overhead") && c->argc == 2) {
+    } else if (!strcasecmp(c->argv[1]->ptr,"stats") && c->argc == 2) {
         struct redisMemOverhead *mh = getMemoryOverheadData();
 
-        addReplyMultiBulkLen(c,(11+mh->num_dbs)*2);
+        addReplyMultiBulkLen(c,(14+mh->num_dbs)*2);
 
         addReplyBulkCString(c,"peak.allocated");
         addReplyLongLong(c,mh->peak_allocated);
@@ -1029,6 +1109,12 @@ void memoryCommand(client *c) {
         addReplyBulkCString(c,"overhead.total");
         addReplyLongLong(c,mh->overhead_total);
 
+        addReplyBulkCString(c,"keys.count");
+        addReplyLongLong(c,mh->total_keys);
+
+        addReplyBulkCString(c,"keys.bytes-per-key");
+        addReplyLongLong(c,mh->bytes_per_key);
+
         addReplyBulkCString(c,"dataset.bytes");
         addReplyLongLong(c,mh->dataset);
 
@@ -1038,15 +1124,21 @@ void memoryCommand(client *c) {
         addReplyBulkCString(c,"peak.percentage");
         addReplyDouble(c,mh->peak_perc);
 
+        addReplyBulkCString(c,"fragmentation");
+        addReplyDouble(c,mh->fragmentation);
+
         freeMemoryOverheadData(mh);
-    } else if (!strcasecmp(c->argv[1]->ptr,"allocator-stats") && c->argc == 2) {
+    } else if (!strcasecmp(c->argv[1]->ptr,"malloc-stats") && c->argc == 2) {
 #if defined(USE_JEMALLOC)
         sds info = sdsempty();
         je_malloc_stats_print(inputCatSds, &info, NULL);
         addReplyBulkSds(c, info);
 #else
         addReplyBulkCString(c,"Stats not supported for the current allocator");
 #endif
+    } else if (!strcasecmp(c->argv[1]->ptr,"doctor") && c->argc == 2) {
+        sds report = getMemoryDoctorReport();
+        addReplyBulkSds(c,report);
     } else if (!strcasecmp(c->argv[1]->ptr,"purge") && c->argc == 2) {
 #if defined(USE_JEMALLOC)
         char tmp[32];
@@ -1069,11 +1161,11 @@ void memoryCommand(client *c) {
         addReplyBulkCString(c,
 "MEMORY USAGE <key> [SAMPLES <count>] - Estimate memory usage of key");
         addReplyBulkCString(c,
-"MEMORY OVERHEAD                      - Show memory usage details");
+"MEMORY STATS                         - Show memory usage details");
         addReplyBulkCString(c,
 "MEMORY PURGE                         - Ask the allocator to release memory");
         addReplyBulkCString(c,
-"MEMORY ALLOCATOR-STATS               - Show allocator internal stats");
+"MEMORY MALLOC-STATS                  - Show allocator internal stats");
     } else {
         addReplyError(c,"Syntax error. Try MEMORY HELP");
     }