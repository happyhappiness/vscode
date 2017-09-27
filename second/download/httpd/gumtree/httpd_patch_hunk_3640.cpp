                 status = APR_SUCCESS;
             }
             else {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00950)
                              "send_http_connect: the forward proxy returned code is '%s'",
                              code_str);
-            status = APR_INCOMPLETE;
+                status = APR_INCOMPLETE;
             }
         }
     }
 
     return(status);
 }
 
 
 #if APR_HAVE_SYS_UN_H
-/* lifted from mod_proxy_fdpass.c; tweaked addrlen in connect() call */
-static apr_status_t socket_connect_un(apr_socket_t *sock,
-                                      struct sockaddr_un *sa)
+/* TODO: In APR 2.x: Extend apr_sockaddr_t to possibly be a path !!! */
+PROXY_DECLARE(apr_status_t) ap_proxy_connect_uds(apr_socket_t *sock,
+                                                 const char *uds_path,
+                                                 apr_pool_t *p)
 {
     apr_status_t rv;
     apr_os_sock_t rawsock;
     apr_interval_time_t t;
+    struct sockaddr_un *sa;
+    apr_socklen_t addrlen, pathlen;
 
     rv = apr_os_sock_get(&rawsock, sock);
     if (rv != APR_SUCCESS) {
         return rv;
     }
 
     rv = apr_socket_timeout_get(sock, &t);
     if (rv != APR_SUCCESS) {
         return rv;
     }
 
+    pathlen = strlen(uds_path);
+    /* copy the UDS path (including NUL) to the sockaddr_un */
+    addrlen = APR_OFFSETOF(struct sockaddr_un, sun_path) + pathlen;
+    sa = (struct sockaddr_un *)apr_palloc(p, addrlen + 1);
+    memcpy(sa->sun_path, uds_path, pathlen + 1);
+    sa->sun_family = AF_UNIX;
+
     do {
-        const socklen_t addrlen = APR_OFFSETOF(struct sockaddr_un, sun_path)
-                                  + strlen(sa->sun_path) + 1;
         rv = connect(rawsock, (struct sockaddr*)sa, addrlen);
-    } while (rv == -1 && errno == EINTR);
+    } while (rv == -1 && (rv = errno) == EINTR);
 
-    if ((rv == -1) && (errno == EINPROGRESS || errno == EALREADY)
-        && (t > 0)) {
+    if (rv && rv != EISCONN) {
+        if ((rv == EINPROGRESS || rv == EALREADY) && (t > 0))  {
 #if APR_MAJOR_VERSION < 2
-        rv = apr_wait_for_io_or_timeout(NULL, sock, 0);
+            rv = apr_wait_for_io_or_timeout(NULL, sock, 0);
 #else
-        rv = apr_socket_wait(sock, APR_WAIT_WRITE);
+            rv = apr_socket_wait(sock, APR_WAIT_WRITE);
 #endif
-
+        }
         if (rv != APR_SUCCESS) {
             return rv;
         }
     }
 
-    if (rv == -1 && errno != EISCONN) {
-        return errno;
-    }
-
     return APR_SUCCESS;
 }
 #endif
 
 PROXY_DECLARE(int) ap_proxy_connect_backend(const char *proxy_function,
                                             proxy_conn_rec *conn,
