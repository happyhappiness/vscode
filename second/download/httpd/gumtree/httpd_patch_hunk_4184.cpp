             /* We let each thread update its own scoreboard entry.  This is
              * done because it lets us deal with tid better.
              */
             rv = apr_thread_create(&threads[i], thread_attr,
                                    worker_thread, my_info, pchild);
             if (rv != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
-                    "apr_thread_create: unable to create worker thread");
+                ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf, APLOGNO(03142)
+                             "apr_thread_create: unable to create worker thread");
                 /* let the parent decide how bad this really is */
                 clean_child_exit(APEXIT_CHILDSICK);
             }
             threads_created++;
         }
         /* Start the listener only when there are workers available */
