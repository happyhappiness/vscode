              */
             retained->sick_child_detected = 0;
         }
         else {
             /* looks like a basket case, as no child ever fully initialized; give up.
              */
-            shutdown_pending = 1;
+            retained->mpm->shutdown_pending = 1;
             child_fatal = 1;
             ap_log_error(APLOG_MARK, APLOG_ALERT, 0,
                          ap_server_conf, APLOGNO(02325)
                          "A resource shortage or other unrecoverable failure "
                          "was encountered before any child process initialized "
                          "successfully... httpd is exiting!");
