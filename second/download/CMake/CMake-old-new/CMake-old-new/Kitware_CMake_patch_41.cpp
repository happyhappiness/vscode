@@ -6,7 +6,7 @@
  *                             \___|\___/|_| \_\_____|
  *
  * Copyright (C) 2010, DirecTV, Contact: Eric Hu, <ehu@directv.com>.
- * Copyright (C) 2010 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 2010 - 2017, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -156,6 +156,12 @@ static CURLcode connect_prep(struct connectdata *conn, int sockindex)
        same connection */
     return CURLE_OK;
 
+  if(SSL_CONN_CONFIG(version_max) != CURL_SSLVERSION_MAX_NONE) {
+    failf(data, "axtls does not support CURL_SSLVERSION_MAX");
+    return CURLE_SSL_CONNECT_ERROR;
+  }
+
+
   /* axTLS only supports TLSv1 */
   /* check to see if we've been told to use an explicit SSL/TLS version */
   switch(SSL_CONN_CONFIG(version)) {
@@ -256,7 +262,7 @@ static CURLcode connect_prep(struct connectdata *conn, int sockindex)
    * 2) setting up callbacks.  these seem gnutls specific
    */
 
-  if(data->set.general_ssl.sessionid) {
+  if(SSL_SET_OPTION(primary.sessionid)) {
     const uint8_t *ssl_sessionid;
     size_t ssl_idsize;
 
@@ -267,13 +273,13 @@ static CURLcode connect_prep(struct connectdata *conn, int sockindex)
       /* we got a session id, use it! */
       infof(data, "SSL re-using session ID\n");
       ssl = ssl_client_new(ssl_ctx, conn->sock[sockindex],
-                           ssl_sessionid, (uint8_t)ssl_idsize);
+                           ssl_sessionid, (uint8_t)ssl_idsize, NULL);
     }
     Curl_ssl_sessionid_unlock(conn);
   }
 
   if(!ssl)
-    ssl = ssl_client_new(ssl_ctx, conn->sock[sockindex], NULL, 0);
+    ssl = ssl_client_new(ssl_ctx, conn->sock[sockindex], NULL, 0, NULL);
 
   conn->ssl[sockindex].ssl = ssl;
   return CURLE_OK;
@@ -386,9 +392,9 @@ static CURLcode connect_finish(struct connectdata *conn, int sockindex)
   conn->send[sockindex] = axtls_send;
 
   /* Put our freshly minted SSL session in cache */
-  if(data->set.general_ssl.sessionid) {
-    const uint8_t *ssl_sessionid = ssl_get_session_id_size(ssl);
-    size_t ssl_idsize = ssl_get_session_id(ssl);
+  if(SSL_SET_OPTION(primary.sessionid)) {
+    const uint8_t *ssl_sessionid = ssl_get_session_id(ssl);
+    size_t ssl_idsize = ssl_get_session_id_size(ssl);
     Curl_ssl_sessionid_lock(conn);
     if(Curl_ssl_addsessionid(conn, (void *) ssl_sessionid, ssl_idsize,
                              sockindex) != CURLE_OK)
@@ -680,9 +686,9 @@ size_t Curl_axtls_version(char *buffer, size_t size)
   return snprintf(buffer, size, "axTLS/%s", ssl_version());
 }
 
-int Curl_axtls_random(struct Curl_easy *data,
-                      unsigned char *entropy,
-                      size_t length)
+CURLcode Curl_axtls_random(struct Curl_easy *data,
+                           unsigned char *entropy,
+                           size_t length)
 {
   static bool ssl_seeded = FALSE;
   (void)data;
@@ -694,7 +700,7 @@ int Curl_axtls_random(struct Curl_easy *data,
     RNG_initialize();
   }
   get_random((int)length, entropy);
-  return 0;
+  return CURLE_OK;
 }
 
 #endif /* USE_AXTLS */