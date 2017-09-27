     if (threads_created) {
         ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00363)
                      "Child: Terminating %d threads that failed to exit.",
                      threads_created);
     }
     for (i = 0; i < threads_created; i++) {
-        int *score_idx;
+        int *idx;
         TerminateThread(child_handles[i], 1);
         CloseHandle(child_handles[i]);
         /* Reset the scoreboard entry for the thread we just whacked */
-        score_idx = apr_hash_get(ht, &child_handles[i], sizeof(HANDLE));
-        if (score_idx) {
-            ap_update_child_status_from_indexes(0, *score_idx, SERVER_DEAD, NULL);
+        idx = apr_hash_get(ht, &child_handles[i], sizeof(HANDLE));
+        if (idx) {
+            ap_update_child_status_from_indexes(0, *idx, SERVER_DEAD, NULL);
         }
     }
     ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00364)
                  "Child: All worker threads have exited.");
 
     apr_thread_mutex_destroy(child_lock);
