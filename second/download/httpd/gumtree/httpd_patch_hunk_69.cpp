     else {
         cid->ecb->cbTotalBytes = 0;
         cid->ecb->cbAvailable = 0;
         cid->ecb->lpbData = NULL;
     }
 
+    /* To emulate async behavior...
+     *
+     * We create a cid->completed mutex and lock on it so that the
+     * app can believe is it running async.
+     *
+     * This request completes upon a notification through
+     * ServerSupportFunction(HSE_REQ_DONE_WITH_SESSION), which
+     * unlocks this mutex.  If the HttpExtensionProc() returns
+     * HSE_STATUS_PENDING, we will attempt to gain this lock again
+     * which may *only* happen once HSE_REQ_DONE_WITH_SESSION has
+     * unlocked the mutex.
+     */
+    if (cid->dconf.fake_async) {
+        rv = apr_thread_mutex_create(&cid->completed, 
+                                     APR_THREAD_MUTEX_UNNESTED, 
+                                     r->pool);
+        if (cid->completed && (rv == APR_SUCCESS)) {
+            rv = apr_thread_mutex_lock(cid->completed);
+        }
+
+        if (!cid->completed || (rv != APR_SUCCESS)) {
+            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+                          "ISAPI: Failed to create completion mutex");
+            return HTTP_INTERNAL_SERVER_ERROR;
+        }
+    }
+
     /* All right... try and run the sucker */
     rv = (*isa->HttpExtensionProc)(cid->ecb);
 
     /* Check for a log message - and log it */
     if (cid->ecb->lpszLogData && *cid->ecb->lpszLogData)
         ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
