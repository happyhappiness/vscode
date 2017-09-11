@@ -53,6 +53,7 @@
 #include <sys/resource.h>
 #include <sys/utsname.h>
 #include <locale.h>
+#include <sys/sysctl.h>
 
 /* Our shared "common" objects */
 
@@ -288,6 +289,7 @@ struct redisCommand redisCommandTable[] = {
 };
 
 struct evictionPoolEntry *evictionPoolAlloc(void);
+static size_t getMemorySize(void);
 
 /*============================ Utility functions ============================ */
 
@@ -1759,6 +1761,7 @@ void initServer(void) {
     server.clients_waiting_acks = listCreate();
     server.get_ack_from_slaves = 0;
     server.clients_paused = 0;
+    server.system_memory_size = getMemorySize();
 
     createSharedObjects();
     adjustOpenFilesLimit();
@@ -2479,7 +2482,6 @@ void timeCommand(redisClient *c) {
     addReplyBulkLongLong(c,tv.tv_usec);
 }
 
-
 /* Helper function for addReplyCommand() to output flags. */
 int addReplyCommandFlag(redisClient *c, struct redisCommand *cmd, int f, char *reply) {
     if (cmd->flags & f) {
@@ -2570,6 +2572,54 @@ void commandCommand(redisClient *c) {
     }
 }
 
+/**
+ * Returns the size of physical memory (RAM) in bytes.
+ * It looks ugly, but this is the cleanest way to achive cross platform results.
+ * Cleaned up from:
+ * http://nadeausoftware.com/articles/2012/09/c_c_tip_how_get_physical_memory_size_system
+ */
+size_t getMemorySize() {
+#if defined(__unix__) || defined(__unix) || defined(unix) || \
+    (defined(__APPLE__) && defined(__MACH__))
+#if defined(CTL_HW) && (defined(HW_MEMSIZE) || defined(HW_PHYSMEM64))
+    int mib[2];
+    mib[0] = CTL_HW;
+#if defined(HW_MEMSIZE)
+    mib[1] = HW_MEMSIZE;            /* OSX. --------------------- */
+#elif defined(HW_PHYSMEM64)
+    mib[1] = HW_PHYSMEM64;          /* NetBSD, OpenBSD. --------- */
+#endif
+    int64_t size = 0;               /* 64-bit */
+    size_t len = sizeof(size);
+    if (sysctl( mib, 2, &size, &len, NULL, 0) == 0)
+        return (size_t)size;
+    return 0L;          /* Failed? */
+
+#elif defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)
+    /* FreeBSD, Linux, OpenBSD, and Solaris. -------------------- */
+    return (size_t)sysconf(_SC_PHYS_PAGES) * (size_t)sysconf(_SC_PAGESIZE);
+
+#elif defined(CTL_HW) && (defined(HW_PHYSMEM) || defined(HW_REALMEM))
+    /* DragonFly BSD, FreeBSD, NetBSD, OpenBSD, and OSX. -------- */
+    int mib[2];
+    mib[0] = CTL_HW;
+#if defined(HW_REALMEM)
+    mib[1] = HW_REALMEM;        /* FreeBSD. ----------------- */
+#elif defined(HW_PYSMEM)
+    mib[1] = HW_PHYSMEM;        /* Others. ------------------ */
+#endif
+    unsigned int size = 0;      /* 32-bit */
+    size_t len = sizeof(size);
+    if (sysctl(mib, 2, &size, &len, NULL, 0) == 0)
+        return (size_t)size;
+    return 0L;          /* Failed? */
+#endif /* sysctl and sysconf variants */
+
+#else
+    return 0L;          /* Unknown OS. */
+#endif
+}
+
 /* Convert an amount of bytes into a human readable string in the form
  * of 100B, 2G, 100M, 4K, and so forth. */
 void bytesToHuman(char *s, unsigned long long n) {
@@ -2698,7 +2748,10 @@ sds genRedisInfoString(char *section) {
     if (allsections || defsections || !strcasecmp(section,"memory")) {
         char hmem[64];
         char peak_hmem[64];
+        char total_system_hmem[64];
         size_t zmalloc_used = zmalloc_used_memory();
+        size_t total_system_mem = server.system_memory_size;
+        char *evict_policy = maxmemoryToString();
 
         /* Peak memory is updated from time to time by serverCron() so it
          * may happen that the instantaneous value is slightly bigger than
@@ -2709,6 +2762,8 @@ sds genRedisInfoString(char *section) {
 
         bytesToHuman(hmem,zmalloc_used);
         bytesToHuman(peak_hmem,server.stat_peak_memory);
+        bytesToHuman(total_system_hmem,total_system_mem);
+
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Memory\r\n"
@@ -2717,17 +2772,23 @@ sds genRedisInfoString(char *section) {
             "used_memory_rss:%zu\r\n"
             "used_memory_peak:%zu\r\n"
             "used_memory_peak_human:%s\r\n"
+            "total_system_memory:%lu\r\n"
+            "total_system_memory_human:%s\r\n"
             "used_memory_lua:%lld\r\n"
             "mem_fragmentation_ratio:%.2f\r\n"
-            "mem_allocator:%s\r\n",
+            "mem_allocator:%s\r\n"
+            "maxmemory_policy:%s\r\n",
             zmalloc_used,
             hmem,
             server.resident_set_size,
             server.stat_peak_memory,
             peak_hmem,
+            (unsigned long)total_system_mem,
+            total_system_hmem,
             ((long long)lua_gc(server.lua,LUA_GCCOUNT,0))*1024LL,
             zmalloc_get_fragmentation_ratio(server.resident_set_size),
-            ZMALLOC_LIB
+            ZMALLOC_LIB,
+            evict_policy
             );
     }
 