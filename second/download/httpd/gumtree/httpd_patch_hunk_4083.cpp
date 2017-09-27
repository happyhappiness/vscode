             apr_table_set(r->headers_out, "Transfer-Encoding", "chunked");
             
             r->clength = 0;
             r->bytes_sent = 0;
             r->read_chunked = 0;
             ap_rflush(r);
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03012) 
                           "Websocket: Upgraded from HTTP to Websocket");
             lua_pushboolean(L, 1);
             return 1;
         }
     }
     ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02666)
