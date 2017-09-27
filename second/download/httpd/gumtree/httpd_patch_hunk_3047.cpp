      * their decoding from the headers_in T-E list.
      * XXX: Make this extensible, but in doing so, presume the
      * encoding has been done by the extensions' handler, and
      * do not modify add_te_chunked's logic
      */
     if (old_te_val && strcasecmp(old_te_val, "chunked") != 0) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                     "proxy: %s Transfer-Encoding is not supported",
-                     old_te_val);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01093)
+                      "%s Transfer-Encoding is not supported", old_te_val);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     if (old_cl_val && old_te_val) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_ENOTIMPL, r->server,
-                     "proxy: client %s (%s) requested Transfer-Encoding "
-                     "chunked body with Content-Length (C-L ignored)",
-                     c->remote_ip, c->remote_host ? c->remote_host: "");
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01094)
+                      "client %s (%s) requested Transfer-Encoding "
+                      "chunked body with Content-Length (C-L ignored)",
+                      c->client_ip, c->remote_host ? c->remote_host: "");
         apr_table_unset(r->headers_in, "Content-Length");
         old_cl_val = NULL;
         origin->keepalive = AP_CONN_CLOSE;
         p_conn->close++;
     }
 
