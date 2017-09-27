 static int proxy_connect_canon(request_rec *r, char *url)
 {
 
     if (r->method_number != M_CONNECT) {
     return DECLINED;
     }
-    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
-                 "proxy: CONNECT: canonicalising URL %s", url);
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "canonicalising URL %s", url);
 
     return OK;
 }
 
 /* read available data (in blocks of CONN_BLKSZ) from c_i and copy to c_o */
 static int proxy_connect_transfer(request_rec *r, conn_rec *c_i, conn_rec *c_o,
