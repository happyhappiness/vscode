     apr_bucket *e;
     char *old_cl_val = NULL;
     char *old_te_val = NULL;
     apr_bucket_brigade *bb = apr_brigade_create(p, c->bucket_alloc);
     apr_socket_t *client_socket = ap_get_conn_socket(c);
     int done = 0, replied = 0;
+    const char *upgrade_method = *worker->s->upgrade ? worker->s->upgrade : "WebSocket";
 
     header_brigade = apr_brigade_create(p, backconn->bucket_alloc);
 
     ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "sending request");
 
     rv = ap_proxy_create_hdrbrgd(p, header_brigade, r, conn,
                                  worker, conf, uri, url, server_portstr,
                                  &old_cl_val, &old_te_val);
     if (rv != OK) {
         return rv;
     }
 
-    buf = apr_pstrdup(p, "Upgrade: WebSocket" CRLF "Connection: Upgrade" CRLF CRLF);
+    if (ap_cstr_casecmp(upgrade_method, "NONE") == 0) {
+        buf = apr_pstrdup(p, "Upgrade: WebSocket" CRLF "Connection: Upgrade" CRLF CRLF);
+    } else {
+        buf = apr_pstrcat(p, "Upgrade: ", upgrade_method, CRLF "Connection: Upgrade" CRLF CRLF, NULL);
+    }
     ap_xlate_proto_to_ascii(buf, strlen(buf));
     e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(header_brigade, e);
 
     if ((rv = ap_proxy_pass_brigade(backconn->bucket_alloc, r, conn, backconn,
                                     header_brigade, 1)) != OK)
