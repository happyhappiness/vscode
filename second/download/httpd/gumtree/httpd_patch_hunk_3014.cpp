     if (strncasecmp(url, "fd://", 5) == 0) {
         url += 5;
     }
     else {
         return DECLINED;
     }
-    
+
     path = ap_server_root_relative(r->pool, url);
 
     r->filename = apr_pstrcat(r->pool, "proxy:fd://", path, NULL);
 
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                  "proxy: FD: set r->filename to %s", r->filename);
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01151)
+                  "set r->filename to %s", r->filename);
     return OK;
 }
 
 /* TODO: In APR 2.x: Extend apr_sockaddr_t to possibly be a path !!! */
 static apr_status_t socket_connect_un(apr_socket_t *sock,
                                       struct sockaddr_un *sa)
