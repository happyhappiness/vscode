     return bio;
 }
 
 /* Send the OCSP request serialized into BIO 'request' to the
  * responder at given server given by URI.  Returns socket object or
  * NULL on error. */
-static apr_socket_t *send_request(BIO *request, const apr_uri_t *uri, 
+static apr_socket_t *send_request(BIO *request, const apr_uri_t *uri,
                                   apr_interval_time_t timeout,
                                   conn_rec *c, apr_pool_t *p)
 {
     apr_status_t rv;
     apr_sockaddr_t *sa;
     apr_socket_t *sd;
     char buf[HUGE_STRING_LEN];
     int len;
 
     rv = apr_sockaddr_info_get(&sa, uri->hostname, APR_UNSPEC, uri->port, 0, p);
     if (rv) {
-        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
-                      "could not resolve address of OCSP responder %s", 
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01972)
+                      "could not resolve address of OCSP responder %s",
                       uri->hostinfo);
         return NULL;
     }
-    
-    /* establish a connection to the OCSP responder */ 
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
+
+    /* establish a connection to the OCSP responder */
+    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01973)
                   "connecting to OCSP responder '%s'", uri->hostinfo);
 
     /* Cycle through address until a connect() succeeds. */
     for (; sa; sa = sa->next) {
         rv = apr_socket_create(&sd, sa->family, SOCK_STREAM, APR_PROTO_TCP, p);
         if (rv == APR_SUCCESS) {
