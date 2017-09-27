 				"removed PID file %s (pid=%ld)",
 				pidfile, (long)getpid());
 	}
 
 	ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
 		    "caught SIGTERM, shutting down");
+
+        return 1;
+    } else if (shutdown_pending) {
+        /* Time to perform a graceful shut down:
+         * Reap the inactive children, and ask the active ones
+         * to close their listeners, then wait until they are
+         * all done to exit.
+         */
+        int active_children;
+        apr_time_t cutoff = 0;
+
+        /* Stop listening */
+        ap_close_listeners();
+
+        /* kill off the idle ones */
+        ap_mpm_pod_killpg(pod, ap_max_daemons_limit);
+
+        /* Send SIGUSR1 to the active children */
+        active_children = 0;
+        for (index = 0; index < ap_daemons_limit; ++index) {
+            if (ap_scoreboard_image->servers[index][0].status != SERVER_DEAD) {
+                /* Ask each child to close its listeners. */
+                kill(MPM_CHILD_PID(index), AP_SIG_GRACEFUL);
+                active_children++;
+            }
+        }
+
+        /* Allow each child which actually finished to exit */
+        ap_relieve_child_processes();
+
+        /* cleanup pid file */
+        {
+            const char *pidfile = NULL;
+            pidfile = ap_server_root_relative (pconf, ap_pid_fname);
+            if ( pidfile != NULL && unlink(pidfile) == 0)
+                ap_log_error(APLOG_MARK, APLOG_INFO,
+                                0, ap_server_conf,
+                                "removed PID file %s (pid=%ld)",
+                                pidfile, (long)getpid());
+        }
+
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
+           "caught " AP_SIG_GRACEFUL_STOP_STRING ", shutting down gracefully");
+
+        if (ap_graceful_shutdown_timeout) {
+            cutoff = apr_time_now() +
+                     apr_time_from_sec(ap_graceful_shutdown_timeout);
+        }
+
+        /* Don't really exit until each child has finished */
+        shutdown_pending = 0;
+        do {
+            /* Pause for a second */
+            sleep(1);
+
+            /* Relieve any children which have now exited */
+            ap_relieve_child_processes();
+
+            active_children = 0;
+            for (index = 0; index < ap_daemons_limit; ++index) {
+                if (MPM_CHILD_PID(index) != 0) {
+                    if (kill(MPM_CHILD_PID(index), 0) == 0) {
+                            active_children = 1;
+                            /* Having just one child is enough to stay around */
+                            break;
+                    }
+                }
+            }
+        } while (!shutdown_pending && active_children &&
+                 (!ap_graceful_shutdown_timeout || apr_time_now() < cutoff));
+
+        /* We might be here because we received SIGTERM, either
+         * way, try and make sure that all of our processes are
+         * really dead.
+         */
+        unixd_killpg(getpgrp(), SIGTERM);
+
 	return 1;
     }
 
     /* we've been told to restart */
     apr_signal(SIGHUP, SIG_IGN);
+    apr_signal(AP_SIG_GRACEFUL, SIG_IGN);
     if (one_process) {
 	/* not worth thinking about */
 	return 1;
     }
 
     /* advance to the next generation */
     /* XXX: we really need to make sure this new generation number isn't in
      * use by any of the children.
      */
     ++ap_my_generation;
     ap_scoreboard_image->global->running_generation = ap_my_generation;
-    
+
     if (is_graceful) {
 	ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
 		    "Graceful restart requested, doing restart");
 
 	/* kill off the idle ones */
         ap_mpm_pod_killpg(pod, ap_max_daemons_limit);
 
 	/* This is mostly for debugging... so that we know what is still
-	    * gracefully dealing with existing request.  This will break
-	    * in a very nasty way if we ever have the scoreboard totally
-	    * file-based (no shared memory)
-	    */
+         * gracefully dealing with existing request.  This will break
+         * in a very nasty way if we ever have the scoreboard totally
+         * file-based (no shared memory)
+         */
 	for (index = 0; index < ap_daemons_limit; ++index) {
 	    if (ap_scoreboard_image->servers[index][0].status != SERVER_DEAD) {
 		ap_scoreboard_image->servers[index][0].status = SERVER_GRACEFUL;
+                /* Ask each child to close its listeners.
+                 *
+                 * NOTE: we use the scoreboard, because if we send SIGUSR1
+                 * to every process in the group, this may include CGI's,
+                 * piped loggers, etc. They almost certainly won't handle
+                 * it gracefully.
+                 */
+                kill(ap_scoreboard_image->parent[index].pid, AP_SIG_GRACEFUL);
 	    }
 	}
     }
     else {
 	/* Kill 'em off */
 	if (unixd_killpg(getpgrp(), SIGHUP) < 0) {
