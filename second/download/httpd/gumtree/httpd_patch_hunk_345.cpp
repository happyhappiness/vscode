     else {
         ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf, 
                      "Child %d: Failure releasing the start mutex", my_pid);
     }
 
     /* Shutdown the worker threads */
-    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
+    if (!use_acceptex) {
         for (i = 0; i < threads_created; i++) {
             add_job(INVALID_SOCKET);
         }
     }
     else { /* Windows NT/2000 */
         /* Post worker threads blocked on the ThreadDispatch IOCompletion port */
