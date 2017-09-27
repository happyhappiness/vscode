         apr_table_get(tbl, "busy") != NULL &&
         apr_table_get(tbl, "ready") != NULL) {
         char *ip;
         int port = 80;
         hm_server_t *s;
         /* TODO: REMOVE ME BEFORE PRODUCTION (????) */
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s,
-                     "Heartmonitor: %pI busy=%s ready=%s", from,
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(02086)
+                     "%pI busy=%s ready=%s", from,
                      apr_table_get(tbl, "busy"), apr_table_get(tbl, "ready"));
 
         apr_sockaddr_ip_get(&ip, from);
 
         if (apr_table_get(tbl, "port") != NULL)
             port = atoi(apr_table_get(tbl, "port"));
-           
+
         s = hm_get_server(ctx, ip, port);
 
         s->busy = atoi(apr_table_get(tbl, "busy"));
         s->ready = atoi(apr_table_get(tbl, "ready"));
         s->seen = apr_time_now();
     }
     else {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ctx->s,
-                     "Heartmonitor: malformed message from %pI",
+        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ctx->s, APLOGNO(02087)
+                     "malformed message from %pI",
                      from);
     }
 
 }
 /* Read message from multicast socket */
 #define MAX_MSG_LEN (1000)
