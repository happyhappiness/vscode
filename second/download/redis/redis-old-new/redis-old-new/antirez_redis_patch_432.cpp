@@ -153,7 +153,7 @@ void computeDatasetDigest(unsigned char *final) {
             if (o->type == OBJ_STRING) {
                 mixObjectDigest(digest,o);
             } else if (o->type == OBJ_LIST) {
-                listTypeIterator *li = listTypeInitIterator(o,0,REDIS_TAIL);
+                listTypeIterator *li = listTypeInitIterator(o,0,LIST_TAIL);
                 listTypeEntry entry;
                 while(listTypeNext(li,&entry)) {
                     robj *eleobj = listTypeGet(&entry);
@@ -219,7 +219,7 @@ void computeDatasetDigest(unsigned char *final) {
                     }
                     dictReleaseIterator(di);
                 } else {
-                    redisPanic("Unknown sorted set encoding");
+                    serverPanic("Unknown sorted set encoding");
                 }
             } else if (o->type == OBJ_HASH) {
                 hashTypeIterator *hi;
@@ -240,7 +240,7 @@ void computeDatasetDigest(unsigned char *final) {
                 }
                 hashTypeReleaseIterator(hi);
             } else {
-                redisPanic("Unknown object type");
+                serverPanic("Unknown object type");
             }
             /* If the key has an expire, add it to the mix */
             if (expiretime != -1) xorDigest(digest,"!!expire!!",10);
@@ -278,7 +278,7 @@ void debugCommand(client *c) {
             addReplyError(c,"Error trying to load the RDB dump");
             return;
         }
-        serverLog(REDIS_WARNING,"DB reloaded by DEBUG RELOAD");
+        serverLog(LL_WARNING,"DB reloaded by DEBUG RELOAD");
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
         emptyDb(NULL);
@@ -287,7 +287,7 @@ void debugCommand(client *c) {
             return;
         }
         server.dirty = 0; /* Prevent AOF / replication */
-        serverLog(REDIS_WARNING,"Append Only File loaded by DEBUG LOADAOF");
+        serverLog(LL_WARNING,"Append Only File loaded by DEBUG LOADAOF");
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"object") && c->argc == 3) {
         dictEntry *de;
@@ -472,13 +472,13 @@ void debugCommand(client *c) {
 
 void _serverAssert(char *estr, char *file, int line) {
     bugReportStart();
-    serverLog(REDIS_WARNING,"=== ASSERTION FAILED ===");
-    serverLog(REDIS_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
+    serverLog(LL_WARNING,"=== ASSERTION FAILED ===");
+    serverLog(LL_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
 #ifdef HAVE_BACKTRACE
     server.assert_failed = estr;
     server.assert_file = file;
     server.assert_line = line;
-    serverLog(REDIS_WARNING,"(forcing SIGSEGV to print the bug report.)");
+    serverLog(LL_WARNING,"(forcing SIGSEGV to print the bug report.)");
 #endif
     *((char*)-1) = 'x';
 }
@@ -487,10 +487,10 @@ void _serverAssertPrintClientInfo(client *c) {
     int j;
 
     bugReportStart();
-    serverLog(REDIS_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
-    serverLog(REDIS_WARNING,"client->flags = %d", c->flags);
-    serverLog(REDIS_WARNING,"client->fd = %d", c->fd);
-    serverLog(REDIS_WARNING,"client->argc = %d", c->argc);
+    serverLog(LL_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
+    serverLog(LL_WARNING,"client->flags = %d", c->flags);
+    serverLog(LL_WARNING,"client->fd = %d", c->fd);
+    serverLog(LL_WARNING,"client->argc = %d", c->argc);
     for (j=0; j < c->argc; j++) {
         char buf[128];
         char *arg;
@@ -502,38 +502,38 @@ void _serverAssertPrintClientInfo(client *c) {
                 c->argv[j]->type, c->argv[j]->encoding);
             arg = buf;
         }
-        serverLog(REDIS_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
+        serverLog(LL_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
             j, arg, c->argv[j]->refcount);
     }
 }
 
 void serverLogObjectDebugInfo(robj *o) {
-    serverLog(REDIS_WARNING,"Object type: %d", o->type);
-    serverLog(REDIS_WARNING,"Object encoding: %d", o->encoding);
-    serverLog(REDIS_WARNING,"Object refcount: %d", o->refcount);
+    serverLog(LL_WARNING,"Object type: %d", o->type);
+    serverLog(LL_WARNING,"Object encoding: %d", o->encoding);
+    serverLog(LL_WARNING,"Object refcount: %d", o->refcount);
     if (o->type == OBJ_STRING && sdsEncodedObject(o)) {
-        serverLog(REDIS_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
+        serverLog(LL_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
         if (sdslen(o->ptr) < 4096) {
             sds repr = sdscatrepr(sdsempty(),o->ptr,sdslen(o->ptr));
-            serverLog(REDIS_WARNING,"Object raw string content: %s", repr);
+            serverLog(LL_WARNING,"Object raw string content: %s", repr);
             sdsfree(repr);
         }
     } else if (o->type == OBJ_LIST) {
-        serverLog(REDIS_WARNING,"List length: %d", (int) listTypeLength(o));
+        serverLog(LL_WARNING,"List length: %d", (int) listTypeLength(o));
     } else if (o->type == OBJ_SET) {
-        serverLog(REDIS_WARNING,"Set size: %d", (int) setTypeSize(o));
+        serverLog(LL_WARNING,"Set size: %d", (int) setTypeSize(o));
     } else if (o->type == OBJ_HASH) {
-        serverLog(REDIS_WARNING,"Hash size: %d", (int) hashTypeLength(o));
+        serverLog(LL_WARNING,"Hash size: %d", (int) hashTypeLength(o));
     } else if (o->type == OBJ_ZSET) {
-        serverLog(REDIS_WARNING,"Sorted set size: %d", (int) zsetLength(o));
+        serverLog(LL_WARNING,"Sorted set size: %d", (int) zsetLength(o));
         if (o->encoding == OBJ_ENCODING_SKIPLIST)
-            serverLog(REDIS_WARNING,"Skiplist level: %d", (int) ((zset*)o->ptr)->zsl->level);
+            serverLog(LL_WARNING,"Skiplist level: %d", (int) ((zset*)o->ptr)->zsl->level);
     }
 }
 
 void _serverAssertPrintObject(robj *o) {
     bugReportStart();
-    serverLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
+    serverLog(LL_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
     serverLogObjectDebugInfo(o);
 }
 
@@ -543,21 +543,21 @@ void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line)
     _serverAssert(estr,file,line);
 }
 
-void _redisPanic(char *msg, char *file, int line) {
+void _serverPanic(char *msg, char *file, int line) {
     bugReportStart();
-    serverLog(REDIS_WARNING,"------------------------------------------------");
-    serverLog(REDIS_WARNING,"!!! Software Failure. Press left mouse button to continue");
-    serverLog(REDIS_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
+    serverLog(LL_WARNING,"------------------------------------------------");
+    serverLog(LL_WARNING,"!!! Software Failure. Press left mouse button to continue");
+    serverLog(LL_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
 #ifdef HAVE_BACKTRACE
-    serverLog(REDIS_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
+    serverLog(LL_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
 #endif
-    serverLog(REDIS_WARNING,"------------------------------------------------");
+    serverLog(LL_WARNING,"------------------------------------------------");
     *((char*)-1) = 'x';
 }
 
 void bugReportStart(void) {
     if (server.bug_report_start == 0) {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===");
         server.bug_report_start = 1;
     }
@@ -602,20 +602,20 @@ void logStackContent(void **sp) {
         unsigned long val = (unsigned long) sp[i];
 
         if (sizeof(long) == 4)
-            serverLog(REDIS_WARNING, "(%08lx) -> %08lx", addr, val);
+            serverLog(LL_WARNING, "(%08lx) -> %08lx", addr, val);
         else
-            serverLog(REDIS_WARNING, "(%016lx) -> %016lx", addr, val);
+            serverLog(LL_WARNING, "(%016lx) -> %016lx", addr, val);
     }
 }
 
 void logRegisters(ucontext_t *uc) {
-    serverLog(REDIS_WARNING, "--- REGISTERS");
+    serverLog(LL_WARNING, "--- REGISTERS");
 
 /* OSX */
 #if defined(__APPLE__) && defined(MAC_OS_X_VERSION_10_6)
   /* OSX AMD64 */
     #if defined(_STRUCT_X86_THREAD_STATE64) && !defined(__i386__)
-    serverLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
     "\n"
     "RAX:%016lx RBX:%016lx\nRCX:%016lx RDX:%016lx\n"
     "RDI:%016lx RSI:%016lx\nRBP:%016lx RSP:%016lx\n"
@@ -647,7 +647,7 @@ void logRegisters(ucontext_t *uc) {
     logStackContent((void**)uc->uc_mcontext->__ss.__rsp);
     #else
     /* OSX x86 */
-    serverLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
     "\n"
     "EAX:%08lx EBX:%08lx ECX:%08lx EDX:%08lx\n"
     "EDI:%08lx ESI:%08lx EBP:%08lx ESP:%08lx\n"
@@ -676,7 +676,7 @@ void logRegisters(ucontext_t *uc) {
 #elif defined(__linux__)
     /* Linux x86 */
     #if defined(__i386__)
-    serverLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
     "\n"
     "EAX:%08lx EBX:%08lx ECX:%08lx EDX:%08lx\n"
     "EDI:%08lx ESI:%08lx EBP:%08lx ESP:%08lx\n"
@@ -702,7 +702,7 @@ void logRegisters(ucontext_t *uc) {
     logStackContent((void**)uc->uc_mcontext.gregs[7]);
     #elif defined(__X86_64__) || defined(__x86_64__)
     /* Linux AMD64 */
-    serverLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
     "\n"
     "RAX:%016lx RBX:%016lx\nRCX:%016lx RDX:%016lx\n"
     "RDI:%016lx RSI:%016lx\nRBP:%016lx RSP:%016lx\n"
@@ -732,7 +732,7 @@ void logRegisters(ucontext_t *uc) {
     logStackContent((void**)uc->uc_mcontext.gregs[15]);
     #endif
 #else
-    serverLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
         "  Dumping of registers not supported for this OS/arch");
 #endif
 }
@@ -774,15 +774,15 @@ void logCurrentClient(void) {
     sds client;
     int j;
 
-    serverLog(REDIS_WARNING, "--- CURRENT CLIENT INFO");
+    serverLog(LL_WARNING, "--- CURRENT CLIENT INFO");
     client = catClientInfoString(sdsempty(),cc);
-    serverLog(REDIS_WARNING,"client: %s", client);
+    serverLog(LL_WARNING,"client: %s", client);
     sdsfree(client);
     for (j = 0; j < cc->argc; j++) {
         robj *decoded;
 
         decoded = getDecodedObject(cc->argv[j]);
-        serverLog(REDIS_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
+        serverLog(LL_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
         decrRefCount(decoded);
     }
     /* Check if the first argument, usually a key, is found inside the
@@ -795,7 +795,7 @@ void logCurrentClient(void) {
         de = dictFind(cc->db->dict, key->ptr);
         if (de) {
             val = dictGetVal(de);
-            serverLog(REDIS_WARNING,"key '%s' found in DB containing the following object:", (char*)key->ptr);
+            serverLog(LL_WARNING,"key '%s' found in DB containing the following object:", (char*)key->ptr);
             serverLogObjectDebugInfo(val);
         }
         decrRefCount(key);
@@ -889,28 +889,28 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     ucontext_t *uc = (ucontext_t*) secret;
     sds infostring, clients;
     struct sigaction act;
-    REDIS_NOTUSED(info);
+    UNUSED(info);
 
     bugReportStart();
-    serverLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
         "    Redis %s crashed by signal: %d", REDIS_VERSION, sig);
-    serverLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
         "    Failed assertion: %s (%s:%d)", server.assert_failed,
                         server.assert_file, server.assert_line);
 
     /* Log the stack trace */
-    serverLog(REDIS_WARNING, "--- STACK TRACE");
+    serverLog(LL_WARNING, "--- STACK TRACE");
     logStackTrace(uc);
 
     /* Log INFO and CLIENT LIST */
-    serverLog(REDIS_WARNING, "--- INFO OUTPUT");
+    serverLog(LL_WARNING, "--- INFO OUTPUT");
     infostring = genRedisInfoString("all");
     infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
         dictGetHashFunctionSeed());
-    serverLogRaw(REDIS_WARNING, infostring);
-    serverLog(REDIS_WARNING, "--- CLIENT LIST OUTPUT");
+    serverLogRaw(LL_WARNING, infostring);
+    serverLog(LL_WARNING, "--- CLIENT LIST OUTPUT");
     clients = getAllClientsInfoString();
-    serverLogRaw(REDIS_WARNING, clients);
+    serverLogRaw(LL_WARNING, clients);
     sdsfree(infostring);
     sdsfree(clients);
 
@@ -922,18 +922,18 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
 
 #if defined(HAVE_PROC_MAPS)
     /* Test memory */
-    serverLog(REDIS_WARNING, "--- FAST MEMORY TEST");
+    serverLog(LL_WARNING, "--- FAST MEMORY TEST");
     bioKillThreads();
     if (memtest_test_linux_anonymous_maps()) {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "!!! MEMORY ERROR DETECTED! Check your memory ASAP !!!");
     } else {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Fast memory test PASSED, however your memory can still be broken. Please run a memory test for several hours if possible.");
     }
 #endif
 
-    serverLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
 "\n=== REDIS BUG REPORT END. Make sure to include from START to END. ===\n\n"
 "       Please report the crash by opening an issue on github:\n\n"
 "           http://github.com/antirez/redis/issues\n\n"
@@ -969,11 +969,11 @@ void serverLogHexDump(int level, char *descr, void *value, size_t len) {
         len--;
         v++;
         if (b-buf == 64 || len == 0) {
-            serverLogRaw(level|REDIS_LOG_RAW,buf);
+            serverLogRaw(level|LL_RAW,buf);
             b = buf;
         }
     }
-    serverLogRaw(level|REDIS_LOG_RAW,"\n");
+    serverLogRaw(level|LL_RAW,"\n");
 }
 
 /* =========================== Software Watchdog ============================ */
@@ -983,16 +983,16 @@ void watchdogSignalHandler(int sig, siginfo_t *info, void *secret) {
 #ifdef HAVE_BACKTRACE
     ucontext_t *uc = (ucontext_t*) secret;
 #endif
-    REDIS_NOTUSED(info);
-    REDIS_NOTUSED(sig);
+    UNUSED(info);
+    UNUSED(sig);
 
-    serverLogFromHandler(REDIS_WARNING,"\n--- WATCHDOG TIMER EXPIRED ---");
+    serverLogFromHandler(LL_WARNING,"\n--- WATCHDOG TIMER EXPIRED ---");
 #ifdef HAVE_BACKTRACE
     logStackTrace(uc);
 #else
-    serverLogFromHandler(REDIS_WARNING,"Sorry: no support for backtrace().");
+    serverLogFromHandler(LL_WARNING,"Sorry: no support for backtrace().");
 #endif
-    serverLogFromHandler(REDIS_WARNING,"--------\n");
+    serverLogFromHandler(LL_WARNING,"--------\n");
 }
 
 /* Schedule a SIGALRM delivery after the specified period in milliseconds.