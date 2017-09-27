             apr_socket_timeout_set(cin->socket, saved_timeout);
         }
     }
     
     switch (status) {
         case APR_SUCCESS:
-            status = consume_brigade(cin, cin->bb, block);
+            status = recv_RAW_brigade(f->c, cin, cin->bb, block);
             break;
         case APR_EOF:
         case APR_EAGAIN:
         case APR_TIMEUP:
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
-                          "core_input(%ld): read", (long)f->c->id);
+            if (trace1) {
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
+                              "h2_session(%ld): read", f->c->id);
+            }
             break;
         default:
             ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, f->c, APLOGNO(03046)
-                          "h2_conn_io: error reading");
+                          "h2_session(%ld): error reading", f->c->id);
             break;
     }
     return status;
 }
 
 /*******************************************************************************
