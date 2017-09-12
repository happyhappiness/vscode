@@ -544,6 +544,7 @@ static struct redisCommand cmdTable[] = {
     {"debug",debugCommand,-2,REDIS_CMD_INLINE},
     {NULL,NULL,0,0}
 };
+
 /*============================ Utility functions ============================ */
 
 /* Glob-style pattern matching. */
@@ -1025,7 +1026,7 @@ static void appendServerSaveParams(time_t seconds, int changes) {
     server.saveparamslen++;
 }
 
-static void ResetServerSaveParams() {
+static void resetServerSaveParams() {
     zfree(server.saveparams);
     server.saveparams = NULL;
     server.saveparamslen = 0;
@@ -1054,7 +1055,7 @@ static void initServerConfig() {
     server.sharingpoolsize = 1024;
     server.maxclients = 0;
     server.maxmemory = 0;
-    ResetServerSaveParams();
+    resetServerSaveParams();
 
     appendServerSaveParams(60*60,1);  /* save after 1 hour and 1 change */
     appendServerSaveParams(300,100);  /* save after 5 minutes and 100 changes */
@@ -5534,150 +5535,91 @@ static void debugCommand(redisClient *c) {
     }
 }
 
-#ifdef HAVE_BACKTRACE
-static struct redisFunctionSym symsTable[] = {
-{"compareStringObjects", (unsigned long)compareStringObjects},
-{"isStringRepresentableAsLong", (unsigned long)isStringRepresentableAsLong},
-{"dictEncObjKeyCompare", (unsigned long)dictEncObjKeyCompare},
-{"dictEncObjHash", (unsigned long)dictEncObjHash},
-{"incrDecrCommand", (unsigned long)incrDecrCommand},
-{"freeStringObject", (unsigned long)freeStringObject},
-{"freeListObject", (unsigned long)freeListObject},
-{"freeSetObject", (unsigned long)freeSetObject},
-{"decrRefCount", (unsigned long)decrRefCount},
-{"createObject", (unsigned long)createObject},
-{"freeClient", (unsigned long)freeClient},
-{"rdbLoad", (unsigned long)rdbLoad},
-{"rdbSaveStringObject", (unsigned long)rdbSaveStringObject},
-{"rdbSaveStringObjectRaw", (unsigned long)rdbSaveStringObjectRaw},
-{"addReply", (unsigned long)addReply},
-{"addReplySds", (unsigned long)addReplySds},
-{"incrRefCount", (unsigned long)incrRefCount},
-{"rdbSaveBackground", (unsigned long)rdbSaveBackground},
-{"createStringObject", (unsigned long)createStringObject},
-{"replicationFeedSlaves", (unsigned long)replicationFeedSlaves},
-{"syncWithMaster", (unsigned long)syncWithMaster},
-{"tryObjectSharing", (unsigned long)tryObjectSharing},
-{"tryObjectEncoding", (unsigned long)tryObjectEncoding},
-{"getDecodedObject", (unsigned long)getDecodedObject},
-{"removeExpire", (unsigned long)removeExpire},
-{"expireIfNeeded", (unsigned long)expireIfNeeded},
-{"deleteIfVolatile", (unsigned long)deleteIfVolatile},
-{"deleteKey", (unsigned long)deleteKey},
-{"getExpire", (unsigned long)getExpire},
-{"setExpire", (unsigned long)setExpire},
-{"updateSlavesWaitingBgsave", (unsigned long)updateSlavesWaitingBgsave},
-{"freeMemoryIfNeeded", (unsigned long)freeMemoryIfNeeded},
-{"authCommand", (unsigned long)authCommand},
-{"pingCommand", (unsigned long)pingCommand},
-{"echoCommand", (unsigned long)echoCommand},
-{"setCommand", (unsigned long)setCommand},
-{"setnxCommand", (unsigned long)setnxCommand},
-{"getCommand", (unsigned long)getCommand},
-{"delCommand", (unsigned long)delCommand},
-{"existsCommand", (unsigned long)existsCommand},
-{"incrCommand", (unsigned long)incrCommand},
-{"decrCommand", (unsigned long)decrCommand},
-{"incrbyCommand", (unsigned long)incrbyCommand},
-{"decrbyCommand", (unsigned long)decrbyCommand},
-{"selectCommand", (unsigned long)selectCommand},
-{"randomkeyCommand", (unsigned long)randomkeyCommand},
-{"keysCommand", (unsigned long)keysCommand},
-{"dbsizeCommand", (unsigned long)dbsizeCommand},
-{"lastsaveCommand", (unsigned long)lastsaveCommand},
-{"saveCommand", (unsigned long)saveCommand},
-{"bgsaveCommand", (unsigned long)bgsaveCommand},
-{"shutdownCommand", (unsigned long)shutdownCommand},
-{"moveCommand", (unsigned long)moveCommand},
-{"renameCommand", (unsigned long)renameCommand},
-{"renamenxCommand", (unsigned long)renamenxCommand},
-{"lpushCommand", (unsigned long)lpushCommand},
-{"rpushCommand", (unsigned long)rpushCommand},
-{"lpopCommand", (unsigned long)lpopCommand},
-{"rpopCommand", (unsigned long)rpopCommand},
-{"llenCommand", (unsigned long)llenCommand},
-{"lindexCommand", (unsigned long)lindexCommand},
-{"lrangeCommand", (unsigned long)lrangeCommand},
-{"ltrimCommand", (unsigned long)ltrimCommand},
-{"typeCommand", (unsigned long)typeCommand},
-{"lsetCommand", (unsigned long)lsetCommand},
-{"saddCommand", (unsigned long)saddCommand},
-{"sremCommand", (unsigned long)sremCommand},
-{"smoveCommand", (unsigned long)smoveCommand},
-{"sismemberCommand", (unsigned long)sismemberCommand},
-{"scardCommand", (unsigned long)scardCommand},
-{"spopCommand", (unsigned long)spopCommand},
-{"srandmemberCommand", (unsigned long)srandmemberCommand},
-{"sinterCommand", (unsigned long)sinterCommand},
-{"sinterstoreCommand", (unsigned long)sinterstoreCommand},
-{"sunionCommand", (unsigned long)sunionCommand},
-{"sunionstoreCommand", (unsigned long)sunionstoreCommand},
-{"sdiffCommand", (unsigned long)sdiffCommand},
-{"sdiffstoreCommand", (unsigned long)sdiffstoreCommand},
-{"syncCommand", (unsigned long)syncCommand},
-{"flushdbCommand", (unsigned long)flushdbCommand},
-{"flushallCommand", (unsigned long)flushallCommand},
-{"sortCommand", (unsigned long)sortCommand},
-{"lremCommand", (unsigned long)lremCommand},
-{"infoCommand", (unsigned long)infoCommand},
-{"mgetCommand", (unsigned long)mgetCommand},
-{"monitorCommand", (unsigned long)monitorCommand},
-{"expireCommand", (unsigned long)expireCommand},
-{"expireatCommand", (unsigned long)expireatCommand},
-{"getsetCommand", (unsigned long)getsetCommand},
-{"ttlCommand", (unsigned long)ttlCommand},
-{"slaveofCommand", (unsigned long)slaveofCommand},
-{"debugCommand", (unsigned long)debugCommand},
-{"processCommand", (unsigned long)processCommand},
-{"setupSigSegvAction", (unsigned long)setupSigSegvAction},
-{"readQueryFromClient", (unsigned long)readQueryFromClient},
-{"rdbRemoveTempFile", (unsigned long)rdbRemoveTempFile},
-{"msetGenericCommand", (unsigned long)msetGenericCommand},
-{"msetCommand", (unsigned long)msetCommand},
-{"msetnxCommand", (unsigned long)msetnxCommand},
-{"zslCreateNode", (unsigned long)zslCreateNode},
-{"zslCreate", (unsigned long)zslCreate},
-{"zslFreeNode",(unsigned long)zslFreeNode},
-{"zslFree",(unsigned long)zslFree},
-{"zslRandomLevel",(unsigned long)zslRandomLevel},
-{"zslInsert",(unsigned long)zslInsert},
-{"zslDelete",(unsigned long)zslDelete},
-{"createZsetObject",(unsigned long)createZsetObject},
-{"zaddCommand",(unsigned long)zaddCommand},
-{"zrangeGenericCommand",(unsigned long)zrangeGenericCommand},
-{"zrangeCommand",(unsigned long)zrangeCommand},
-{"zrevrangeCommand",(unsigned long)zrevrangeCommand},
-{"zremCommand",(unsigned long)zremCommand},
-{"rdbSaveDoubleValue",(unsigned long)rdbSaveDoubleValue},
-{"rdbLoadDoubleValue",(unsigned long)rdbLoadDoubleValue},
-{"feedAppendOnlyFile",(unsigned long)feedAppendOnlyFile},
-{NULL,0}
-};
+/* =================================== Main! ================================ */
 
-/* This function try to convert a pointer into a function name. It's used in
- * oreder to provide a backtrace under segmentation fault that's able to
- * display functions declared as static (otherwise the backtrace is useless). */
-static char *findFuncName(void *pointer, unsigned long *offset){
-    int i, ret = -1;
-    unsigned long off, minoff = 0;
+#ifdef __linux__
+int linuxOvercommitMemoryValue(void) {
+    FILE *fp = fopen("/proc/sys/vm/overcommit_memory","r");
+    char buf[64];
 
-    /* Try to match against the Symbol with the smallest offset */
-    for (i=0; symsTable[i].pointer; i++) {
-        unsigned long lp = (unsigned long) pointer;
+    if (!fp) return -1;
+    if (fgets(buf,64,fp) == NULL) {
+        fclose(fp);
+        return -1;
+    }
+    fclose(fp);
 
-        if (lp != (unsigned long)-1 && lp >= symsTable[i].pointer) {
-            off=lp-symsTable[i].pointer;
-            if (ret < 0 || off < minoff) {
-                minoff=off;
-                ret=i;
-            }
-        }
+    return atoi(buf);
+}
+
+void linuxOvercommitMemoryWarning(void) {
+    if (linuxOvercommitMemoryValue() == 0) {
+        redisLog(REDIS_WARNING,"WARNING overcommit_memory is set to 0! Background save may fail under low condition memory. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.");
+    }
+}
+#endif /* __linux__ */
+
+static void daemonize(void) {
+    int fd;
+    FILE *fp;
+
+    if (fork() != 0) exit(0); /* parent exits */
+    setsid(); /* create a new session */
+
+    /* Every output goes to /dev/null. If Redis is daemonized but
+     * the 'logfile' is set to 'stdout' in the configuration file
+     * it will not log at all. */
+    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
+        dup2(fd, STDIN_FILENO);
+        dup2(fd, STDOUT_FILENO);
+        dup2(fd, STDERR_FILENO);
+        if (fd > STDERR_FILENO) close(fd);
+    }
+    /* Try to write the pid file */
+    fp = fopen(server.pidfile,"w");
+    if (fp) {
+        fprintf(fp,"%d\n",getpid());
+        fclose(fp);
     }
-    if (ret == -1) return NULL;
-    *offset = minoff;
-    return symsTable[ret].name;
 }
 
+int main(int argc, char **argv) {
+    initServerConfig();
+    if (argc == 2) {
+        resetServerSaveParams();
+        loadServerConfig(argv[1]);
+    } else if (argc > 2) {
+        fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
+        exit(1);
+    } else {
+        redisLog(REDIS_WARNING,"Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'");
+    }
+    initServer();
+    if (server.daemonize) daemonize();
+    redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
+#ifdef __linux__
+    linuxOvercommitMemoryWarning();
+#endif
+    if (server.appendonly) {
+        if (loadAppendOnlyFile(server.appendfilename) == REDIS_OK)
+            redisLog(REDIS_NOTICE,"DB loaded from append only file");
+    } else {
+        if (rdbLoad(server.dbfilename) == REDIS_OK)
+            redisLog(REDIS_NOTICE,"DB loaded from disk");
+    }
+    if (aeCreateFileEvent(server.el, server.fd, AE_READABLE,
+        acceptHandler, NULL, NULL) == AE_ERR) oom("creating file event");
+    redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
+    aeMain(server.el);
+    aeDeleteEventLoop(server.el);
+    return 0;
+}
+
+/* ============================= Backtrace support ========================= */
+
+#ifdef HAVE_BACKTRACE
+static char *findFuncName(void *pointer, unsigned long *offset);
+
 static void *getMcontextEip(ucontext_t *uc) {
 #if defined(__FreeBSD__)
     return (void*) uc->uc_mcontext.mc_eip;
@@ -5772,87 +5714,39 @@ static void setupSigSegvAction(void) {
     sigaction (SIGBUS, &act, NULL);
     return;
 }
-#else /* HAVE_BACKTRACE */
-static void setupSigSegvAction(void) {
-}
-#endif /* HAVE_BACKTRACE */
 
-/* =================================== Main! ================================ */
+#include "staticsymbols.h"
+/* This function try to convert a pointer into a function name. It's used in
+ * oreder to provide a backtrace under segmentation fault that's able to
+ * display functions declared as static (otherwise the backtrace is useless). */
+static char *findFuncName(void *pointer, unsigned long *offset){
+    int i, ret = -1;
+    unsigned long off, minoff = 0;
 
-#ifdef __linux__
-int linuxOvercommitMemoryValue(void) {
-    FILE *fp = fopen("/proc/sys/vm/overcommit_memory","r");
-    char buf[64];
+    /* Try to match against the Symbol with the smallest offset */
+    for (i=0; symsTable[i].pointer; i++) {
+        unsigned long lp = (unsigned long) pointer;
 
-    if (!fp) return -1;
-    if (fgets(buf,64,fp) == NULL) {
-        fclose(fp);
-        return -1;
+        if (lp != (unsigned long)-1 && lp >= symsTable[i].pointer) {
+            off=lp-symsTable[i].pointer;
+            if (ret < 0 || off < minoff) {
+                minoff=off;
+                ret=i;
+            }
+        }
     }
-    fclose(fp);
-
-    return atoi(buf);
+    if (ret == -1) return NULL;
+    *offset = minoff;
+    return symsTable[ret].name;
 }
-
-void linuxOvercommitMemoryWarning(void) {
-    if (linuxOvercommitMemoryValue() == 0) {
-        redisLog(REDIS_WARNING,"WARNING overcommit_memory is set to 0! Background save may fail under low condition memory. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.");
-    }
+#else /* HAVE_BACKTRACE */
+static void setupSigSegvAction(void) {
 }
-#endif /* __linux__ */
+#endif /* HAVE_BACKTRACE */
 
-static void daemonize(void) {
-    int fd;
-    FILE *fp;
 
-    if (fork() != 0) exit(0); /* parent exits */
-    setsid(); /* create a new session */
 
-    /* Every output goes to /dev/null. If Redis is daemonized but
-     * the 'logfile' is set to 'stdout' in the configuration file
-     * it will not log at all. */
-    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
-        dup2(fd, STDIN_FILENO);
-        dup2(fd, STDOUT_FILENO);
-        dup2(fd, STDERR_FILENO);
-        if (fd > STDERR_FILENO) close(fd);
-    }
-    /* Try to write the pid file */
-    fp = fopen(server.pidfile,"w");
-    if (fp) {
-        fprintf(fp,"%d\n",getpid());
-        fclose(fp);
-    }
-}
+/* The End */
+
+
 
-int main(int argc, char **argv) {
-    initServerConfig();
-    if (argc == 2) {
-        ResetServerSaveParams();
-        loadServerConfig(argv[1]);
-    } else if (argc > 2) {
-        fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
-        exit(1);
-    } else {
-        redisLog(REDIS_WARNING,"Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'");
-    }
-    initServer();
-    if (server.daemonize) daemonize();
-    redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
-#ifdef __linux__
-    linuxOvercommitMemoryWarning();
-#endif
-    if (server.appendonly) {
-        if (loadAppendOnlyFile(server.appendfilename) == REDIS_OK)
-            redisLog(REDIS_NOTICE,"DB loaded from append only file");
-    } else {
-        if (rdbLoad(server.dbfilename) == REDIS_OK)
-            redisLog(REDIS_NOTICE,"DB loaded from disk");
-    }
-    if (aeCreateFileEvent(server.el, server.fd, AE_READABLE,
-        acceptHandler, NULL, NULL) == AE_ERR) oom("creating file event");
-    redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
-    aeMain(server.el);
-    aeDeleteEventLoop(server.el);
-    return 0;
-}