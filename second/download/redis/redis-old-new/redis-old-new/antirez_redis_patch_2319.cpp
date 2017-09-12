@@ -279,7 +279,7 @@ struct redisCommand {
 
 struct redisFunctionSym {
     char *name;
-    long pointer;
+    unsigned long pointer;
 };
 
 typedef struct _redisSortObject {
@@ -330,6 +330,8 @@ static int setExpire(redisDb *db, robj *key, time_t when);
 static void updateSalvesWaitingBgsave(int bgsaveerr);
 static void freeMemoryIfNeeded(void);
 static int processCommand(redisClient *c);
+static void segvHandler(int sig, siginfo_t *info, void *secret);
+static void setupSigSegvAction(void);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -388,7 +390,6 @@ static void getSetCommand(redisClient *c);
 static void ttlCommand(redisClient *c);
 static void slaveofCommand(redisClient *c);
 static void debugCommand(redisClient *c);
-static void setupSigSegvAction();
 /*================================= Globals ================================= */
 
 /* Global vars */
@@ -454,91 +455,6 @@ static struct redisCommand cmdTable[] = {
     {"debug",debugCommand,-2,REDIS_CMD_INLINE},
     {NULL,NULL,0,0}
 };
-static struct redisFunctionSym symsTable[] = {
-{"freeStringObject", (long)freeStringObject},
-{"freeListObject", (long)freeListObject},
-{"freeSetObject", (long)freeSetObject},
-{"decrRefCount", (long)decrRefCount},
-{"createObject", (long)createObject},
-{"freeClient", (long)freeClient},
-{"rdbLoad", (long)rdbLoad},
-{"addReply", (long)addReply},
-{"addReplySds", (long)addReplySds},
-{"incrRefCount", (long)incrRefCount},
-{"rdbSaveBackground", (long)rdbSaveBackground},
-{"createStringObject", (long)createStringObject},
-{"replicationFeedSlaves", (long)replicationFeedSlaves},
-{"syncWithMaster", (long)syncWithMaster},
-{"tryObjectSharing", (long)tryObjectSharing},
-{"removeExpire", (long)removeExpire},
-{"expireIfNeeded", (long)expireIfNeeded},
-{"deleteIfVolatile", (long)deleteIfVolatile},
-{"deleteKey", (long)deleteKey},
-{"getExpire", (long)getExpire},
-{"setExpire", (long)setExpire},
-{"updateSalvesWaitingBgsave", (long)updateSalvesWaitingBgsave},
-{"freeMemoryIfNeeded", (long)freeMemoryIfNeeded},
-{"authCommand", (long)authCommand},
-{"pingCommand", (long)pingCommand},
-{"echoCommand", (long)echoCommand},
-{"setCommand", (long)setCommand},
-{"setnxCommand", (long)setnxCommand},
-{"getCommand", (long)getCommand},
-{"delCommand", (long)delCommand},
-{"existsCommand", (long)existsCommand},
-{"incrCommand", (long)incrCommand},
-{"decrCommand", (long)decrCommand},
-{"incrbyCommand", (long)incrbyCommand},
-{"decrbyCommand", (long)decrbyCommand},
-{"selectCommand", (long)selectCommand},
-{"randomkeyCommand", (long)randomkeyCommand},
-{"keysCommand", (long)keysCommand},
-{"dbsizeCommand", (long)dbsizeCommand},
-{"lastsaveCommand", (long)lastsaveCommand},
-{"saveCommand", (long)saveCommand},
-{"bgsaveCommand", (long)bgsaveCommand},
-{"shutdownCommand", (long)shutdownCommand},
-{"moveCommand", (long)moveCommand},
-{"renameCommand", (long)renameCommand},
-{"renamenxCommand", (long)renamenxCommand},
-{"lpushCommand", (long)lpushCommand},
-{"rpushCommand", (long)rpushCommand},
-{"lpopCommand", (long)lpopCommand},
-{"rpopCommand", (long)rpopCommand},
-{"llenCommand", (long)llenCommand},
-{"lindexCommand", (long)lindexCommand},
-{"lrangeCommand", (long)lrangeCommand},
-{"ltrimCommand", (long)ltrimCommand},
-{"typeCommand", (long)typeCommand},
-{"lsetCommand", (long)lsetCommand},
-{"saddCommand", (long)saddCommand},
-{"sremCommand", (long)sremCommand},
-{"smoveCommand", (long)smoveCommand},
-{"sismemberCommand", (long)sismemberCommand},
-{"scardCommand", (long)scardCommand},
-{"sinterCommand", (long)sinterCommand},
-{"sinterstoreCommand", (long)sinterstoreCommand},
-{"sunionCommand", (long)sunionCommand},
-{"sunionstoreCommand", (long)sunionstoreCommand},
-{"sdiffCommand", (long)sdiffCommand},
-{"sdiffstoreCommand", (long)sdiffstoreCommand},
-{"syncCommand", (long)syncCommand},
-{"flushdbCommand", (long)flushdbCommand},
-{"flushallCommand", (long)flushallCommand},
-{"sortCommand", (long)sortCommand},
-{"lremCommand", (long)lremCommand},
-{"infoCommand", (long)infoCommand},
-{"mgetCommand", (long)mgetCommand},
-{"monitorCommand", (long)monitorCommand},
-{"expireCommand", (long)expireCommand},
-{"getSetCommand", (long)getSetCommand},
-{"ttlCommand", (long)ttlCommand},
-{"slaveofCommand", (long)slaveofCommand},
-{"debugCommand", (long)debugCommand},
-{"processCommand", (long)processCommand},
-{"setupSigSegvAction", (long)setupSigSegvAction},
-{NULL,0}
-};
 /*============================ Utility functions ============================ */
 
 /* Glob-style pattern matching. */
@@ -664,8 +580,7 @@ int stringmatchlen(const char *pattern, int patternLen,
     return 0;
 }
 
-void redisLog(int level, const char *fmt, ...)
-{
+static void redisLog(int level, const char *fmt, ...) {
     va_list ap;
     FILE *fp;
 
@@ -760,7 +675,7 @@ static void oom(const char *msg) {
 }
 
 /* ====================== Redis server networking stuff ===================== */
-void closeTimedoutClients(void) {
+static void closeTimedoutClients(void) {
     redisClient *c;
     listNode *ln;
     time_t now = time(NULL);
@@ -779,7 +694,7 @@ void closeTimedoutClients(void) {
 
 /* If the percentage of used slots in the HT reaches REDIS_HT_MINFILL
  * we resize the hash table to save memory */
-void tryResizeHashTables(void) {
+static void tryResizeHashTables(void) {
     int j;
 
     for (j = 0; j < server.dbnum; j++) {
@@ -796,7 +711,7 @@ void tryResizeHashTables(void) {
     }
 }
 
-int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
+static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     int j, loops = server.cronloops++;
     REDIS_NOTUSED(eventLoop);
     REDIS_NOTUSED(id);
@@ -1869,7 +1784,7 @@ static int rdbSaveLen(FILE *fp, uint32_t len) {
 /* String objects in the form "2391" "-100" without any space and with a
  * range of values that can fit in an 8, 16 or 32 bit signed value can be
  * encoded as integers to save space */
-int rdbTryIntegerEncoding(sds s, unsigned char *enc) {
+static int rdbTryIntegerEncoding(sds s, unsigned char *enc) {
     long long value;
     char *endptr, buf[32];
 
@@ -3361,7 +3276,7 @@ static void flushallCommand(redisClient *c) {
     server.dirty++;
 }
 
-redisSortOperation *createSortOperation(int type, robj *pattern) {
+static redisSortOperation *createSortOperation(int type, robj *pattern) {
     redisSortOperation *so = zmalloc(sizeof(*so));
     if (!so) oom("createSortOperation");
     so->type = type;
@@ -3371,7 +3286,7 @@ redisSortOperation *createSortOperation(int type, robj *pattern) {
 
 /* Return the value associated to the key with a name obtained
  * substituting the first occurence of '*' in 'pattern' with 'subst' */
-robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
+static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
     char *p;
     sds spat, ssub;
     robj keyobj;
@@ -4192,37 +4107,145 @@ static void debugCommand(redisClient *c) {
             "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>]\r\n"));
     }
 }
-char *findFuncName(void *pointer, long *offset){
-	int i, ret=-1;
-	long val, off;
-	for(i=0; symsTable[i].pointer!=0; i++){
-		val=(long)pointer-symsTable[i].pointer;
-		if(val>=0 && (off<0 || val <= off)){
-			off=val;
-			ret=i;
-		}
-	}
-	if(ret<0)
-		*offset=0;
-	else
-		*offset=off;
-	return ret>=0?symsTable[ret].name:"unknown";
-}
-
-static void segvHandler (int sig, siginfo_t *info, void *secret) {
-
-  void *trace[100];
-  char **messages = (char **)NULL;
-  char *tmp;
-  int i, trace_size = 0;
-  long offset=0;
-  ucontext_t *uc = (ucontext_t *)secret;
-  time_t uptime = time(NULL)-server.stat_starttime;
-
-  redisLog(REDIS_WARNING, "application: redis,  signal: segmentation fault -%d-",REDIS_VERSION, sig);
-  redisLog(REDIS_WARNING, "%s", sdscatprintf(sdsempty(),
+
+static struct redisFunctionSym symsTable[] = {
+{"freeStringObject", (unsigned long)freeStringObject},
+{"freeListObject", (unsigned long)freeListObject},
+{"freeSetObject", (unsigned long)freeSetObject},
+{"decrRefCount", (unsigned long)decrRefCount},
+{"createObject", (unsigned long)createObject},
+{"freeClient", (unsigned long)freeClient},
+{"rdbLoad", (unsigned long)rdbLoad},
+{"addReply", (unsigned long)addReply},
+{"addReplySds", (unsigned long)addReplySds},
+{"incrRefCount", (unsigned long)incrRefCount},
+{"rdbSaveBackground", (unsigned long)rdbSaveBackground},
+{"createStringObject", (unsigned long)createStringObject},
+{"replicationFeedSlaves", (unsigned long)replicationFeedSlaves},
+{"syncWithMaster", (unsigned long)syncWithMaster},
+{"tryObjectSharing", (unsigned long)tryObjectSharing},
+{"removeExpire", (unsigned long)removeExpire},
+{"expireIfNeeded", (unsigned long)expireIfNeeded},
+{"deleteIfVolatile", (unsigned long)deleteIfVolatile},
+{"deleteKey", (unsigned long)deleteKey},
+{"getExpire", (unsigned long)getExpire},
+{"setExpire", (unsigned long)setExpire},
+{"updateSalvesWaitingBgsave", (unsigned long)updateSalvesWaitingBgsave},
+{"freeMemoryIfNeeded", (unsigned long)freeMemoryIfNeeded},
+{"authCommand", (unsigned long)authCommand},
+{"pingCommand", (unsigned long)pingCommand},
+{"echoCommand", (unsigned long)echoCommand},
+{"setCommand", (unsigned long)setCommand},
+{"setnxCommand", (unsigned long)setnxCommand},
+{"getCommand", (unsigned long)getCommand},
+{"delCommand", (unsigned long)delCommand},
+{"existsCommand", (unsigned long)existsCommand},
+{"incrCommand", (unsigned long)incrCommand},
+{"decrCommand", (unsigned long)decrCommand},
+{"incrbyCommand", (unsigned long)incrbyCommand},
+{"decrbyCommand", (unsigned long)decrbyCommand},
+{"selectCommand", (unsigned long)selectCommand},
+{"randomkeyCommand", (unsigned long)randomkeyCommand},
+{"keysCommand", (unsigned long)keysCommand},
+{"dbsizeCommand", (unsigned long)dbsizeCommand},
+{"lastsaveCommand", (unsigned long)lastsaveCommand},
+{"saveCommand", (unsigned long)saveCommand},
+{"bgsaveCommand", (unsigned long)bgsaveCommand},
+{"shutdownCommand", (unsigned long)shutdownCommand},
+{"moveCommand", (unsigned long)moveCommand},
+{"renameCommand", (unsigned long)renameCommand},
+{"renamenxCommand", (unsigned long)renamenxCommand},
+{"lpushCommand", (unsigned long)lpushCommand},
+{"rpushCommand", (unsigned long)rpushCommand},
+{"lpopCommand", (unsigned long)lpopCommand},
+{"rpopCommand", (unsigned long)rpopCommand},
+{"llenCommand", (unsigned long)llenCommand},
+{"lindexCommand", (unsigned long)lindexCommand},
+{"lrangeCommand", (unsigned long)lrangeCommand},
+{"ltrimCommand", (unsigned long)ltrimCommand},
+{"typeCommand", (unsigned long)typeCommand},
+{"lsetCommand", (unsigned long)lsetCommand},
+{"saddCommand", (unsigned long)saddCommand},
+{"sremCommand", (unsigned long)sremCommand},
+{"smoveCommand", (unsigned long)smoveCommand},
+{"sismemberCommand", (unsigned long)sismemberCommand},
+{"scardCommand", (unsigned long)scardCommand},
+{"sinterCommand", (unsigned long)sinterCommand},
+{"sinterstoreCommand", (unsigned long)sinterstoreCommand},
+{"sunionCommand", (unsigned long)sunionCommand},
+{"sunionstoreCommand", (unsigned long)sunionstoreCommand},
+{"sdiffCommand", (unsigned long)sdiffCommand},
+{"sdiffstoreCommand", (unsigned long)sdiffstoreCommand},
+{"syncCommand", (unsigned long)syncCommand},
+{"flushdbCommand", (unsigned long)flushdbCommand},
+{"flushallCommand", (unsigned long)flushallCommand},
+{"sortCommand", (unsigned long)sortCommand},
+{"lremCommand", (unsigned long)lremCommand},
+{"infoCommand", (unsigned long)infoCommand},
+{"mgetCommand", (unsigned long)mgetCommand},
+{"monitorCommand", (unsigned long)monitorCommand},
+{"expireCommand", (unsigned long)expireCommand},
+{"getSetCommand", (unsigned long)getSetCommand},
+{"ttlCommand", (unsigned long)ttlCommand},
+{"slaveofCommand", (unsigned long)slaveofCommand},
+{"debugCommand", (unsigned long)debugCommand},
+{"processCommand", (unsigned long)processCommand},
+{"setupSigSegvAction", (unsigned long)setupSigSegvAction},
+{"segvHandler", (unsigned long)segvHandler},
+{"readQueryFromClient", (unsigned long)readQueryFromClient},
+{NULL,0}
+};
+
+/* This function try to convert a pointer into a function name. It's used in
+ * oreder to provide a backtrace under segmentation fault that's able to
+ * display functions declared as static (otherwise the backtrace is useless). */
+static char *findFuncName(void *pointer, unsigned long *offset){
+    int i, ret = -1;
+    unsigned long off, minoff = 0;
+
+    /* Try to match against the Symbol with the smallest offset */
+    for (i=0; symsTable[i].pointer; i++) {
+        unsigned long lp = (unsigned long) pointer;
+
+        if (lp != (unsigned long)-1 && lp >= symsTable[i].pointer) {
+            off=lp-symsTable[i].pointer;
+            if (ret < 0 || off < minoff) {
+                minoff=off;
+                ret=i;
+            }
+        }
+    }
+    if (ret == -1) return NULL;
+    *offset = minoff;
+    return symsTable[ret].name;
+}
+
+static void *getMcontextEip(ucontext_t *uc) {
+#if defined(__FreeBSD__)
+    return (void*) uc->uc_mcontext.mc_eip;
+#elif defined(__dietlibc__)
+    return (void*) uc->uc_mcontext.eip;
+#elif defined(__APPLE__)
+    return (void*) uc->uc_mcontext->__ss.__eip;
+#else /* Linux */
+    return (void*) uc->uc_mcontext.gregs[REG_EIP];
+#endif
+}
+
+static void segvHandler(int sig, siginfo_t *info, void *secret) {
+    void *trace[100];
+    char **messages = NULL;
+    int i, trace_size = 0;
+    unsigned long offset=0;
+    time_t uptime = time(NULL)-server.stat_starttime;
+    ucontext_t *uc = (ucontext_t*) secret;
+    REDIS_NOTUSED(info);
+
+    redisLog(REDIS_WARNING,
+        "======= Ooops! Redis %s got signal: -%d- =======", REDIS_VERSION, sig);
+    redisLog(REDIS_WARNING, "%s", sdscatprintf(sdsempty(),
         "redis_version:%s; "
-        "uptime_in_days:%d; "
+        "uptime_in_seconds:%d; "
         "connected_clients:%d; "
         "connected_slaves:%d; "
         "used_memory:%zu; "
@@ -4244,42 +4267,38 @@ static void segvHandler (int sig, siginfo_t *info, void *secret) {
         server.stat_numcommands,
         server.masterhost == NULL ? "master" : "slave"
     ));
-
-  redisLog(REDIS_WARNING,"EIP %p",  (void *)uc->uc_mcontext.gregs[REG_EIP]);
-  redisLog(REDIS_WARNING,"EAX %p, EBX %p,  ECX %p, EDX %p", (void *)uc->uc_mcontext.gregs[REG_EAX], (void *)uc->uc_mcontext.gregs[REG_EBX],  (void *)uc->uc_mcontext.gregs[REG_ECX], (void *)uc->uc_mcontext.gregs[REG_EDX]);
- 
-	
-  trace_size = backtrace(trace, 100);
-  char pointer[trace_size][11];
+    
+    trace_size = backtrace(trace, 100);
     /* overwrite sigaction with caller's address */
-  trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];
- for (i=1; i<trace_size; ++i)
-  	snprintf(pointer[i],11,"[%p]", trace[i]);
+    trace[1] = getMcontextEip(uc);
+    messages = backtrace_symbols(trace, trace_size);
 
-  messages = backtrace_symbols(trace, trace_size);
-  
-  for (i=1; i<trace_size; ++i){
-	tmp=strstr(messages[i],pointer[i]);
-	if((tmp-2)[0]!=')'){
-		char *a=findFuncName(trace[i], &offset);
-		redisLog(REDIS_WARNING,"#%d (%s+0x%x) %s", i, a, (unsigned int)offset, tmp);
-		}
-	else
-		redisLog(REDIS_WARNING,"#%d %s", i, messages[i]);
-	}
-
-  free(messages);
-  exit(0);
-}
-
-void setupSigSegvAction(){
-  struct sigaction act;
-  sigemptyset (&act.sa_mask);
-  /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction  is used. Otherwise, sa_handler is used */
-  act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
-  act.sa_sigaction = segvHandler;
-  sigaction (SIGSEGV, &act, NULL);
+    for (i=0; i<trace_size; ++i) {
+        char *fn = findFuncName(trace[i], &offset), *p;
+
+        p = strchr(messages[i],'+');
+        if (!fn || (p && ((unsigned long)strtol(p+1,NULL,10)) < offset)) {
+            redisLog(REDIS_WARNING,"%s", messages[i]);
+        } else {
+            redisLog(REDIS_WARNING,"%d redis-server %p %s + %d", i, trace[i], fn, (unsigned int)offset);
+        }
+    }
+    free(messages);
+    exit(0);
 }
+
+static void setupSigSegvAction(void) {
+    struct sigaction act;
+
+    sigemptyset (&act.sa_mask);
+    /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction
+     * is used. Otherwise, sa_handler is used */
+    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
+    act.sa_sigaction = segvHandler;
+    sigaction (SIGSEGV, &act, NULL);
+    sigaction (SIGBUS, &act, NULL);
+}
+
 /* =================================== Main! ================================ */
 
 #ifdef __linux__