     }
 
     /* We may have been in keep_alive_timeout mode, so toggle back
      * to the normal timeout mode as we fetch the header lines,
      * as necessary.
      */
-    csd = ap_get_module_config(conn->conn_config, &core_module);
+    csd = ap_get_conn_socket(conn);
     apr_socket_timeout_get(csd, &cur_timeout);
     if (cur_timeout != conn->base_server->timeout) {
         apr_socket_timeout_set(csd, conn->base_server->timeout);
         cur_timeout = conn->base_server->timeout;
     }
 
     if (!r->assbackwards) {
         ap_get_mime_headers_core(r, tmp_bb);
         if (r->status != HTTP_OK) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00567)
                           "request failed: error reading the headers");
             ap_send_error_response(r, 0);
             ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
             ap_run_log_transaction(r);
             apr_brigade_destroy(tmp_bb);
             goto traceout;
