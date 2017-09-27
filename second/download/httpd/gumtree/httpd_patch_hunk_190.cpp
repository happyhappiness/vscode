             }
 
             /* Check the listen queue on all sockets for requests */
             memcpy(&main_fds, &listenfds, sizeof(fd_set));
             srv = select(listenmaxfd + 1, &main_fds, NULL, NULL, &tv);
 
-            if (srv <= 0)
+            if (srv <= 0) {
+                if (srv < 0) {
+                    ap_log_error(APLOG_MARK, APLOG_NOTICE, apr_get_netos_error(), ap_server_conf,
+                        "select() failed on listen socket");
+                    apr_thread_yield();
+                }
                 continue;
+            }
 
             /* remember the last_lr we searched last time around so that
             we don't end up starving any particular listening socket */
             if (last_lr == NULL) {
                 lr = ap_listeners;
             }
