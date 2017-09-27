 #endif
 #if APR_HAVE_UNISTD_H
 #include <unistd.h>
 #endif
 
 #ifdef AP_MPM_WANT_RECLAIM_CHILD_PROCESSES
+
+typedef enum {DO_NOTHING, SEND_SIGTERM, SEND_SIGKILL, GIVEUP} action_t;
+
+typedef struct extra_process_t {
+    struct extra_process_t *next;
+    pid_t pid;
+} extra_process_t;
+
+static extra_process_t *extras;
+
+void ap_register_extra_mpm_process(pid_t pid)
+{
+    extra_process_t *p = (extra_process_t *)malloc(sizeof(extra_process_t));
+
+    p->next = extras;
+    p->pid = pid;
+    extras = p;
+}
+
+int ap_unregister_extra_mpm_process(pid_t pid)
+{
+    extra_process_t *cur = extras;
+    extra_process_t *prev = NULL;
+
+    while (cur && cur->pid != pid) {
+        prev = cur;
+        cur = cur->next;
+    }
+
+    if (cur) {
+        if (prev) {
+            prev->next = cur->next;
+        }
+        else {
+            extras = cur->next;
+        }
+        free(cur);
+        return 1; /* found */
+    }
+    else {
+        /* we don't know about any such process */
+        return 0;
+    }
+}
+
+static int reclaim_one_pid(pid_t pid, action_t action)
+{
+    apr_proc_t proc;
+    apr_status_t waitret;
+
+    proc.pid = pid;
+    waitret = apr_proc_wait(&proc, NULL, NULL, APR_NOWAIT);
+    if (waitret != APR_CHILD_NOTDONE) {
+        return 1;
+    }
+
+    switch(action) {
+    case DO_NOTHING:
+        break;
+        
+    case SEND_SIGTERM:
+        /* ok, now it's being annoying */
+        ap_log_error(APLOG_MARK, APLOG_WARNING,
+                     0, ap_server_conf,
+                     "child process %" APR_PID_T_FMT
+                     " still did not exit, "
+                     "sending a SIGTERM",
+                     pid);
+        kill(pid, SIGTERM);
+        break;
+        
+    case SEND_SIGKILL:
+        ap_log_error(APLOG_MARK, APLOG_ERR,
+                     0, ap_server_conf,
+                     "child process %" APR_PID_T_FMT
+                     " still did not exit, "
+                     "sending a SIGKILL",
+                     pid);
+#ifndef BEOS
+        kill(pid, SIGKILL);
+#else
+        /* sending a SIGKILL kills the entire team on BeOS, and as
+         * httpd thread is part of that team it removes any chance
+         * of ever doing a restart.  To counter this I'm changing to
+         * use a kinder, gentler way of killing a specific thread
+         * that is just as effective.
+         */
+        kill_thread(pid);
+#endif
+        break;
+                
+    case GIVEUP:
+        /* gave it our best shot, but alas...  If this really
+         * is a child we are trying to kill and it really hasn't
+         * exited, we will likely fail to bind to the port
+         * after the restart.
+         */
+        ap_log_error(APLOG_MARK, APLOG_ERR,
+                     0, ap_server_conf,
+                     "could not make child process %" APR_PID_T_FMT
+                     " exit, "
+                     "attempting to continue anyway",
+                     pid);
+        break;
+    }
+    
+    return 0;
+}
+
 void ap_reclaim_child_processes(int terminate)
 {
+    apr_time_t waittime = 1024 * 16;
     int i;
-    long int waittime = 1024 * 16;      /* in usecs */
-    apr_status_t waitret;
-    int tries;
+    extra_process_t *cur_extra;
     int not_dead_yet;
     int max_daemons;
+    apr_time_t starttime = apr_time_now();
+    /* this table of actions and elapsed times tells what action is taken
+     * at which elapsed time from starting the reclaim
+     */
+    struct {
+        action_t action;
+        apr_time_t action_time;
+    } action_table[] = {
+        {DO_NOTHING, 0}, /* dummy entry for iterations where we reap
+                          * children but take no action against
+                          * stragglers
+                          */
+        {SEND_SIGTERM, apr_time_from_sec(3)},
+        {SEND_SIGTERM, apr_time_from_sec(5)},
+        {SEND_SIGTERM, apr_time_from_sec(7)},
+        {SEND_SIGKILL, apr_time_from_sec(9)},
+        {GIVEUP,       apr_time_from_sec(10)}
+    };
+    int cur_action;      /* index of action we decided to take this
+                          * iteration
+                          */
+    int next_action = 1; /* index of first real action */
 
     ap_mpm_query(AP_MPMQ_MAX_DAEMON_USED, &max_daemons);
 
-    for (tries = terminate ? 4 : 1; tries <= 9; ++tries) {
-        /* don't want to hold up progress any more than
-         * necessary, but we need to allow children a few moments to exit.
-         * Set delay with an exponential backoff.
-         */
+    do {
         apr_sleep(waittime);
+        /* don't let waittime get longer than 1 second; otherwise, we don't
+         * react quickly to the last child exiting, and taking action can
+         * be delayed
+         */
         waittime = waittime * 4;
+        if (waittime > apr_time_from_sec(1)) {
+            waittime = apr_time_from_sec(1);
+        }
+
+        /* see what action to take, if any */
+        if (action_table[next_action].action_time <= apr_time_now() - starttime) {
+            cur_action = next_action;
+            ++next_action;
+        }
+        else {
+            cur_action = 0; /* nothing to do */
+        }
 
         /* now see who is done */
         not_dead_yet = 0;
         for (i = 0; i < max_daemons; ++i) {
             pid_t pid = MPM_CHILD_PID(i);
-            apr_proc_t proc;
 
-            if (pid == 0)
-                continue;
+            if (pid == 0) {
+                continue; /* not every scoreboard entry is in use */
+            }
 
-            proc.pid = pid;
-            waitret = apr_proc_wait(&proc, NULL, NULL, APR_NOWAIT);
-            if (waitret != APR_CHILD_NOTDONE) {
+            if (reclaim_one_pid(pid, action_table[cur_action].action)) {
                 MPM_NOTE_CHILD_KILLED(i);
-                continue;
             }
+            else {
+                ++not_dead_yet;
+            }
+        }
+ 
+        cur_extra = extras;
+        while (cur_extra) {
+            extra_process_t *next = cur_extra->next;
 
-            ++not_dead_yet;
-            switch (tries) {
-            case 1:     /*  16ms */
-            case 2:     /*  82ms */
-            case 3:     /* 344ms */
-            case 4:     /*  16ms */
-                break;
-
-            case 5:     /*  82ms */
-            case 6:     /* 344ms */
-            case 7:     /* 1.4sec */
-                /* ok, now it's being annoying */
-                ap_log_error(APLOG_MARK, APLOG_WARNING,
-                             0, ap_server_conf,
-                             "child process %ld still did not exit, "
-                             "sending a SIGTERM",
-                             (long)pid);
-                kill(pid, SIGTERM);
-                break;
-
-            case 8:     /*  6 sec */
-                /* die child scum */
-                ap_log_error(APLOG_MARK, APLOG_ERR,
-                             0, ap_server_conf,
-                             "child process %ld still did not exit, "
-                             "sending a SIGKILL",
-                             (long)pid);
-#ifndef BEOS
-                kill(pid, SIGKILL);
-#else
-                /* sending a SIGKILL kills the entire team on BeOS, and as
-                 * httpd thread is part of that team it removes any chance
-                 * of ever doing a restart.  To counter this I'm changing to
-                 * use a kinder, gentler way of killing a specific thread
-                 * that is just as effective.
-                 */
-                kill_thread(pid);
-#endif
-                break;
-
-            case 9:     /* 14 sec */
-                /* gave it our best shot, but alas...  If this really
-                 * is a child we are trying to kill and it really hasn't
-                 * exited, we will likely fail to bind to the port
-                 * after the restart.
-                 */
-                ap_log_error(APLOG_MARK, APLOG_ERR,
-                             0, ap_server_conf,
-                             "could not make child process %ld exit, "
-                             "attempting to continue anyway",
-                             (long)pid);
-                break;
+            if (reclaim_one_pid(cur_extra->pid, action_table[cur_action].action)) {
+                AP_DEBUG_ASSERT(1 == ap_unregister_extra_mpm_process(cur_extra->pid));
+            }
+            else {
+                ++not_dead_yet;
             }
+            cur_extra = next;
         }
 
 #if APR_HAS_OTHER_CHILD
         apr_proc_other_child_check();
 #endif
 
-        if (!not_dead_yet) {
-            /* nothing left to wait for */
-            break;
-        }
-    }
+    } while (not_dead_yet > 0 &&
+             action_table[cur_action].action != GIVEUP);
 }
 #endif /* AP_MPM_WANT_RECLAIM_CHILD_PROCESSES */
 
 #ifdef AP_MPM_WANT_WAIT_OR_TIMEOUT
 
 /* number of calls to wait_or_timeout between writable probes */
