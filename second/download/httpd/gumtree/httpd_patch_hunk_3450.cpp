          * children which will then bind to another CPU.
          */
         int status = bindprocessor(BINDPROCESS, (int)getpid(),
                                PROCESSOR_CLASS_ANY);
         if (status != OK)
             ap_log_error(APLOG_MARK, APLOG_DEBUG, errno,
-                         ap_server_conf,
+                         ap_server_conf, APLOGNO(00284)
                          "processor unbind failed");
 #endif
         RAISE_SIGSTOP(MAKE_CHILD);
 
         apr_signal(SIGTERM, just_die);
         child_main(slot);
-
-        clean_child_exit(0);
+        /* NOTREACHED */
     }
     /* else */
     if (ap_scoreboard_image->parent[slot].pid != 0) {
         /* This new child process is squatting on the scoreboard
          * entry owned by an exiting child process, which cannot
          * exit until all active requests complete.
-         * Don't forget about this exiting child process, or we
-         * won't be able to kill it if it doesn't exit by the
-         * time the server is shut down.
          */
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
-                     "taking over scoreboard slot from %" APR_PID_T_FMT "%s",
-                     ap_scoreboard_image->parent[slot].pid,
-                     ap_scoreboard_image->parent[slot].quiescing ?
-                         " (quiescing)" : "");
-        ap_register_extra_mpm_process(ap_scoreboard_image->parent[slot].pid);
+        worker_note_child_lost_slot(slot, pid);
     }
     ap_scoreboard_image->parent[slot].quiescing = 0;
-    ap_scoreboard_image->parent[slot].pid = pid;
+    worker_note_child_started(slot, pid);
     return 0;
 }
 
 /* start up a bunch of children */
 static void startup_children(int number_to_start)
 {
