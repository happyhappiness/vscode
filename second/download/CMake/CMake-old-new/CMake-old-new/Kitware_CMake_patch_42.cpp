@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2017, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -134,6 +134,7 @@ cyassl_connect_step1(struct connectdata *conn,
                      int sockindex)
 {
   char error_buffer[CYASSL_MAX_ERROR_SZ];
+  char *ciphers;
   struct Curl_easy *data = conn->data;
   struct ssl_connect_data* conssl = &conn->ssl[sockindex];
   SSL_METHOD* req_method = NULL;
@@ -148,6 +149,11 @@ cyassl_connect_step1(struct connectdata *conn,
   if(conssl->state == ssl_connection_complete)
     return CURLE_OK;
 
+  if(SSL_CONN_CONFIG(version_max) != CURL_SSLVERSION_MAX_NONE) {
+    failf(data, "CyaSSL does not support to set maximum SSL/TLS version");
+    return CURLE_SSL_CONNECT_ERROR;
+  }
+
   /* check to see if we've been told to use an explicit SSL/TLS version */
   switch(SSL_CONN_CONFIG(version)) {
   case CURL_SSLVERSION_DEFAULT:
@@ -229,6 +235,15 @@ cyassl_connect_step1(struct connectdata *conn,
     break;
   }
 
+  ciphers = SSL_CONN_CONFIG(cipher_list);
+  if(ciphers) {
+    if(!SSL_CTX_set_cipher_list(conssl->ctx, ciphers)) {
+      failf(data, "failed setting cipher list: %s", ciphers);
+      return CURLE_SSL_CIPHER;
+    }
+    infof(data, "Cipher selection: %s\n", ciphers);
+  }
+
 #ifndef NO_FILESYSTEM
   /* load trusted cacert */
   if(SSL_CONN_CONFIG(CAfile)) {
@@ -383,7 +398,7 @@ cyassl_connect_step1(struct connectdata *conn,
 #endif /* HAVE_ALPN */
 
   /* Check if there's a cached ID we can/should use here! */
-  if(data->set.general_ssl.sessionid) {
+  if(SSL_SET_OPTION(primary.sessionid)) {
     void *ssl_sessionid = NULL;
 
     Curl_ssl_sessionid_lock(conn);
@@ -581,7 +596,13 @@ cyassl_connect_step2(struct connectdata *conn,
 #endif /* HAVE_ALPN */
 
   conssl->connecting_state = ssl_connect_3;
+#if (LIBCYASSL_VERSION_HEX >= 0x03009010)
+  infof(data, "SSL connection using %s / %s\n",
+        wolfSSL_get_version(conssl->handle),
+        wolfSSL_get_cipher_name(conssl->handle));
+#else
   infof(data, "SSL connected\n");
+#endif
 
   return CURLE_OK;
 }
@@ -597,7 +618,7 @@ cyassl_connect_step3(struct connectdata *conn,
 
   DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);
 
-  if(data->set.general_ssl.sessionid) {
+  if(SSL_SET_OPTION(primary.sessionid)) {
     bool incache;
     SSL_SESSION *our_ssl_sessionid;
     void *old_ssl_sessionid = NULL;
@@ -720,7 +741,9 @@ void Curl_cyassl_session_free(void *ptr)
 
 size_t Curl_cyassl_version(char *buffer, size_t size)
 {
-#ifdef WOLFSSL_VERSION
+#if LIBCYASSL_VERSION_HEX >= 0x03006000
+  return snprintf(buffer, size, "wolfSSL/%s", wolfSSL_lib_version());
+#elif defined(WOLFSSL_VERSION)
   return snprintf(buffer, size, "wolfSSL/%s", WOLFSSL_VERSION);
 #elif defined(CYASSL_VERSION)
   return snprintf(buffer, size, "CyaSSL/%s", CYASSL_VERSION);
@@ -772,7 +795,7 @@ cyassl_connect_common(struct connectdata *conn,
   struct Curl_easy *data = conn->data;
   struct ssl_connect_data *connssl = &conn->ssl[sockindex];
   curl_socket_t sockfd = conn->sock[sockindex];
-  long timeout_ms;
+  time_t timeout_ms;
   int what;
 
   /* check if the connection has already been established */
@@ -901,19 +924,19 @@ Curl_cyassl_connect(struct connectdata *conn,
   return CURLE_OK;
 }
 
-int Curl_cyassl_random(struct Curl_easy *data,
-                       unsigned char *entropy,
-                       size_t length)
+CURLcode Curl_cyassl_random(struct Curl_easy *data,
+                            unsigned char *entropy,
+                            size_t length)
 {
   RNG rng;
   (void)data;
   if(InitRng(&rng))
-    return 1;
+    return CURLE_FAILED_INIT;
   if(length > UINT_MAX)
-    return 1;
+    return CURLE_FAILED_INIT;
   if(RNG_GenerateBlock(&rng, entropy, (unsigned)length))
-    return 1;
-  return 0;
+    return CURLE_FAILED_INIT;
+  return CURLE_OK;
 }
 
 void Curl_cyassl_sha256sum(const unsigned char *tmp, /* input */