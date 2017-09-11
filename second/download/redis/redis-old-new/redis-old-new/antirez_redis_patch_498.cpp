@@ -278,7 +278,7 @@ void debugCommand(redisClient *c) {
             addReplyError(c,"Error trying to load the RDB dump");
             return;
         }
-        redisLog(REDIS_WARNING,"DB reloaded by DEBUG RELOAD");
+        serverLog(REDIS_WARNING,"DB reloaded by DEBUG RELOAD");
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
         emptyDb(NULL);
@@ -287,7 +287,7 @@ void debugCommand(redisClient *c) {
             return;
         }
         server.dirty = 0; /* Prevent AOF / replication */
-        redisLog(REDIS_WARNING,"Append Only File loaded by DEBUG LOADAOF");
+        serverLog(REDIS_WARNING,"Append Only File loaded by DEBUG LOADAOF");
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"object") && c->argc == 3) {
         dictEntry *de;
@@ -472,13 +472,13 @@ void debugCommand(redisClient *c) {
 
 void _redisAssert(char *estr, char *file, int line) {
     bugReportStart();
-    redisLog(REDIS_WARNING,"=== ASSERTION FAILED ===");
-    redisLog(REDIS_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
+    serverLog(REDIS_WARNING,"=== ASSERTION FAILED ===");
+    serverLog(REDIS_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
 #ifdef HAVE_BACKTRACE
     server.assert_failed = estr;
     server.assert_file = file;
     server.assert_line = line;
-    redisLog(REDIS_WARNING,"(forcing SIGSEGV to print the bug report.)");
+    serverLog(REDIS_WARNING,"(forcing SIGSEGV to print the bug report.)");
 #endif
     *((char*)-1) = 'x';
 }
@@ -487,10 +487,10 @@ void _redisAssertPrintClientInfo(redisClient *c) {
     int j;
 
     bugReportStart();
-    redisLog(REDIS_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
-    redisLog(REDIS_WARNING,"client->flags = %d", c->flags);
-    redisLog(REDIS_WARNING,"client->fd = %d", c->fd);
-    redisLog(REDIS_WARNING,"client->argc = %d", c->argc);
+    serverLog(REDIS_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
+    serverLog(REDIS_WARNING,"client->flags = %d", c->flags);
+    serverLog(REDIS_WARNING,"client->fd = %d", c->fd);
+    serverLog(REDIS_WARNING,"client->argc = %d", c->argc);
     for (j=0; j < c->argc; j++) {
         char buf[128];
         char *arg;
@@ -502,39 +502,39 @@ void _redisAssertPrintClientInfo(redisClient *c) {
                 c->argv[j]->type, c->argv[j]->encoding);
             arg = buf;
         }
-        redisLog(REDIS_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
+        serverLog(REDIS_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
             j, arg, c->argv[j]->refcount);
     }
 }
 
-void redisLogObjectDebugInfo(robj *o) {
-    redisLog(REDIS_WARNING,"Object type: %d", o->type);
-    redisLog(REDIS_WARNING,"Object encoding: %d", o->encoding);
-    redisLog(REDIS_WARNING,"Object refcount: %d", o->refcount);
+void serverLogObjectDebugInfo(robj *o) {
+    serverLog(REDIS_WARNING,"Object type: %d", o->type);
+    serverLog(REDIS_WARNING,"Object encoding: %d", o->encoding);
+    serverLog(REDIS_WARNING,"Object refcount: %d", o->refcount);
     if (o->type == REDIS_STRING && sdsEncodedObject(o)) {
-        redisLog(REDIS_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
+        serverLog(REDIS_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
         if (sdslen(o->ptr) < 4096) {
             sds repr = sdscatrepr(sdsempty(),o->ptr,sdslen(o->ptr));
-            redisLog(REDIS_WARNING,"Object raw string content: %s", repr);
+            serverLog(REDIS_WARNING,"Object raw string content: %s", repr);
             sdsfree(repr);
         }
     } else if (o->type == REDIS_LIST) {
-        redisLog(REDIS_WARNING,"List length: %d", (int) listTypeLength(o));
+        serverLog(REDIS_WARNING,"List length: %d", (int) listTypeLength(o));
     } else if (o->type == REDIS_SET) {
-        redisLog(REDIS_WARNING,"Set size: %d", (int) setTypeSize(o));
+        serverLog(REDIS_WARNING,"Set size: %d", (int) setTypeSize(o));
     } else if (o->type == REDIS_HASH) {
-        redisLog(REDIS_WARNING,"Hash size: %d", (int) hashTypeLength(o));
+        serverLog(REDIS_WARNING,"Hash size: %d", (int) hashTypeLength(o));
     } else if (o->type == REDIS_ZSET) {
-        redisLog(REDIS_WARNING,"Sorted set size: %d", (int) zsetLength(o));
+        serverLog(REDIS_WARNING,"Sorted set size: %d", (int) zsetLength(o));
         if (o->encoding == REDIS_ENCODING_SKIPLIST)
-            redisLog(REDIS_WARNING,"Skiplist level: %d", (int) ((zset*)o->ptr)->zsl->level);
+            serverLog(REDIS_WARNING,"Skiplist level: %d", (int) ((zset*)o->ptr)->zsl->level);
     }
 }
 
 void _redisAssertPrintObject(robj *o) {
     bugReportStart();
-    redisLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
-    redisLogObjectDebugInfo(o);
+    serverLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
+    serverLogObjectDebugInfo(o);
 }
 
 void _redisAssertWithInfo(redisClient *c, robj *o, char *estr, char *file, int line) {
@@ -545,19 +545,19 @@ void _redisAssertWithInfo(redisClient *c, robj *o, char *estr, char *file, int l
 
 void _redisPanic(char *msg, char *file, int line) {
     bugReportStart();
-    redisLog(REDIS_WARNING,"------------------------------------------------");
-    redisLog(REDIS_WARNING,"!!! Software Failure. Press left mouse button to continue");
-    redisLog(REDIS_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
+    serverLog(REDIS_WARNING,"------------------------------------------------");
+    serverLog(REDIS_WARNING,"!!! Software Failure. Press left mouse button to continue");
+    serverLog(REDIS_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
 #ifdef HAVE_BACKTRACE
-    redisLog(REDIS_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
+    serverLog(REDIS_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
 #endif
-    redisLog(REDIS_WARNING,"------------------------------------------------");
+    serverLog(REDIS_WARNING,"------------------------------------------------");
     *((char*)-1) = 'x';
 }
 
 void bugReportStart(void) {
     if (server.bug_report_start == 0) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===");
         server.bug_report_start = 1;
     }
@@ -602,20 +602,20 @@ void logStackContent(void **sp) {
         unsigned long val = (unsigned long) sp[i];
 
         if (sizeof(long) == 4)
-            redisLog(REDIS_WARNING, "(%08lx) -> %08lx", addr, val);
+            serverLog(REDIS_WARNING, "(%08lx) -> %08lx", addr, val);
         else
-            redisLog(REDIS_WARNING, "(%016lx) -> %016lx", addr, val);
+            serverLog(REDIS_WARNING, "(%016lx) -> %016lx", addr, val);
     }
 }
 
 void logRegisters(ucontext_t *uc) {
-    redisLog(REDIS_WARNING, "--- REGISTERS");
+    serverLog(REDIS_WARNING, "--- REGISTERS");
 
 /* OSX */
 #if defined(__APPLE__) && defined(MAC_OS_X_VERSION_10_6)
   /* OSX AMD64 */
     #if defined(_STRUCT_X86_THREAD_STATE64) && !defined(__i386__)
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
     "\n"
     "RAX:%016lx RBX:%016lx\nRCX:%016lx RDX:%016lx\n"
     "RDI:%016lx RSI:%016lx\nRBP:%016lx RSP:%016lx\n"
@@ -647,7 +647,7 @@ void logRegisters(ucontext_t *uc) {
     logStackContent((void**)uc->uc_mcontext->__ss.__rsp);
     #else
     /* OSX x86 */
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
     "\n"
     "EAX:%08lx EBX:%08lx ECX:%08lx EDX:%08lx\n"
     "EDI:%08lx ESI:%08lx EBP:%08lx ESP:%08lx\n"
@@ -676,7 +676,7 @@ void logRegisters(ucontext_t *uc) {
 #elif defined(__linux__)
     /* Linux x86 */
     #if defined(__i386__)
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
     "\n"
     "EAX:%08lx EBX:%08lx ECX:%08lx EDX:%08lx\n"
     "EDI:%08lx ESI:%08lx EBP:%08lx ESP:%08lx\n"
@@ -702,7 +702,7 @@ void logRegisters(ucontext_t *uc) {
     logStackContent((void**)uc->uc_mcontext.gregs[7]);
     #elif defined(__X86_64__) || defined(__x86_64__)
     /* Linux AMD64 */
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
     "\n"
     "RAX:%016lx RBX:%016lx\nRCX:%016lx RDX:%016lx\n"
     "RDI:%016lx RSI:%016lx\nRBP:%016lx RSP:%016lx\n"
@@ -732,7 +732,7 @@ void logRegisters(ucontext_t *uc) {
     logStackContent((void**)uc->uc_mcontext.gregs[15]);
     #endif
 #else
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
         "  Dumping of registers not supported for this OS/arch");
 #endif
 }
@@ -774,15 +774,15 @@ void logCurrentClient(void) {
     sds client;
     int j;
 
-    redisLog(REDIS_WARNING, "--- CURRENT CLIENT INFO");
+    serverLog(REDIS_WARNING, "--- CURRENT CLIENT INFO");
     client = catClientInfoString(sdsempty(),cc);
-    redisLog(REDIS_WARNING,"client: %s", client);
+    serverLog(REDIS_WARNING,"client: %s", client);
     sdsfree(client);
     for (j = 0; j < cc->argc; j++) {
         robj *decoded;
 
         decoded = getDecodedObject(cc->argv[j]);
-        redisLog(REDIS_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
+        serverLog(REDIS_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
         decrRefCount(decoded);
     }
     /* Check if the first argument, usually a key, is found inside the
@@ -795,8 +795,8 @@ void logCurrentClient(void) {
         de = dictFind(cc->db->dict, key->ptr);
         if (de) {
             val = dictGetVal(de);
-            redisLog(REDIS_WARNING,"key '%s' found in DB containing the following object:", (char*)key->ptr);
-            redisLogObjectDebugInfo(val);
+            serverLog(REDIS_WARNING,"key '%s' found in DB containing the following object:", (char*)key->ptr);
+            serverLogObjectDebugInfo(val);
         }
         decrRefCount(key);
     }
@@ -892,25 +892,25 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     REDIS_NOTUSED(info);
 
     bugReportStart();
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
         "    Redis %s crashed by signal: %d", REDIS_VERSION, sig);
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
         "    Failed assertion: %s (%s:%d)", server.assert_failed,
                         server.assert_file, server.assert_line);
 
     /* Log the stack trace */
-    redisLog(REDIS_WARNING, "--- STACK TRACE");
+    serverLog(REDIS_WARNING, "--- STACK TRACE");
     logStackTrace(uc);
 
     /* Log INFO and CLIENT LIST */
-    redisLog(REDIS_WARNING, "--- INFO OUTPUT");
+    serverLog(REDIS_WARNING, "--- INFO OUTPUT");
     infostring = genRedisInfoString("all");
     infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
         dictGetHashFunctionSeed());
-    redisLogRaw(REDIS_WARNING, infostring);
-    redisLog(REDIS_WARNING, "--- CLIENT LIST OUTPUT");
+    serverLogRaw(REDIS_WARNING, infostring);
+    serverLog(REDIS_WARNING, "--- CLIENT LIST OUTPUT");
     clients = getAllClientsInfoString();
-    redisLogRaw(REDIS_WARNING, clients);
+    serverLogRaw(REDIS_WARNING, clients);
     sdsfree(infostring);
     sdsfree(clients);
 
@@ -922,18 +922,18 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
 
 #if defined(HAVE_PROC_MAPS)
     /* Test memory */
-    redisLog(REDIS_WARNING, "--- FAST MEMORY TEST");
+    serverLog(REDIS_WARNING, "--- FAST MEMORY TEST");
     bioKillThreads();
     if (memtest_test_linux_anonymous_maps()) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "!!! MEMORY ERROR DETECTED! Check your memory ASAP !!!");
     } else {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Fast memory test PASSED, however your memory can still be broken. Please run a memory test for several hours if possible.");
     }
 #endif
 
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
 "\n=== REDIS BUG REPORT END. Make sure to include from START to END. ===\n\n"
 "       Please report the crash by opening an issue on github:\n\n"
 "           http://github.com/antirez/redis/issues\n\n"
@@ -954,12 +954,12 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
 
 /* ==================== Logging functions for debugging ===================== */
 
-void redisLogHexDump(int level, char *descr, void *value, size_t len) {
+void serverLogHexDump(int level, char *descr, void *value, size_t len) {
     char buf[65], *b;
     unsigned char *v = value;
     char charset[] = "0123456789abcdef";
 
-    redisLog(level,"%s (hexdump):", descr);
+    serverLog(level,"%s (hexdump):", descr);
     b = buf;
     while(len) {
         b[0] = charset[(*v)>>4];
@@ -969,11 +969,11 @@ void redisLogHexDump(int level, char *descr, void *value, size_t len) {
         len--;
         v++;
         if (b-buf == 64 || len == 0) {
-            redisLogRaw(level|REDIS_LOG_RAW,buf);
+            serverLogRaw(level|REDIS_LOG_RAW,buf);
             b = buf;
         }
     }
-    redisLogRaw(level|REDIS_LOG_RAW,"\n");
+    serverLogRaw(level|REDIS_LOG_RAW,"\n");
 }
 
 /* =========================== Software Watchdog ============================ */
@@ -986,13 +986,13 @@ void watchdogSignalHandler(int sig, siginfo_t *info, void *secret) {
     REDIS_NOTUSED(info);
     REDIS_NOTUSED(sig);
 
-    redisLogFromHandler(REDIS_WARNING,"\n--- WATCHDOG TIMER EXPIRED ---");
+    serverLogFromHandler(REDIS_WARNING,"\n--- WATCHDOG TIMER EXPIRED ---");
 #ifdef HAVE_BACKTRACE
     logStackTrace(uc);
 #else
-    redisLogFromHandler(REDIS_WARNING,"Sorry: no support for backtrace().");
+    serverLogFromHandler(REDIS_WARNING,"Sorry: no support for backtrace().");
 #endif
-    redisLogFromHandler(REDIS_WARNING,"--------\n");
+    serverLogFromHandler(REDIS_WARNING,"--------\n");
 }
 
 /* Schedule a SIGALRM delivery after the specified period in milliseconds.