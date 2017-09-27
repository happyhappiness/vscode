             closesocket(qhead->accept_socket);
             qhead = qhead->next;
         }
         apr_thread_mutex_unlock(qlock);
     }
 
-    /* Give busy worker threads a chance to service their connections */
-    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
-                 "Child %d: Waiting for %d worker threads to exit.", my_pid, threads_created);
-    end_time = time(NULL) + 180;
-    while (threads_created) {
-        rv = wait_for_many_objects(threads_created, child_handles, (DWORD)(end_time - time(NULL)));
-        if (rv != WAIT_TIMEOUT) {
-            rv = rv - WAIT_OBJECT_0;
-            ap_assert((rv >= 0) && (rv < threads_created));
-            cleanup_thread(child_handles, &threads_created, rv);
+    /* Give busy threads a chance to service their connections,
+     * (no more than the global server timeout period which 
+     * we track in msec remaining).
+     */
+    watch_thread = 0;
+    time_remains = (int)(ap_server_conf->timeout / APR_TIME_C(1000));
+
+    while (threads_created)
+    {
+        int nFailsafe = MAXIMUM_WAIT_OBJECTS;
+        DWORD dwRet;
+
+        /* Every time we roll over to wait on the first group
+         * of MAXIMUM_WAIT_OBJECTS threads, take a breather,
+         * and infrequently update the error log.
+         */
+        if (watch_thread >= threads_created) {
+            if ((time_remains -= 100) < 0)
+                break;
+
+            /* Every 30 seconds give an update */
+            if ((time_remains % 30000) == 0) {
+                ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, 
+                             ap_server_conf,
+                             "Child %d: Waiting %d more seconds "
+                             "for %d worker threads to finish.", 
+                             my_pid, time_remains / 1000, threads_created);
+            }
+            /* We'll poll from the top, 10 times per second */
+            Sleep(100);
+            watch_thread = 0;
+        }
+
+        /* Fairness, on each iteration we will pick up with the thread
+         * after the one we just removed, even if it's a single thread.
+         * We don't block here.
+         */
+        dwRet = WaitForMultipleObjects(min(threads_created - watch_thread,
+                                           MAXIMUM_WAIT_OBJECTS),
+                                       child_handles + watch_thread, 0, 0);
+
+        if (dwRet == WAIT_FAILED) {
+            break;
+        }
+        if (dwRet == WAIT_TIMEOUT) {
+            /* none ready */
+            watch_thread += MAXIMUM_WAIT_OBJECTS;
             continue;
         }
-        break;
+        else if (dwRet >= WAIT_ABANDONED_0) {
+            /* We just got the ownership of the object, which
+             * should happen at most MAXIMUM_WAIT_OBJECTS times.
+             * It does NOT mean that the object is signaled.
+             */
+            if ((nFailsafe--) < 1)
+                break;
+        }
+        else {
+            watch_thread += (dwRet - WAIT_OBJECT_0);
+            if (watch_thread >= threads_created)
+                break;
+            cleanup_thread(child_handles, &threads_created, watch_thread);
+        }
     }
-
+ 
     /* Kill remaining threads off the hard way */
     if (threads_created) {
         ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                      "Child %d: Terminating %d threads that failed to exit.",
                      my_pid, threads_created);
     }
     for (i = 0; i < threads_created; i++) {
         int *score_idx;
         TerminateThread(child_handles[i], 1);
         CloseHandle(child_handles[i]);
         /* Reset the scoreboard entry for the thread we just whacked */
         score_idx = apr_hash_get(ht, &child_handles[i], sizeof(HANDLE));
-        ap_update_child_status_from_indexes(0, *score_idx, SERVER_DEAD, NULL);
+        if (score_idx) {
+            ap_update_child_status_from_indexes(0, *score_idx,
+                                                SERVER_DEAD, NULL);
+        }
     }
     ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                  "Child %d: All worker threads have exited.", my_pid);
 
     CloseHandle(allowed_globals.jobsemaphore);
     apr_thread_mutex_destroy(allowed_globals.jobmutex);
