@@ -273,6 +273,11 @@ struct redisCommand {
     int flags;
 };
 
+struct redisFunctionSym {
+    char *name;
+    long pointer;
+};
+
 typedef struct _redisSortObject {
     robj *obj;
     union {
@@ -320,6 +325,7 @@ static time_t getExpire(redisDb *db, robj *key);
 static int setExpire(redisDb *db, robj *key, time_t when);
 static void updateSalvesWaitingBgsave(int bgsaveerr);
 static void freeMemoryIfNeeded(void);
+static int processCommand(redisClient *c);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -444,7 +450,91 @@ static struct redisCommand cmdTable[] = {
     {"debug",debugCommand,-2,REDIS_CMD_INLINE},
     {NULL,NULL,0,0}
 };
-
+static struct redisFunctionSym symsTable[] = {
+{"freeStringObject", (long)freeStringObject},
+{"freeListObject", (long)freeListObject},
+{"freeSetObject", (long)freeSetObject},
+{"decrRefCount", (long)decrRefCount},
+{"createObject", (long)createObject},
+{"freeClient", (long)freeClient},
+{"rdbLoad", (long)rdbLoad},
+{"addReply", (long)addReply},
+{"addReplySds", (long)addReplySds},
+{"incrRefCount", (long)incrRefCount},
+{"rdbSaveBackground", (long)rdbSaveBackground},
+{"createStringObject", (long)createStringObject},
+{"replicationFeedSlaves", (long)replicationFeedSlaves},
+{"syncWithMaster", (long)syncWithMaster},
+{"tryObjectSharing", (long)tryObjectSharing},
+{"removeExpire", (long)removeExpire},
+{"expireIfNeeded", (long)expireIfNeeded},
+{"deleteIfVolatile", (long)deleteIfVolatile},
+{"deleteKey", (long)deleteKey},
+{"getExpire", (long)getExpire},
+{"setExpire", (long)setExpire},
+{"updateSalvesWaitingBgsave", (long)updateSalvesWaitingBgsave},
+{"freeMemoryIfNeeded", (long)freeMemoryIfNeeded},
+{"authCommand", (long)authCommand},
+{"pingCommand", (long)pingCommand},
+{"echoCommand", (long)echoCommand},
+{"setCommand", (long)setCommand},
+{"setnxCommand", (long)setnxCommand},
+{"getCommand", (long)getCommand},
+{"delCommand", (long)delCommand},
+{"existsCommand", (long)existsCommand},
+{"incrCommand", (long)incrCommand},
+{"decrCommand", (long)decrCommand},
+{"incrbyCommand", (long)incrbyCommand},
+{"decrbyCommand", (long)decrbyCommand},
+{"selectCommand", (long)selectCommand},
+{"randomkeyCommand", (long)randomkeyCommand},
+{"keysCommand", (long)keysCommand},
+{"dbsizeCommand", (long)dbsizeCommand},
+{"lastsaveCommand", (long)lastsaveCommand},
+{"saveCommand", (long)saveCommand},
+{"bgsaveCommand", (long)bgsaveCommand},
+{"shutdownCommand", (long)shutdownCommand},
+{"moveCommand", (long)moveCommand},
+{"renameCommand", (long)renameCommand},
+{"renamenxCommand", (long)renamenxCommand},
+{"lpushCommand", (long)lpushCommand},
+{"rpushCommand", (long)rpushCommand},
+{"lpopCommand", (long)lpopCommand},
+{"rpopCommand", (long)rpopCommand},
+{"llenCommand", (long)llenCommand},
+{"lindexCommand", (long)lindexCommand},
+{"lrangeCommand", (long)lrangeCommand},
+{"ltrimCommand", (long)ltrimCommand},
+{"typeCommand", (long)typeCommand},
+{"lsetCommand", (long)lsetCommand},
+{"saddCommand", (long)saddCommand},
+{"sremCommand", (long)sremCommand},
+{"smoveCommand", (long)smoveCommand},
+{"sismemberCommand", (long)sismemberCommand},
+{"scardCommand", (long)scardCommand},
+{"sinterCommand", (long)sinterCommand},
+{"sinterstoreCommand", (long)sinterstoreCommand},
+{"sunionCommand", (long)sunionCommand},
+{"sunionstoreCommand", (long)sunionstoreCommand},
+{"sdiffCommand", (long)sdiffCommand},
+{"sdiffstoreCommand", (long)sdiffstoreCommand},
+{"syncCommand", (long)syncCommand},
+{"flushdbCommand", (long)flushdbCommand},
+{"flushallCommand", (long)flushallCommand},
+{"sortCommand", (long)sortCommand},
+{"lremCommand", (long)lremCommand},
+{"infoCommand", (long)infoCommand},
+{"mgetCommand", (long)mgetCommand},
+{"monitorCommand", (long)monitorCommand},
+{"expireCommand", (long)expireCommand},
+{"getSetCommand", (long)getSetCommand},
+{"ttlCommand", (long)ttlCommand},
+{"slaveofCommand", (long)slaveofCommand},
+{"debugCommand", (long)debugCommand},
+{"processCommand", (long)processCommand},
+{"setupSigSegvAction", (long)setupSigSegvAction},
+{NULL,0}
+};
 /*============================ Utility functions ============================ */
 
 /* Glob-style pattern matching. */
@@ -4080,12 +4170,30 @@ static void debugCommand(redisClient *c) {
             "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>]\r\n"));
     }
 }
+char *findFuncName(void *pointer, long *offset){
+	int i, ret=-1;
+	long val, off;
+	for(i=0; symsTable[i].pointer!=0; i++){
+		val=(long)pointer-symsTable[i].pointer;
+		if(val>=0 && (off<0 || val <= off)){
+			off=val;
+			ret=i;
+		}
+	}
+	if(ret<0)
+		*offset=0;
+	else
+		*offset=off;
+	return ret>=0?symsTable[ret].name:"unknown";
+}
 
 static void segvHandler (int sig, siginfo_t *info, void *secret) {
 
   void *trace[100];
   char **messages = (char **)NULL;
+  char *tmp;
   int i, trace_size = 0;
+  long offset=0;
   ucontext_t *uc = (ucontext_t *)secret;
   
   redisLog(REDIS_DEBUG, "Segmentation fault -%d- Redis %s", sig, REDIS_VERSION );
@@ -4094,13 +4202,23 @@ static void segvHandler (int sig, siginfo_t *info, void *secret) {
  
 	
   trace_size = backtrace(trace, 100);
-  /* overwrite sigaction with caller's address */
+  char pointer[trace_size][11];
+    /* overwrite sigaction with caller's address */
   trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];
+ for (i=1; i<trace_size; ++i)
+  	snprintf(pointer[i],11,"[%p]", trace[i]);
 
   messages = backtrace_symbols(trace, trace_size);
   
-  for (i=1; i<trace_size; ++i)
-	redisLog(REDIS_DEBUG,"[bt] %s", messages[i]);
+  for (i=1; i<trace_size; ++i){
+	tmp=strstr(messages[i],pointer[i]);
+	if((tmp-2)[0]!=')'){
+		char *a=findFuncName(trace[i], &offset);
+		redisLog(REDIS_DEBUG,"[bt] (%s+%x) %s", a, (unsigned int)offset, tmp);
+		}
+	else
+		redisLog(REDIS_DEBUG,"[bt] %s", messages[i]);
+	}
 
   free(messages);
   exit(0);