             }
             break;
 
         case HSE_STATUS_ERROR:
             /* end response if we have yet to do so.
              */
+            ap_log_rerror(APLOG_MARK, APLOG_WARNING, apr_get_os_error(), r,
+                          "ISAPI: HSE_STATUS_ERROR result from "
+                          "HttpExtensionProc(): %s", r->filename);
             r->status = HTTP_INTERNAL_SERVER_ERROR;
             break;
 
         default:
-            /* TODO: log unrecognized retval for debugging
-             */
-             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
-                           "ISAPI: return code %d from HttpExtensionProc() "
-                           "was not not recognized", rv);
+            ap_log_rerror(APLOG_MARK, APLOG_WARNING, apr_get_os_error(), r,
+                          "ISAPI: unrecognized result code %d "
+                          "from HttpExtensionProc(): %s ", 
+                          rv, r->filename);
             r->status = HTTP_INTERNAL_SERVER_ERROR;
             break;
     }
 
     /* Flush the response now, including headers-only responses */
-    if (cid->headers_set) {
+    if (cid->headers_set || cid->response_sent) {
         conn_rec *c = r->connection;
         apr_bucket_brigade *bb;
         apr_bucket *b;
         apr_status_t rv;
 
         bb = apr_brigade_create(r->pool, c->bucket_alloc);
         b = apr_bucket_eos_create(c->bucket_alloc);
         APR_BRIGADE_INSERT_TAIL(bb, b);
-        b = apr_bucket_flush_create(c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(bb, b);
         rv = ap_pass_brigade(r->output_filters, bb);
         cid->response_sent = 1;
 
-        return OK;  /* NOT r->status or cid->r->status, even if it has changed. */
+        if (rv != APR_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
+                          "ISAPI: ap_pass_brigade failed to "
+                          "complete the response: %s ", r->filename);
+        }
+
+        return OK; /* NOT r->status, even if it has changed. */
     }
 
     /* As the client returned no error, and if we did not error out
      * ourselves, trust dwHttpStatusCode to say something relevant.
      */
     if (!ap_is_HTTP_SERVER_ERROR(r->status) && cid->ecb->dwHttpStatusCode) {
         r->status = cid->ecb->dwHttpStatusCode;
     }
 
-    /* For all missing-response situations simply return the status.
-     * and let the core deal respond to the client.
+    /* For all missing-response situations simply return the status,
+     * and let the core respond to the client.
      */
     return r->status;
 }
 
 /**********************************************************
  *
