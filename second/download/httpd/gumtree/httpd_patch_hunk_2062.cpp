     /* If we have added something to the brigade above, sent it */
     if (!APR_BRIGADE_EMPTY(output_brigade))
         ap_pass_brigade(r->output_filters, output_brigade);
 
     apr_brigade_destroy(output_brigade);
 
-    if (rv)
-        return rv;
-
-    /* Nice we have answer to send to the client */
-    if (result == CMD_AJP13_END_RESPONSE && isok) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                     "proxy: got response from %pI (%s)",
-                     conn->worker->cp->addr,
-                     conn->worker->hostname);
-        return OK;
-    }
-
-    ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
-                 "proxy: got bad response (%d) from %pI (%s)",
-                 result,
-                 conn->worker->cp->addr,
-                 conn->worker->hostname);
-
-    /* We had a failure: Close connection to backend */
-    conn->close++;
-    return HTTP_SERVICE_UNAVAILABLE;
+    return rv;
 }
 
 /*
  * This handles ajp:// URLs
  */
 static int proxy_ajp_handler(request_rec *r, proxy_worker *worker,
