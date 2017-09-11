@@ -116,6 +116,15 @@ typedef struct sentinelAddr {
 #define SENTINEL_NO_FLAGS 0
 #define SENTINEL_GENERATE_EVENT 1
 
+/* Script execution flags and limits. */
+#define SENTINEL_SCRIPT_NONE 0
+#define SENTINEL_SCRIPT_RUNNING 1
+#define SENTINEL_SCRIPT_MAX_QUEUE 256
+#define SENTINEL_SCRIPT_MAX_RUNNING 16
+#define SENTINEL_SCRIPT_MAX_RUNTIME 60000 /* 60 seconds max exec time. */
+#define SENTINEL_SCRIPT_MAX_RETRY 10
+#define SENTINEL_SCRIPT_RETRY_DELAY 30000 /* 30 seconds between retries. */
+
 typedef struct sentinelRedisInstance {
     int flags;      /* See SRI_... defines */
     char *name;     /* Master name from the point of view of this sentinel. */
@@ -181,10 +190,25 @@ struct sentinelState {
                            Key is the instance name, value is the
                            sentinelRedisInstance structure pointer. */
     int tilt;           /* Are we in TILT mode? */
+    int running_scripts;    /* Number of scripts in execution right now. */
     mstime_t tilt_start_time;   /* When TITL started. */
     mstime_t previous_time;     /* Time last time we ran the time handler. */
+    list *scripts_queue;    /* Queue of user scripts to execute. */
 } sentinel;
 
+/* A script execution job. */
+typedef struct sentinelScriptJob {
+    int flags;              /* Script job flags: SENTINEL_SCRIPT_* */
+    int retry_num;          /* Number of times we tried to execute it. */
+    char **argv;            /* Arguments to call the script. */
+    mstime_t start_time;    /* Script execution time if the script is running,
+                               otherwise 0 if we are allowed to retry the
+                               execution at any time. If the script is not
+                               running and it's not 0, it means: do not run
+                               before the specified time. */
+    pid_t pid;              /* Script execution pid. */
+} sentinelScriptJob;
+
 /* ======================= hiredis ae.c adapters =============================
  * Note: this implementation is taken from hiredis/adapters/ae.h, however
  * we have our modified copy for Sentinel in order to use our allocator
@@ -295,6 +319,7 @@ const char *sentinelRedisInstanceTypeStr(sentinelRedisInstance *ri);
 void sentinelAbortFailover(sentinelRedisInstance *ri);
 void sentinelEvent(int level, char *type, sentinelRedisInstance *ri, const char *fmt, ...);
 sentinelRedisInstance *sentinelSelectSlave(sentinelRedisInstance *master);
+void sentinelScheduleScriptExecution(char *path, ...);
 
 /* ========================= Dictionary types =============================== */
 
@@ -371,6 +396,8 @@ void initSentinel(void) {
     sentinel.tilt = 0;
     sentinel.tilt_start_time = mstime();
     sentinel.previous_time = mstime();
+    sentinel.running_scripts = 0;
+    sentinel.scripts_queue = listCreate();
 }
 
 /* ============================== sentinelAddr ============================== */
@@ -406,32 +433,6 @@ void releaseSentinelAddr(sentinelAddr *sa) {
 
 /* =========================== Events notification ========================== */
 
-void sentinelCallNotificationScript(char *scriptpath, char *type, char *msg) {
-    pid_t pid = fork();
-
-    if (pid == -1) {
-        /* Parent on error. */
-        sentinelEvent(REDIS_WARNING,"-notification-script-error",NULL,
-                      "#can't fork: %s",strerror(errno));
-        return;
-    } else if (pid == 0) {
-        /* Child */
-        char *argv[4];
-
-        argv[0] = scriptpath;
-        argv[1] = type;
-        argv[2] = msg;
-        argv[3] = NULL;
-        execve(scriptpath,argv,environ);
-        /* If we are here an error occurred. */
-        sentinelEvent(REDIS_WARNING,"-notification-script-error",NULL,
-                      "#execve(2): %s",strerror(errno));
-        _exit(1);
-    } else {
-        sentinelEvent(REDIS_DEBUG,"+child",NULL,"%ld",(long)pid);
-    }
-}
-
 /* Send an event to log, pub/sub, user notification script.
  * 
  * 'level' is the log level for logging. Only REDIS_WARNING events will trigger
@@ -507,9 +508,256 @@ void sentinelEvent(int level, char *type, sentinelRedisInstance *ri,
         sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
                                          ri : ri->master;
         if (master->notification_script) {
-            sentinelCallNotificationScript(master->notification_script,
-                                           type,msg);
+            sentinelScheduleScriptExecution(master->notification_script,
+                type,msg,NULL);
+        }
+    }
+}
+
+/* ============================ script execution ============================ */
+
+/* Release a script job structure and all the associated data. */
+void sentinelReleaseScriptJob(sentinelScriptJob *sj) {
+    int j = 0;
+
+    while(sj->argv[j]) sdsfree(sj->argv[j++]);
+    zfree(sj->argv);
+    zfree(sj);
+}
+
+#define SENTINEL_SCRIPT_MAX_ARGS 16
+void sentinelScheduleScriptExecution(char *path, ...) {
+    va_list ap;
+    char *argv[SENTINEL_SCRIPT_MAX_ARGS+1];
+    int argc = 1;
+    sentinelScriptJob *sj;
+
+    va_start(ap, path);
+    while(argc < SENTINEL_SCRIPT_MAX_ARGS) {
+        argv[argc] = va_arg(ap,char*);
+        if (!argv[argc]) break;
+        argv[argc] = sdsnew(argv[argc]); /* Copy the string. */
+        argc++;
+    }
+    va_end(ap);
+    argv[0] = sdsnew(path);
+    
+    sj = zmalloc(sizeof(*sj));
+    sj->flags = SENTINEL_SCRIPT_NONE;
+    sj->retry_num = 0;
+    sj->argv = zmalloc(sizeof(char*)*(argc+1));
+    sj->start_time = 0;
+    sj->pid = 0;
+    memcpy(sj->argv,argv,sizeof(char*)*(argc+1));
+
+    listAddNodeTail(sentinel.scripts_queue,sj);
+
+    /* Remove the oldest non running script if we already hit the limit. */
+    if (listLength(sentinel.scripts_queue) > SENTINEL_SCRIPT_MAX_QUEUE) {
+        listNode *ln;
+        listIter li;
+
+        listRewind(sentinel.scripts_queue,&li);
+        while ((ln = listNext(&li)) != NULL) {
+            sj = ln->value;
+
+            if (sj->flags & SENTINEL_SCRIPT_RUNNING) continue;
+            /* The first node is the oldest as we add on tail. */
+            listDelNode(sentinel.scripts_queue,ln);
+            sentinelReleaseScriptJob(sj);
+            break;
         }
+        redisAssert(listLength(sentinel.scripts_queue) <=
+                    SENTINEL_SCRIPT_MAX_QUEUE);
+    }
+}
+
+/* Lookup a script in the scripts queue via pid, and returns the list node
+ * (so that we can easily remove it from the queue if needed). */
+listNode *sentinelGetScriptListNodeByPid(pid_t pid) {
+    listNode *ln;
+    listIter li;
+
+    listRewind(sentinel.scripts_queue,&li);
+    while ((ln = listNext(&li)) != NULL) {
+        sentinelScriptJob *sj = ln->value;
+
+        if ((sj->flags & SENTINEL_SCRIPT_RUNNING) && sj->pid == pid)
+            return ln;
+    }
+    return NULL;
+}
+
+/* Run pending scripts if we are not already at max number of running
+ * scripts. */
+void sentinelRunPendingScripts(void) {
+    listNode *ln;
+    listIter li;
+    mstime_t now = mstime();
+
+    /* Find jobs that are not running and run them, from the top to the
+     * tail of the queue, so we run older jobs first. */
+    listRewind(sentinel.scripts_queue,&li);
+    while (sentinel.running_scripts < SENTINEL_SCRIPT_MAX_RUNNING &&
+           (ln = listNext(&li)) != NULL)
+    {
+        sentinelScriptJob *sj = ln->value;
+        pid_t pid;
+
+        /* Skip if already running. */
+        if (sj->flags & SENTINEL_SCRIPT_RUNNING) continue;
+
+        /* Skip if it's a retry, but not enough time has elapsed. */
+        if (sj->start_time && sj->start_time > now) continue;
+
+        sj->flags |= SENTINEL_SCRIPT_RUNNING;
+        sj->start_time = mstime();
+        sj->retry_num++;
+        pid = fork();
+
+        if (pid == -1) {
+            /* Parent (fork error).
+             * We report fork errors as signal 99, in order to unify the
+             * reporting with other kind of errors. */
+            sentinelEvent(REDIS_WARNING,"-script-error",NULL,
+                          "%s %d %d", sj->argv[0], 99, 0);
+            sj->flags &= ~SENTINEL_SCRIPT_RUNNING;
+            sj->pid = 0;
+        } else if (pid == 0) {
+            /* Child */
+            execve(sj->argv[0],sj->argv,environ);
+            /* If we are here an error occurred. */
+            _exit(2); /* Don't retry execution. */
+        } else {
+            sentinel.running_scripts++;
+            sj->pid = pid;
+            sentinelEvent(REDIS_DEBUG,"+script-child",NULL,"%ld",(long)pid);
+        }
+    }
+}
+
+/* How much to delay the execution of a script that we need to retry after
+ * an error?
+ *
+ * We double the retry delay for every further retry we do. So for instance
+ * if RETRY_DELAY is set to 30 seconds and the max number of retries is 10
+ * starting from the second attempt to execute the script the delays are:
+ * 30 sec, 60 sec, 2 min, 4 min, 8 min, 16 min, 32 min, 64 min, 128 min. */
+mstime_t sentinelScriptRetryDelay(int retry_num) {
+    mstime_t delay = SENTINEL_SCRIPT_RETRY_DELAY;
+
+    while (retry_num-- > 1) delay *= 2;
+    return delay;
+}
+
+/* Check for scripts that terminated, and remove them from the queue if the
+ * script terminated successfully. If instead the script was terminated by
+ * a signal, or returned exit code "1", it is scheduled to run again if
+ * the max number of retries did not already elapsed. */
+void sentinelCollectTerminatedScripts(void) {
+    int statloc;
+    pid_t pid;
+
+    while ((pid = wait3(&statloc,WNOHANG,NULL)) > 0) {
+        int exitcode = WEXITSTATUS(statloc);
+        int bysignal = 0;
+        listNode *ln;
+        sentinelScriptJob *sj;
+
+        if (WIFSIGNALED(statloc)) bysignal = WTERMSIG(statloc);
+        sentinelEvent(REDIS_DEBUG,"-script-child",NULL,"%ld %d %d",
+            (long)pid, exitcode, bysignal);
+        
+        ln = sentinelGetScriptListNodeByPid(pid);
+        if (ln == NULL) {
+            redisLog(REDIS_WARNING,"wait3() returned a pid (%ld) we can't find in our scripts execution queue!", (long)pid);
+            continue;
+        }
+        sj = ln->value;
+
+        /* If the script was terminated by a signal or returns an
+         * exit code of "1" (that means: please retry), we reschedule it
+         * if the max number of retries is not already reached. */
+        if ((bysignal || exitcode == 1) &&
+            sj->retry_num != SENTINEL_SCRIPT_MAX_RETRY)
+        {
+            sj->flags &= ~SENTINEL_SCRIPT_RUNNING;
+            sj->pid = 0;
+            sj->start_time = mstime() +
+                             sentinelScriptRetryDelay(sj->retry_num);
+        } else {
+            /* Otherwise let's remove the script, but log the event if the
+             * execution did not terminated in the best of the ways. */
+            if (bysignal || exitcode != 0) {
+                sentinelEvent(REDIS_WARNING,"-script-error",NULL,
+                              "%s %d %d", sj->argv[0], bysignal, exitcode);
+            }
+            listDelNode(sentinel.scripts_queue,ln);
+            sentinelReleaseScriptJob(sj);
+            sentinel.running_scripts--;
+        }
+    }
+}
+
+/* Kill scripts in timeout, they'll be collected by the
+ * sentinelCollectTerminatedScripts() function. */
+void sentinelKillTimedoutScripts(void) {
+    listNode *ln;
+    listIter li;
+    mstime_t now = mstime();
+
+    listRewind(sentinel.scripts_queue,&li);
+    while ((ln = listNext(&li)) != NULL) {
+        sentinelScriptJob *sj = ln->value;
+
+        if (sj->flags & SENTINEL_SCRIPT_RUNNING &&
+            (now - sj->start_time) > SENTINEL_SCRIPT_MAX_RUNTIME)
+        {
+            sentinelEvent(REDIS_WARNING,"-script-timeout",NULL,"%s %ld",
+                sj->argv[0], (long)sj->pid);
+            kill(sj->pid,SIGKILL);
+        }
+    }
+}
+
+/* Implements SENTINEL PENDING-SCRIPTS command. */
+void sentinelPendingScriptsCommand(redisClient *c) {
+    listNode *ln;
+    listIter li;
+
+    addReplyMultiBulkLen(c,listLength(sentinel.scripts_queue));
+    listRewind(sentinel.scripts_queue,&li);
+    while ((ln = listNext(&li)) != NULL) {
+        sentinelScriptJob *sj = ln->value;
+        int j = 0;
+
+        addReplyMultiBulkLen(c,10);
+
+        addReplyBulkCString(c,"argv");
+        while (sj->argv[j]) j++;
+        addReplyMultiBulkLen(c,j);
+        j = 0;
+        while (sj->argv[j]) addReplyBulkCString(c,sj->argv[j++]);
+
+        addReplyBulkCString(c,"flags");
+        addReplyBulkCString(c,
+            (sj->flags & SENTINEL_SCRIPT_RUNNING) ? "running" : "scheduled");
+
+        addReplyBulkCString(c,"pid");
+        addReplyBulkLongLong(c,sj->pid);
+
+        if (sj->flags & SENTINEL_SCRIPT_RUNNING) {
+            addReplyBulkCString(c,"run-time");
+            addReplyBulkLongLong(c,mstime() - sj->start_time);
+        } else {
+            mstime_t delay = sj->start_time ? (sj->start_time-mstime()) : 0;
+            if (delay < 0) delay = 0;
+            addReplyBulkCString(c,"run-delay");
+            addReplyBulkLongLong(c,delay);
+        }
+
+        addReplyBulkCString(c,"retry-num");
+        addReplyBulkLongLong(c,sj->retry_num);
     }
 }
 
@@ -1696,6 +1944,11 @@ void sentinelCommand(redisClient *c) {
             addReplyBulkCString(c,addr->ip);
             addReplyBulkLongLong(c,addr->port);
         }
+    } else if (!strcasecmp(c->argv[1]->ptr,"pending-scripts")) {
+        /* SENTINEL PENDING-SCRIPTS */
+
+        if (c->argc != 2) goto numargserr;
+        sentinelPendingScriptsCommand(c);
     } else {
         addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                                (char*)c->argv[1]->ptr);
@@ -2557,27 +2810,11 @@ void sentinelCheckTiltCondition(void) {
     sentinel.previous_time = mstime();
 }
 
-/* Handle terminated childs resulting from calls to notifications and client
- * reconfigurations scripts. */
-void sentinelHandleChildren(void) {
-    int statloc;
-    pid_t pid;
-
-    if ((pid = wait3(&statloc,WNOHANG,NULL)) != 0) {
-        int exitcode = WEXITSTATUS(statloc);
-        int bysignal = 0;
-        
-        if (WIFSIGNALED(statloc)) bysignal = WTERMSIG(statloc);
-        sentinelEvent(REDIS_DEBUG,"-child",NULL,"%ld %d %d",
-            (long)pid, exitcode, bysignal);
-
-        /* TODO: remove client reconfiguration scripts from the queue. */
-    }
-}
-
 void sentinelTimer(void) {
     sentinelCheckTiltCondition();
     sentinelHandleDictOfRedisInstances(sentinel.masters);
-    sentinelHandleChildren();
+    sentinelRunPendingScripts();
+    sentinelCollectTerminatedScripts();
+    sentinelKillTimedoutScripts();
 }
 