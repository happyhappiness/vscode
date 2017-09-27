         APR_BRIGADE_INSERT_TAIL(header_brigade, e);
     }
 
     /* send the request body, if any. */
     switch(rb_method) {
     case RB_STREAM_CHUNKED:
-        status = stream_reqbody_chunked(p, r, p_conn, origin, header_brigade,
+        rv = stream_reqbody_chunked(p, r, p_conn, origin, header_brigade,
                                         input_brigade);
         break;
     case RB_STREAM_CL:
-        status = stream_reqbody_cl(p, r, p_conn, origin, header_brigade,
+        rv = stream_reqbody_cl(p, r, p_conn, origin, header_brigade,
                                    input_brigade, old_cl_val);
         break;
     case RB_SPOOL_CL:
-        status = spool_reqbody_cl(p, r, p_conn, origin, header_brigade,
+        rv = spool_reqbody_cl(p, r, p_conn, origin, header_brigade,
                                   input_brigade, (old_cl_val != NULL)
                                               || (old_te_val != NULL)
                                               || (bytes_read > 0));
         break;
     default:
         /* shouldn't be possible */
-        status = APR_EINVAL;
+        rv = HTTP_INTERNAL_SERVER_ERROR ;
         break;
     }
 
-    if (status != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
+    if (rv != OK) {
+        /* apr_errno value has been logged in lower level method */
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                      "proxy: pass request body failed to %pI (%s)"
                      " from %s (%s)",
                      p_conn->addr,
                      p_conn->hostname ? p_conn->hostname: "",
                      c->remote_ip,
                      c->remote_host ? c->remote_host: "");
-        return status;
+        return rv;
     }
 
-    return APR_SUCCESS;
+    return OK;
 }
 
 static void process_proxy_header(request_rec* r, proxy_dir_conf* c,
                       const char* key, const char* value)
 {
     static const char* date_hdrs[]
