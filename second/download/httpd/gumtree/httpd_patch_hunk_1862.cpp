             watch_thread += (dwRet - WAIT_OBJECT_0);
             if (watch_thread >= threads_created)
                 break;
             cleanup_thread(child_handles, &threads_created, watch_thread);
         }
     }
- 
+
     /* Kill remaining threads off the hard way */
     if (threads_created) {
-        ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                     "Child %lu: Terminating %d threads that failed to exit.",
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
+                     "Child %d: Terminating %d threads that failed to exit.",
                      my_pid, threads_created);
     }
     for (i = 0; i < threads_created; i++) {
         int *score_idx;
         TerminateThread(child_handles[i], 1);
         CloseHandle(child_handles[i]);
         /* Reset the scoreboard entry for the thread we just whacked */
         score_idx = apr_hash_get(ht, &child_handles[i], sizeof(HANDLE));
         if (score_idx) {
-            ap_update_child_status_from_indexes(0, *score_idx,
-                                                SERVER_DEAD, NULL);
+            ap_update_child_status_from_indexes(0, *score_idx, SERVER_DEAD, NULL);
         }
     }
-    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                 "Child %lu: All worker threads have exited.", my_pid);
+    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
+                 "Child %d: All worker threads have exited.", my_pid);
 
-    CloseHandle(allowed_globals.jobsemaphore);
-    apr_thread_mutex_destroy(allowed_globals.jobmutex);
     apr_thread_mutex_destroy(child_lock);
-
-    if (use_acceptex) {
-        apr_thread_mutex_destroy(qlock);
-        CloseHandle(qwait_event);
-    }
+    apr_thread_mutex_destroy(qlock);
+    CloseHandle(qwait_event);
 
     apr_pool_destroy(pchild);
     CloseHandle(exit_event);
 }
 
 #endif /* def WIN32 */
