              * ... so we were pat all this time
              */
             break;
 
         case HSE_STATUS_PENDING:
             /* emulating async behavior...
-             *
-             * Create a cid->completed mutex and wait on it for some timeout
-             * so that the app thinks is it running async.
-             *
-             * All async ServerSupportFunction calls will be handled through
-             * the registered IO_COMPLETION hook.
-             *
-             * This request completes upon a notification through
-             * ServerSupportFunction(HSE_REQ_DONE_WITH_SESSION)
              */
-            if (cid->dconf.fake_async) {
-                apr_thread_mutex_t *comp;
-
-                rv = apr_thread_mutex_create(&cid->completed, 
-                                             APR_THREAD_MUTEX_UNNESTED, 
-                                             r->pool);
-                comp = cid->completed;
-                if (cid->completed && (rv == APR_SUCCESS)) {
-                    rv = apr_thread_mutex_lock(comp);
-                }
-                /* The completion port is now locked.  When we regain the
-                 * lock, we may destroy the request.
+            if (cid->completed) {
+                /* The completion port was locked prior to invoking
+                 * HttpExtensionProc().  Once we can regain the lock,
+                 * when ServerSupportFunction(HSE_REQ_DONE_WITH_SESSION)
+                 * is called by the extension to release the lock,
+                 * we may finally destroy the request.
                  */
-                if (cid->completed && (rv == APR_SUCCESS)) {
-                    rv = apr_thread_mutex_lock(comp);
-                }
+                (void)apr_thread_mutex_lock(cid->completed);
                 break;
             }
             else if (cid->dconf.log_unsupported) {
                  ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                                "ISAPI: asynch I/O result HSE_STATUS_PENDING "
                                "from HttpExtensionProc() is not supported: %s",
                                r->filename);
-                 cid->r->status = HTTP_INTERNAL_SERVER_ERROR;
+                 r->status = HTTP_INTERNAL_SERVER_ERROR;
             }
             break;
 
         case HSE_STATUS_ERROR:    
             /* end response if we have yet to do so.
              */
-            cid->r->status = HTTP_INTERNAL_SERVER_ERROR;
+            r->status = HTTP_INTERNAL_SERVER_ERROR;
             break;
 
         default:
             /* TODO: log unrecognized retval for debugging 
              */
-            cid->r->status = HTTP_INTERNAL_SERVER_ERROR;
+             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+                           "ISAPI: return code %d from HttpExtensionProc() "
+                           "was not not recognized", rv);
+            r->status = HTTP_INTERNAL_SERVER_ERROR;
             break;
     }
 
-    /* Set the status (for logging) */
-    if (cid->ecb->dwHttpStatusCode) {
-        cid->r->status = cid->ecb->dwHttpStatusCode;
+    /* Flush the response now, including headers-only responses */
+    if (cid->headers_set) {
+        conn_rec *c = r->connection;
+        apr_bucket_brigade *bb;
+        apr_bucket *b;
+        apr_status_t rv;
+
+        bb = apr_brigade_create(r->pool, c->bucket_alloc);
+        b = apr_bucket_eos_create(c->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(bb, b);
+        rv = ap_pass_brigade(r->output_filters, bb);
+        cid->response_sent = 1;
+
+        return OK;  /* NOT r->status or cid->r->status, even if it has changed. */
+    }
+    
+    /* As the client returned no error, and if we did not error out
+     * ourselves, trust dwHttpStatusCode to say something relevant.
+     */
+    if (!ap_is_HTTP_SERVER_ERROR(r->status) && cid->ecb->dwHttpStatusCode) {
+        r->status = cid->ecb->dwHttpStatusCode;
     }
 
-    return cid->r->status;
+    /* For all missing-response situations simply return the status.
+     * and let the core deal respond to the client.
+     */
+    return r->status;
 }
 
 /**********************************************************
  *
  *  ISAPI Module Setup Hooks
  *
