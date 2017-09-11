@@ -37,6 +37,8 @@
 #include <arpa/inet.h>
 #include <sys/socket.h>
 
+extern char **environ;
+
 #define REDIS_SENTINEL_PORT 26379
 
 /* ======================== Sentinel global state =========================== */
@@ -169,7 +171,7 @@ typedef struct sentinelRedisInstance {
     struct sentinelRedisInstance *promoted_slave; /* Promoted slave instance. */
     /* Scripts executed to notify admin or reconfigure clients: when they
      * are set to NULL no script is executed. */
-    char *notify_script;
+    char *notification_script;
     char *client_reconfig_script;
 } sentinelRedisInstance;
 
@@ -291,6 +293,7 @@ void sentinelDisconnectInstanceFromContext(const redisAsyncContext *c);
 void sentinelKillLink(sentinelRedisInstance *ri, redisAsyncContext *c);
 const char *sentinelRedisInstanceTypeStr(sentinelRedisInstance *ri);
 void sentinelAbortFailover(sentinelRedisInstance *ri);
+void sentinelEvent(int level, char *type, sentinelRedisInstance *ri, const char *fmt, ...);
 
 /* ========================= Dictionary types =============================== */
 
@@ -403,7 +406,29 @@ void releaseSentinelAddr(sentinelAddr *sa) {
 /* =========================== Events notification ========================== */
 
 void sentinelCallNotificationScript(char *scriptpath, char *type, char *msg) {
-    /* TODO: implement it. */
+    pid_t pid = fork();
+
+    if (pid == -1) {
+        /* Parent on error. */
+        sentinelEvent(REDIS_WARNING,"-notification-script-error",NULL,
+                      "#can't fork: %s",strerror(errno));
+        return;
+    } else if (pid == 0) {
+        /* Child */
+        char *argv[4];
+
+        argv[0] = scriptpath;
+        argv[1] = type;
+        argv[2] = msg;
+        argv[3] = NULL;
+        execve(scriptpath,argv,environ);
+        /* If we are here an error occurred. */
+        sentinelEvent(REDIS_WARNING,"-notification-script-error",NULL,
+                      "#execve(2): %s",strerror(errno));
+        _exit(1);
+    } else {
+        sentinelEvent(REDIS_DEBUG,"+child",NULL,"%ld",(long)pid);
+    }
 }
 
 /* Send an event to log, pub/sub, user notification script.
@@ -480,8 +505,9 @@ void sentinelEvent(int level, char *type, sentinelRedisInstance *ri,
     if (level == REDIS_WARNING && ri != NULL) {
         sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
                                          ri : ri->master;
-        if (master->notify_script) {
-            sentinelCallNotificationScript(master->notify_script,type,msg);
+        if (master->notification_script) {
+            sentinelCallNotificationScript(master->notification_script,
+                                           type,msg);
         }
     }
 }
@@ -584,7 +610,7 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     ri->failover_start_time = 0;
     ri->failover_timeout = SENTINEL_DEFAULT_FAILOVER_TIMEOUT;
     ri->promoted_slave = NULL;
-    ri->notify_script = NULL;
+    ri->notification_script = NULL;
     ri->client_reconfig_script = NULL;
 
     /* Add into the right table. */
@@ -608,7 +634,7 @@ void releaseSentinelRedisInstance(sentinelRedisInstance *ri) {
     /* Free other resources. */
     sdsfree(ri->name);
     sdsfree(ri->runid);
-    sdsfree(ri->notify_script);
+    sdsfree(ri->notification_script);
     sdsfree(ri->client_reconfig_script);
     sdsfree(ri->slave_master_host);
     sdsfree(ri->leader);
@@ -881,6 +907,21 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         ri = sentinelGetMasterByName(argv[1]);
         if (!ri) return "No such master with specified name.";
         ri->parallel_syncs = atoi(argv[2]);
+   } else if (!strcasecmp(argv[0],"notification-script") && argc == 3) {
+        /* notification-script <name> <path> */
+        ri = sentinelGetMasterByName(argv[1]);
+        if (!ri) return "No such master with specified name.";
+        if (access(argv[2],X_OK) == -1)
+            return "Notification script seems non existing or non executable.";
+        ri->notification_script = sdsnew(argv[2]);
+   } else if (!strcasecmp(argv[0],"client-reconfig-script") && argc == 3) {
+        /* client-reconfig-script <name> <path> */
+        ri = sentinelGetMasterByName(argv[1]);
+        if (!ri) return "No such master with specified name.";
+        if (access(argv[2],X_OK) == -1)
+            return "Client reconfiguration script seems non existing or "
+                   "non executable.";
+        ri->client_reconfig_script = sdsnew(argv[2]);
     } else {
         return "Unrecognized sentinel configuration statement.";
     }
@@ -2511,8 +2552,27 @@ void sentinelCheckTiltCondition(void) {
     sentinel.previous_time = mstime();
 }
 
+/* Handle terminated childs resulting from calls to notifications and client
+ * reconfigurations scripts. */
+void sentinelHandleChildren(void) {
+    int statloc;
+    pid_t pid;
+
+    if ((pid = wait3(&statloc,WNOHANG,NULL)) != 0) {
+        int exitcode = WEXITSTATUS(statloc);
+        int bysignal = 0;
+        
+        if (WIFSIGNALED(statloc)) bysignal = WTERMSIG(statloc);
+        sentinelEvent(REDIS_DEBUG,"-child",NULL,"%ld %d %d",
+            (long)pid, exitcode, bysignal);
+
+        /* TODO: remove client reconfiguration scripts from the queue. */
+    }
+}
+
 void sentinelTimer(void) {
     sentinelCheckTiltCondition();
     sentinelHandleDictOfRedisInstances(sentinel.masters);
+    sentinelHandleChildren();
 }
 