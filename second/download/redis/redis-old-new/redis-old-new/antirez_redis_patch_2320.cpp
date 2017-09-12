@@ -36,7 +36,10 @@
 #include <string.h>
 #include <time.h>
 #include <unistd.h>
+#define __USE_POSIX199309
 #include <signal.h>
+#include <execinfo.h>
+#include <ucontext.h>
 #include <sys/wait.h>
 #include <errno.h>
 #include <assert.h>
@@ -51,6 +54,7 @@
 #include <limits.h>
 #include <execinfo.h>
 
+#include "redis.h"
 #include "ae.h"     /* Event driven programming library */
 #include "sds.h"    /* Dynamic safe strings */
 #include "anet.h"   /* Networking the easy way */
@@ -171,6 +175,7 @@
 /* Anti-warning macro... */
 #define REDIS_NOTUSED(V) ((void) V)
 
+
 /*================================= Data types ============================== */
 
 /* A redis object, that is a type able to hold a string / list / set */
@@ -272,6 +277,11 @@ struct redisCommand {
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
@@ -319,6 +329,7 @@ static time_t getExpire(redisDb *db, robj *key);
 static int setExpire(redisDb *db, robj *key, time_t when);
 static void updateSalvesWaitingBgsave(int bgsaveerr);
 static void freeMemoryIfNeeded(void);
+static int processCommand(redisClient *c);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -377,7 +388,7 @@ static void getSetCommand(redisClient *c);
 static void ttlCommand(redisClient *c);
 static void slaveofCommand(redisClient *c);
 static void debugCommand(redisClient *c);
-
+static void setupSigSegvAction();
 /*================================= Globals ================================= */
 
 /* Global vars */
@@ -443,7 +454,91 @@ static struct redisCommand cmdTable[] = {
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
@@ -902,6 +997,7 @@ static void initServer() {
 
     signal(SIGHUP, SIG_IGN);
     signal(SIGPIPE, SIG_IGN);
+    setupSigSegvAction();
 
     server.clients = listCreate();
     server.slaves = listCreate();
@@ -4096,7 +4192,94 @@ static void debugCommand(redisClient *c) {
             "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>]\r\n"));
     }
 }
-
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
+
+static void segvHandler (int sig, siginfo_t *info, void *secret) {
+
+  void *trace[100];
+  char **messages = (char **)NULL;
+  char *tmp;
+  int i, trace_size = 0;
+  long offset=0;
+  ucontext_t *uc = (ucontext_t *)secret;
+  time_t uptime = time(NULL)-server.stat_starttime;
+
+  redisLog(REDIS_WARNING, "application: redis,  signal: segmentation fault -%d-",REDIS_VERSION, sig);
+  redisLog(REDIS_WARNING, "%s", sdscatprintf(sdsempty(),
+        "redis_version:%s; "
+        "uptime_in_days:%d; "
+        "connected_clients:%d; "
+        "connected_slaves:%d; "
+        "used_memory:%zu; "
+        "changes_since_last_save:%lld; "
+        "bgsave_in_progress:%d; "
+        "last_save_time:%d; "
+        "total_connections_received:%lld; "
+        "total_commands_processed:%lld; "
+        "role:%s;"
+        ,REDIS_VERSION,
+        uptime,
+        listLength(server.clients)-listLength(server.slaves),
+        listLength(server.slaves),
+        server.usedmemory,
+        server.dirty,
+        server.bgsaveinprogress,
+        server.lastsave,
+        server.stat_numconnections,
+        server.stat_numcommands,
+        server.masterhost == NULL ? "master" : "slave"
+    ));
+
+  redisLog(REDIS_WARNING,"EIP %p",  (void *)uc->uc_mcontext.gregs[REG_EIP]);
+  redisLog(REDIS_WARNING,"EAX %p, EBX %p,  ECX %p, EDX %p", (void *)uc->uc_mcontext.gregs[REG_EAX], (void *)uc->uc_mcontext.gregs[REG_EBX],  (void *)uc->uc_mcontext.gregs[REG_ECX], (void *)uc->uc_mcontext.gregs[REG_EDX]);
+ 
+	
+  trace_size = backtrace(trace, 100);
+  char pointer[trace_size][11];
+    /* overwrite sigaction with caller's address */
+  trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];
+ for (i=1; i<trace_size; ++i)
+  	snprintf(pointer[i],11,"[%p]", trace[i]);
+
+  messages = backtrace_symbols(trace, trace_size);
+  
+  for (i=1; i<trace_size; ++i){
+	tmp=strstr(messages[i],pointer[i]);
+	if((tmp-2)[0]!=')'){
+		char *a=findFuncName(trace[i], &offset);
+		redisLog(REDIS_WARNING,"#%d (%s+0x%x) %s", i, a, (unsigned int)offset, tmp);
+		}
+	else
+		redisLog(REDIS_WARNING,"#%d %s", i, messages[i]);
+	}
+
+  free(messages);
+  exit(0);
+}
+
+void setupSigSegvAction(){
+  struct sigaction act;
+  sigemptyset (&act.sa_mask);
+  /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction  is used. Otherwise, sa_handler is used */
+  act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
+  act.sa_sigaction = segvHandler;
+  sigaction (SIGSEGV, &act, NULL);
+}
 /* =================================== Main! ================================ */
 
 #ifdef __linux__
@@ -4149,7 +4332,7 @@ int main(int argc, char **argv) {
 #ifdef __linux__
     linuxOvercommitMemoryWarning();
 #endif
-
+    
     initServerConfig();
     if (argc == 2) {
         ResetServerSaveParams();