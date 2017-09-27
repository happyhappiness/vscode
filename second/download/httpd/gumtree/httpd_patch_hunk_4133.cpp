                                             OCSP_REQUEST *request,
                                             conn_rec *c, apr_pool_t *p)
 {
     OCSP_RESPONSE *response = NULL;
     apr_socket_t *sd;
     BIO *bio;
+    const apr_uri_t *proxy_uri;
 
-    bio = serialize_request(request, uri);
+    proxy_uri = (mySrvConfigFromConn(c))->server->proxy_uri;
+    bio = serialize_request(request, uri, proxy_uri);
     if (bio == NULL) {
         ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01989)
                       "could not serialize OCSP request");
         ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, mySrvFromConn(c));
         return NULL;
     }
 
-    sd = send_request(bio, uri, timeout, c, p);
+    sd = send_request(bio, uri, timeout, c, p, proxy_uri);
     if (sd == NULL) {
         /* Errors already logged. */
         BIO_free(bio);
         return NULL;
     }
 
