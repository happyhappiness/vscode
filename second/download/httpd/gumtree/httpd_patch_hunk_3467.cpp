         /* gave it our best shot, but alas...  If this really
          * is a child we are trying to kill and it really hasn't
          * exited, we will likely fail to bind to the port
          * after the restart.
          */
         ap_log_error(APLOG_MARK, APLOG_ERR,
-                     0, ap_server_conf,
+                     0, ap_server_conf, APLOGNO(00047)
                      "could not make child process %" APR_PID_T_FMT
                      " exit, "
                      "attempting to continue anyway",
                      pid);
         break;
     }
 
     return 0;
 }
 
-void ap_reclaim_child_processes(int terminate)
+void ap_reclaim_child_processes(int terminate,
+                                ap_reclaim_callback_fn_t *mpm_callback)
 {
     apr_time_t waittime = 1024 * 16;
     int i;
     extra_process_t *cur_extra;
     int not_dead_yet;
     int max_daemons;
