 #include "apr_allocator.h"
 
 #include "httpd.h"
 #include "http_config.h"
 #include "http_log.h"
 #include "http_main.h"
-#include "mpm.h"
 #include "mpm_common.h"
 #include "ap_mpm.h"
 #include "ap_listen.h"
-#include "mpm_default.h"
+#include "util_mutex.h"
 
-#ifdef AP_MPM_WANT_SET_SCOREBOARD
 #include "scoreboard.h"
-#endif
 
 #ifdef HAVE_PWD_H
 #include <pwd.h>
 #endif
 #ifdef HAVE_GRP_H
 #include <grp.h>
 #endif
 #if APR_HAVE_UNISTD_H
 #include <unistd.h>
 #endif
 
+APLOG_USE_MODULE(core);
+
 #if AP_ENABLE_EXCEPTION_HOOK
 APR_HOOK_STRUCT(
     APR_HOOK_LINK(fatal_exception)
     APR_HOOK_LINK(monitor)
+    APR_HOOK_LINK(drop_privileges)
+    APR_HOOK_LINK(mpm)
+    APR_HOOK_LINK(mpm_query)
+    APR_HOOK_LINK(mpm_note_child_killed)
+    APR_HOOK_LINK(mpm_register_timed_callback)
+    APR_HOOK_LINK(mpm_get_name)
 )
 AP_IMPLEMENT_HOOK_RUN_ALL(int, fatal_exception,
                           (ap_exception_info_t *ei), (ei), OK, DECLINED)
 #else
 APR_HOOK_STRUCT(
     APR_HOOK_LINK(monitor)
+    APR_HOOK_LINK(drop_privileges)
+    APR_HOOK_LINK(mpm)
+    APR_HOOK_LINK(mpm_query)
+    APR_HOOK_LINK(mpm_note_child_killed)
+    APR_HOOK_LINK(mpm_register_timed_callback)
+    APR_HOOK_LINK(mpm_get_name)
 )
 #endif
 AP_IMPLEMENT_HOOK_RUN_ALL(int, monitor,
-                          (apr_pool_t *p), (p), OK, DECLINED)
-
-
-#ifdef AP_MPM_WANT_RECLAIM_CHILD_PROCESSES
-
-typedef enum {DO_NOTHING, SEND_SIGTERM, SEND_SIGKILL, GIVEUP} action_t;
-
-typedef struct extra_process_t {
-    struct extra_process_t *next;
-    pid_t pid;
-} extra_process_t;
-
-static extra_process_t *extras;
-
-void ap_register_extra_mpm_process(pid_t pid)
-{
-    extra_process_t *p = (extra_process_t *)malloc(sizeof(extra_process_t));
-
-    p->next = extras;
-    p->pid = pid;
-    extras = p;
-}
-
-int ap_unregister_extra_mpm_process(pid_t pid)
-{
-    extra_process_t *cur = extras;
-    extra_process_t *prev = NULL;
-
-    while (cur && cur->pid != pid) {
-        prev = cur;
-        cur = cur->next;
-    }
-
-    if (cur) {
-        if (prev) {
-            prev->next = cur->next;
-        }
-        else {
-            extras = cur->next;
-        }
-        free(cur);
-        return 1; /* found */
-    }
-    else {
-        /* we don't know about any such process */
-        return 0;
-    }
-}
-
-static int reclaim_one_pid(pid_t pid, action_t action)
-{
-    apr_proc_t proc;
-    apr_status_t waitret;
-
-    /* Ensure pid sanity. */
-    if (pid < 1) {
-        return 1;
-    }        
-
-    proc.pid = pid;
-    waitret = apr_proc_wait(&proc, NULL, NULL, APR_NOWAIT);
-    if (waitret != APR_CHILD_NOTDONE) {
-        return 1;
-    }
-
-    switch(action) {
-    case DO_NOTHING:
-        break;
-
-    case SEND_SIGTERM:
-        /* ok, now it's being annoying */
-        ap_log_error(APLOG_MARK, APLOG_WARNING,
-                     0, ap_server_conf,
-                     "child process %" APR_PID_T_FMT
-                     " still did not exit, "
-                     "sending a SIGTERM",
-                     pid);
-        kill(pid, SIGTERM);
-        break;
-
-    case SEND_SIGKILL:
-        ap_log_error(APLOG_MARK, APLOG_ERR,
-                     0, ap_server_conf,
-                     "child process %" APR_PID_T_FMT
-                     " still did not exit, "
-                     "sending a SIGKILL",
-                     pid);
-#ifndef BEOS
-        kill(pid, SIGKILL);
-#else
-        /* sending a SIGKILL kills the entire team on BeOS, and as
-         * httpd thread is part of that team it removes any chance
-         * of ever doing a restart.  To counter this I'm changing to
-         * use a kinder, gentler way of killing a specific thread
-         * that is just as effective.
-         */
-        kill_thread(pid);
-#endif
-        break;
-
-    case GIVEUP:
-        /* gave it our best shot, but alas...  If this really
-         * is a child we are trying to kill and it really hasn't
-         * exited, we will likely fail to bind to the port
-         * after the restart.
-         */
-        ap_log_error(APLOG_MARK, APLOG_ERR,
-                     0, ap_server_conf,
-                     "could not make child process %" APR_PID_T_FMT
-                     " exit, "
-                     "attempting to continue anyway",
-                     pid);
-        break;
-    }
-
-    return 0;
-}
-
-void ap_reclaim_child_processes(int terminate)
-{
-    apr_time_t waittime = 1024 * 16;
-    int i;
-    extra_process_t *cur_extra;
-    int not_dead_yet;
-    int max_daemons;
-    apr_time_t starttime = apr_time_now();
-    /* this table of actions and elapsed times tells what action is taken
-     * at which elapsed time from starting the reclaim
-     */
-    struct {
-        action_t action;
-        apr_time_t action_time;
-    } action_table[] = {
-        {DO_NOTHING, 0}, /* dummy entry for iterations where we reap
-                          * children but take no action against
-                          * stragglers
-                          */
-        {SEND_SIGTERM, apr_time_from_sec(3)},
-        {SEND_SIGTERM, apr_time_from_sec(5)},
-        {SEND_SIGTERM, apr_time_from_sec(7)},
-        {SEND_SIGKILL, apr_time_from_sec(9)},
-        {GIVEUP,       apr_time_from_sec(10)}
-    };
-    int cur_action;      /* index of action we decided to take this
-                          * iteration
-                          */
-    int next_action = 1; /* index of first real action */
-
-    ap_mpm_query(AP_MPMQ_MAX_DAEMON_USED, &max_daemons);
-
-    do {
-        apr_sleep(waittime);
-        /* don't let waittime get longer than 1 second; otherwise, we don't
-         * react quickly to the last child exiting, and taking action can
-         * be delayed
-         */
-        waittime = waittime * 4;
-        if (waittime > apr_time_from_sec(1)) {
-            waittime = apr_time_from_sec(1);
-        }
-
-        /* see what action to take, if any */
-        if (action_table[next_action].action_time <= apr_time_now() - starttime) {
-            cur_action = next_action;
-            ++next_action;
-        }
-        else {
-            cur_action = 0; /* nothing to do */
-        }
-
-        /* now see who is done */
-        not_dead_yet = 0;
-        for (i = 0; i < max_daemons; ++i) {
-            pid_t pid = MPM_CHILD_PID(i);
-
-            if (pid == 0) {
-                continue; /* not every scoreboard entry is in use */
-            }
-
-            if (reclaim_one_pid(pid, action_table[cur_action].action)) {
-                MPM_NOTE_CHILD_KILLED(i);
-            }
-            else {
-                ++not_dead_yet;
-            }
-        }
-
-        cur_extra = extras;
-        while (cur_extra) {
-            extra_process_t *next = cur_extra->next;
-
-            if (reclaim_one_pid(cur_extra->pid, action_table[cur_action].action)) {
-                AP_DEBUG_ASSERT(1 == ap_unregister_extra_mpm_process(cur_extra->pid));
-            }
-            else {
-                ++not_dead_yet;
-            }
-            cur_extra = next;
-        }
-#if APR_HAS_OTHER_CHILD
-        apr_proc_other_child_refresh_all(APR_OC_REASON_RESTART);
-#endif
-
-    } while (not_dead_yet > 0 &&
-             action_table[cur_action].action != GIVEUP);
-}
-
-void ap_relieve_child_processes(void)
-{
-    int i;
-    extra_process_t *cur_extra;
-    int max_daemons;
-
-    ap_mpm_query(AP_MPMQ_MAX_DAEMON_USED, &max_daemons);
-
-    /* now see who is done */
-    for (i = 0; i < max_daemons; ++i) {
-        pid_t pid = MPM_CHILD_PID(i);
-
-        if (pid == 0) {
-            continue; /* not every scoreboard entry is in use */
-        }
-
-        if (reclaim_one_pid(pid, DO_NOTHING)) {
-            MPM_NOTE_CHILD_KILLED(i);
-        }
-    }
-
-    cur_extra = extras;
-    while (cur_extra) {
-        extra_process_t *next = cur_extra->next;
-
-        if (reclaim_one_pid(cur_extra->pid, DO_NOTHING)) {
-            AP_DEBUG_ASSERT(1 == ap_unregister_extra_mpm_process(cur_extra->pid));
-        }
-        cur_extra = next;
-    }
-}
-
-/* Before sending the signal to the pid this function verifies that
- * the pid is a member of the current process group; either using
- * apr_proc_wait(), where waitpid() guarantees to fail for non-child
- * processes; or by using getpgid() directly, if available. */
-apr_status_t ap_mpm_safe_kill(pid_t pid, int sig)
-{
-#ifndef HAVE_GETPGID
-    apr_proc_t proc;
-    apr_status_t rv;
-    apr_exit_why_e why;
-    int status;
-
-    /* Ensure pid sanity */
-    if (pid < 1) {
-        return APR_EINVAL;
-    }
-
-    proc.pid = pid;
-    rv = apr_proc_wait(&proc, &status, &why, APR_NOWAIT);
-    if (rv == APR_CHILD_DONE) {
-#ifdef AP_MPM_WANT_PROCESS_CHILD_STATUS
-        /* The child already died - log the termination status if
-         * necessary: */
-        ap_process_child_status(&proc, why, status);
-#endif
-        return APR_EINVAL;
-    }
-    else if (rv != APR_CHILD_NOTDONE) {
-        /* The child is already dead and reaped, or was a bogus pid -
-         * log this either way. */
-        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf,
-                     "cannot send signal %d to pid %ld (non-child or "
-                     "already dead)", sig, (long)pid);
-        return APR_EINVAL;
-    }
-#else
-    pid_t pg;
-
-    /* Ensure pid sanity. */
-    if (pid < 1) {
-        return APR_EINVAL;
-    }
-
-    pg = getpgid(pid);    
-    if (pg == -1) {
-        /* Process already dead... */
-        return errno;
-    }
-
-    if (pg != getpgrp()) {
-        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, ap_server_conf,
-                     "refusing to send signal %d to pid %ld outside "
-                     "process group", sig, (long)pid);
-        return APR_EINVAL;
-    }
-#endif        
-
-    return kill(pid, sig) ? errno : APR_SUCCESS;
-}
-#endif /* AP_MPM_WANT_RECLAIM_CHILD_PROCESSES */
-
-#ifdef AP_MPM_WANT_WAIT_OR_TIMEOUT
+                          (apr_pool_t *p, server_rec *s), (p, s), OK, DECLINED)
+AP_IMPLEMENT_HOOK_RUN_ALL(int, drop_privileges,
+                          (apr_pool_t * pchild, server_rec * s),
+                          (pchild, s), OK, DECLINED)
+AP_IMPLEMENT_HOOK_RUN_FIRST(int, mpm,
+                            (apr_pool_t *pconf, apr_pool_t *plog, server_rec *s),
+                            (pconf, plog, s), DECLINED)
+AP_IMPLEMENT_HOOK_RUN_FIRST(int, mpm_query,
+                            (int query_code, int *result, apr_status_t *_rv),
+                            (query_code, result, _rv), DECLINED)
+AP_IMPLEMENT_HOOK_RUN_FIRST(apr_status_t, mpm_note_child_killed,
+                            (int childnum),
+                            (childnum), APR_ENOTIMPL)
+AP_IMPLEMENT_HOOK_RUN_FIRST(apr_status_t, mpm_register_timed_callback,
+                            (apr_time_t t, ap_mpm_callback_fn_t *cbfn, void *baton),
+                            (t, cbfn, baton), APR_ENOTIMPL)
+AP_IMPLEMENT_HOOK_RUN_FIRST(const char *, mpm_get_name,
+                            (void),
+                            (), NULL)
 
 /* number of calls to wait_or_timeout between writable probes */
 #ifndef INTERVAL_OF_WRITABLE_PROBES
 #define INTERVAL_OF_WRITABLE_PROBES 10
 #endif
 static int wait_or_timeout_counter;
 
 void ap_wait_or_timeout(apr_exit_why_e *status, int *exitcode, apr_proc_t *ret,
-                        apr_pool_t *p)
+                        apr_pool_t *p, server_rec *s)
 {
     apr_status_t rv;
 
     ++wait_or_timeout_counter;
     if (wait_or_timeout_counter == INTERVAL_OF_WRITABLE_PROBES) {
         wait_or_timeout_counter = 0;
-        ap_run_monitor(p);
+        ap_run_monitor(p, s);
     }
 
     rv = apr_proc_wait_all_procs(ret, exitcode, status, APR_NOWAIT, p);
     if (APR_STATUS_IS_EINTR(rv)) {
         ret->pid = -1;
         return;
     }
 
     if (APR_STATUS_IS_CHILD_DONE(rv)) {
         return;
     }
 
-#ifdef NEED_WAITPID
-    if ((ret = reap_children(exitcode, status)) > 0) {
-        return;
-    }
-#endif
-
-    apr_sleep(SCOREBOARD_MAINTENANCE_INTERVAL);
+    apr_sleep(1000000);
     ret->pid = -1;
     return;
 }
-#endif /* AP_MPM_WANT_WAIT_OR_TIMEOUT */
-
-#ifdef AP_MPM_WANT_PROCESS_CHILD_STATUS
-int ap_process_child_status(apr_proc_t *pid, apr_exit_why_e why, int status)
-{
-    int signum = status;
-    const char *sigdesc = apr_signal_description_get(signum);
-
-    /* Child died... if it died due to a fatal error,
-     * we should simply bail out.  The caller needs to
-     * check for bad rc from us and exit, running any
-     * appropriate cleanups.
-     *
-     * If the child died due to a resource shortage,
-     * the parent should limit the rate of forking
-     */
-    if (APR_PROC_CHECK_EXIT(why)) {
-        if (status == APEXIT_CHILDSICK) {
-            return status;
-        }
-
-        if (status == APEXIT_CHILDFATAL) {
-            ap_log_error(APLOG_MARK, APLOG_ALERT,
-                         0, ap_server_conf,
-                         "Child %" APR_PID_T_FMT
-                         " returned a Fatal error... Apache is exiting!",
-                         pid->pid);
-            return APEXIT_CHILDFATAL;
-        }
-
-        return 0;
-    }
-
-    if (APR_PROC_CHECK_SIGNALED(why)) {
-        switch (signum) {
-        case SIGTERM:
-        case SIGHUP:
-        case AP_SIG_GRACEFUL:
-        case SIGKILL:
-            break;
-
-        default:
-            if (APR_PROC_CHECK_CORE_DUMP(why)) {
-                ap_log_error(APLOG_MARK, APLOG_NOTICE,
-                             0, ap_server_conf,
-                             "child pid %ld exit signal %s (%d), "
-                             "possible coredump in %s",
-                             (long)pid->pid, sigdesc, signum,
-                             ap_coredump_dir);
-            }
-            else {
-                ap_log_error(APLOG_MARK, APLOG_NOTICE,
-                             0, ap_server_conf,
-                             "child pid %ld exit signal %s (%d)",
-                             (long)pid->pid, sigdesc, signum);
-            }
-        }
-    }
-    return 0;
-}
-#endif /* AP_MPM_WANT_PROCESS_CHILD_STATUS */
 
-#if defined(TCP_NODELAY) && !defined(MPE) && !defined(TPF)
+#if defined(TCP_NODELAY)
 void ap_sock_disable_nagle(apr_socket_t *s)
 {
     /* The Nagle algorithm says that we should delay sending partial
      * packets in hopes of getting more data.  We don't want to do
      * this; we are not telnet.  There are bad interactions between
      * persistent connections and Nagle's algorithm that have very severe
