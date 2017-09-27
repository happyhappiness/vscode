                              proxy_function,
                              worker->s->hostname);
                 break;
             }
             conn->connection = NULL;
 
-            sa.sun_family = AF_UNIX;
-            apr_cpystrn(sa.sun_path, conn->uds_path, sizeof(sa.sun_path));
-
-            rv = socket_connect_un(newsock, &sa);
+            rv = ap_proxy_connect_uds(newsock, conn->uds_path, conn->scpool);
             if (rv != APR_SUCCESS) {
                 apr_socket_close(newsock);
                 ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(02454)
                              "%s: attempt to connect to Unix domain socket "
                              "%s (%s) failed",
                              proxy_function,
                              conn->uds_path,
                              worker->s->hostname);
                 break;
             }
+
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02823)
+                         "%s: connection established with Unix domain socket "
+                         "%s (%s)",
+                         proxy_function,
+                         conn->uds_path,
+                         worker->s->hostname);
         }
         else
 #endif
         {
             if ((rv = apr_socket_create(&newsock, backend_addr->family,
                                         SOCK_STREAM, APR_PROTO_TCP,
