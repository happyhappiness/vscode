     struct conn_rec *conn = r->connection;
     apr_bucket_brigade *bb;
     SSLConnRec *sslconn;
     apr_status_t rv;
     SSL *ssl;
 
-    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, 
+    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02028)
                   "upgrading connection to TLS");
 
     bb = apr_brigade_create(r->pool, conn->bucket_alloc);
 
     rv = ap_fputstrs(conn->output_filters, bb, SWITCH_STATUS_LINE, CRLF,
                      UPGRADE_HEADER, CRLF, CONNECTION_HEADER, CRLF, CRLF, NULL);
