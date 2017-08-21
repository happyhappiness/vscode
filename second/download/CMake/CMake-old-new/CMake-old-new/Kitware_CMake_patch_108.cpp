@@ -176,39 +176,34 @@ static int passwd_callback(char *buf, int num, int encrypting,
 }
 
 /*
- * rand_enough() is a function that returns TRUE if we have seeded the random
- * engine properly. We use some preprocessor magic to provide a seed_enough()
- * macro to use, just to prevent a compiler warning on this function if we
- * pass in an argument that is never used.
+ * rand_enough() returns TRUE if we have seeded the random engine properly.
  */
-
-#ifdef HAVE_RAND_STATUS
-#define seed_enough(x) rand_enough()
 static bool rand_enough(void)
 {
   return (0 != RAND_status()) ? TRUE : FALSE;
 }
-#else
-#define seed_enough(x) rand_enough(x)
-static bool rand_enough(int nread)
-{
-  /* this is a very silly decision to make */
-  return (nread > 500) ? TRUE : FALSE;
-}
-#endif
 
-static int ossl_seed(struct Curl_easy *data)
+static CURLcode Curl_ossl_seed(struct Curl_easy *data)
 {
+  /* we have the "SSL is seeded" boolean static to prevent multiple
+     time-consuming seedings in vain */
+  static bool ssl_seeded = FALSE;
   char *buf = data->state.buffer; /* point to the big buffer */
   int nread=0;
 
-  /* Q: should we add support for a random file name as a libcurl option?
-     A: Yes, it is here */
+  if(ssl_seeded)
+    return CURLE_OK;
+
+  if(rand_enough()) {
+    /* OpenSSL 1.1.0+ will return here */
+    ssl_seeded = TRUE;
+    return CURLE_OK;
+  }
 
 #ifndef RANDOM_FILE
   /* if RANDOM_FILE isn't defined, we only perform this if an option tells
      us to! */
-  if(data->set.ssl.random_file)
+  if(data->set.str[STRING_SSL_RANDOM_FILE])
 #define RANDOM_FILE "" /* doesn't matter won't be used */
 #endif
   {
@@ -217,7 +212,7 @@ static int ossl_seed(struct Curl_easy *data)
                              data->set.str[STRING_SSL_RANDOM_FILE]:
                              RANDOM_FILE),
                             RAND_LOAD_LENGTH);
-    if(seed_enough(nread))
+    if(rand_enough())
       return nread;
   }
 
@@ -237,7 +232,7 @@ static int ossl_seed(struct Curl_easy *data)
                        data->set.str[STRING_SSL_EGDSOCKET]:EGD_SOCKET);
     if(-1 != ret) {
       nread += ret;
-      if(seed_enough(nread))
+      if(rand_enough())
         return nread;
     }
   }
@@ -248,35 +243,23 @@ static int ossl_seed(struct Curl_easy *data)
   do {
     unsigned char randb[64];
     int len = sizeof(randb);
-    RAND_bytes(randb, len);
+    if(!RAND_bytes(randb, len))
+      break;
     RAND_add(randb, len, (len >> 1));
-  } while(!RAND_status());
+  } while(!rand_enough());
 
   /* generates a default path for the random seed file */
   buf[0]=0; /* blank it first */
   RAND_file_name(buf, BUFSIZE);
   if(buf[0]) {
     /* we got a file name to try */
     nread += RAND_load_file(buf, RAND_LOAD_LENGTH);
-    if(seed_enough(nread))
+    if(rand_enough())
       return nread;
   }
 
   infof(data, "libcurl is now using a weak random seed!\n");
-  return nread;
-}
-
-static void Curl_ossl_seed(struct Curl_easy *data)
-{
-  /* we have the "SSL is seeded" boolean static to prevent multiple
-     time-consuming seedings in vain */
-  static bool ssl_seeded = FALSE;
-
-  if(!ssl_seeded || data->set.str[STRING_SSL_RANDOM_FILE] ||
-     data->set.str[STRING_SSL_EGDSOCKET]) {
-    ossl_seed(data);
-    ssl_seeded = TRUE;
-  }
+  return CURLE_SSL_CONNECT_ERROR; /* confusing error code */
 }
 
 #ifndef SSL_FILETYPE_ENGINE
@@ -312,7 +295,7 @@ static int ssl_ui_reader(UI *ui, UI_STRING *uis)
   switch(UI_get_string_type(uis)) {
   case UIT_PROMPT:
   case UIT_VERIFY:
-    password = (const char*)UI_get0_user_data(ui);
+    password = (const char *)UI_get0_user_data(ui);
     if(password && (UI_get_input_flags(uis) & UI_INPUT_FLAG_DEFAULT_PWD)) {
       UI_set_result(ui, uis, password);
       return 1;
@@ -348,7 +331,8 @@ int cert_stuff(struct connectdata *conn,
                char *cert_file,
                const char *cert_type,
                char *key_file,
-               const char *key_type)
+               const char *key_type,
+               char *key_passwd)
 {
   struct Curl_easy *data = conn->data;
 
@@ -359,10 +343,9 @@ int cert_stuff(struct connectdata *conn,
     X509 *x509;
     int cert_done = 0;
 
-    if(data->set.str[STRING_KEY_PASSWD]) {
+    if(key_passwd) {
       /* set the password in the callback userdata */
-      SSL_CTX_set_default_passwd_cb_userdata(ctx,
-                                             data->set.str[STRING_KEY_PASSWD]);
+      SSL_CTX_set_default_passwd_cb_userdata(ctx, key_passwd);
       /* Set passwd callback: */
       SSL_CTX_set_default_passwd_cb(ctx, passwd_callback);
     }
@@ -473,7 +456,7 @@ int cert_stuff(struct connectdata *conn,
 
       PKCS12_PBE_add();
 
-      if(!PKCS12_parse(p12, data->set.str[STRING_KEY_PASSWD], &pri, &x509,
+      if(!PKCS12_parse(p12, key_passwd, &pri, &x509,
                        &ca)) {
         failf(data,
               "could not parse PKCS12 file, check password, " OSSL_PACKAGE
@@ -571,7 +554,7 @@ int cert_stuff(struct connectdata *conn,
         EVP_PKEY *priv_key = NULL;
         if(data->state.engine) {
           UI_METHOD *ui_method =
-            UI_create_method((char *)"cURL user interface");
+            UI_create_method((char *)"curl user interface");
           if(!ui_method) {
             failf(data, "unable do create " OSSL_PACKAGE
                   " user-interface method");
@@ -585,7 +568,7 @@ int cert_stuff(struct connectdata *conn,
           priv_key = (EVP_PKEY *)
             ENGINE_load_private_key(data->state.engine, key_file,
                                     ui_method,
-                                    data->set.str[STRING_KEY_PASSWD]);
+                                    key_passwd);
           UI_destroy_method(ui_method);
           if(!priv_key) {
             failf(data, "failed to load private key from crypto engine");
@@ -916,27 +899,31 @@ struct curl_slist *Curl_ossl_engines_list(struct Curl_easy *data)
 }
 
 
-/*
- * This function is called when an SSL connection is closed.
- */
-void Curl_ossl_close(struct connectdata *conn, int sockindex)
+static void ossl_close(struct ssl_connect_data *connssl)
 {
-  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
-
   if(connssl->handle) {
     (void)SSL_shutdown(connssl->handle);
     SSL_set_connect_state(connssl->handle);
 
-    SSL_free (connssl->handle);
+    SSL_free(connssl->handle);
     connssl->handle = NULL;
   }
   if(connssl->ctx) {
-    SSL_CTX_free (connssl->ctx);
+    SSL_CTX_free(connssl->ctx);
     connssl->ctx = NULL;
   }
 }
 
 /*
+ * This function is called when an SSL connection is closed.
+ */
+void Curl_ossl_close(struct connectdata *conn, int sockindex)
+{
+  ossl_close(&conn->ssl[sockindex]);
+  ossl_close(&conn->proxy_ssl[sockindex]);
+}
+
+/*
  * This function is called to shut down the SSL layer but keep the
  * socket open (CCC - Clear Command Channel)
  */
@@ -1031,7 +1018,7 @@ int Curl_ossl_shutdown(struct connectdata *conn, int sockindex)
 #endif
     }
 
-    SSL_free (connssl->handle);
+    SSL_free(connssl->handle);
     connssl->handle = NULL;
   }
   return retval;
@@ -1107,16 +1094,20 @@ static CURLcode verifyhost(struct connectdata *conn, X509 *server_cert)
   CURLcode result = CURLE_OK;
   bool dNSName = FALSE; /* if a dNSName field exists in the cert */
   bool iPAddress = FALSE; /* if a iPAddress field exists in the cert */
+  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
+    conn->host.name;
+  const char * const dispname = SSL_IS_PROXY() ?
+    conn->http_proxy.host.dispname : conn->host.dispname;
 
 #ifdef ENABLE_IPV6
   if(conn->bits.ipv6_ip &&
-     Curl_inet_pton(AF_INET6, conn->host.name, &addr)) {
+     Curl_inet_pton(AF_INET6, hostname, &addr)) {
     target = GEN_IPADD;
     addrlen = sizeof(struct in6_addr);
   }
   else
 #endif
-    if(Curl_inet_pton(AF_INET, conn->host.name, &addr)) {
+    if(Curl_inet_pton(AF_INET, hostname, &addr)) {
       target = GEN_IPADD;
       addrlen = sizeof(struct in_addr);
     }
@@ -1165,11 +1156,11 @@ static CURLcode verifyhost(struct connectdata *conn, X509 *server_cert)
           if((altlen == strlen(altptr)) &&
              /* if this isn't true, there was an embedded zero in the name
                 string and we cannot match it. */
-             Curl_cert_hostcheck(altptr, conn->host.name)) {
+             Curl_cert_hostcheck(altptr, hostname)) {
             dnsmatched = TRUE;
             infof(data,
                   " subjectAltName: host \"%s\" matched cert's \"%s\"\n",
-                  conn->host.dispname, altptr);
+                  dispname, altptr);
           }
           break;
 
@@ -1180,7 +1171,7 @@ static CURLcode verifyhost(struct connectdata *conn, X509 *server_cert)
             ipmatched = TRUE;
             infof(data,
                   " subjectAltName: host \"%s\" matched cert's IP address!\n",
-                  conn->host.dispname);
+                  dispname);
           }
           break;
         }
@@ -1196,9 +1187,9 @@ static CURLcode verifyhost(struct connectdata *conn, X509 *server_cert)
     /* an alternative name matched */
     ;
   else if(dNSName || iPAddress) {
-    infof(data, " subjectAltName does not match %s\n", conn->host.dispname);
+    infof(data, " subjectAltName does not match %s\n", dispname);
     failf(data, "SSL: no alternative certificate subject name matches "
-          "target host name '%s'", conn->host.dispname);
+          "target host name '%s'", dispname);
     result = CURLE_PEER_FAILED_VERIFICATION;
   }
   else {
@@ -1272,9 +1263,9 @@ static CURLcode verifyhost(struct connectdata *conn, X509 *server_cert)
             "SSL: unable to obtain common name from peer certificate");
       result = CURLE_PEER_FAILED_VERIFICATION;
     }
-    else if(!Curl_cert_hostcheck((const char *)peer_CN, conn->host.name)) {
+    else if(!Curl_cert_hostcheck((const char *)peer_CN, hostname)) {
       failf(data, "SSL: certificate subject name '%s' does not match "
-            "target host name '%s'", peer_CN, conn->host.dispname);
+            "target host name '%s'", peer_CN, dispname);
       result = CURLE_PEER_FAILED_VERIFICATION;
     }
     else {
@@ -1425,7 +1416,7 @@ static const char *ssl_msg_type(int ssl_ver, int msg)
 {
 #ifdef SSL2_VERSION_MAJOR
   if(ssl_ver == SSL2_VERSION_MAJOR) {
-    switch (msg) {
+    switch(msg) {
       case SSL2_MT_ERROR:
         return "Error";
       case SSL2_MT_CLIENT_HELLO:
@@ -1449,7 +1440,7 @@ static const char *ssl_msg_type(int ssl_ver, int msg)
   else
 #endif
   if(ssl_ver == SSL3_VERSION_MAJOR) {
-    switch (msg) {
+    switch(msg) {
       case SSL3_MT_HELLO_REQUEST:
         return "Hello request";
       case SSL3_MT_CLIENT_HELLO:
@@ -1549,6 +1540,11 @@ static void ssl_tls_trace(int direction, int ssl_ver, int content_type,
     verstr = "TLSv1.2";
     break;
 #endif
+#ifdef TLS1_3_VERSION
+  case TLS1_3_VERSION:
+    verstr = "TLSv1.3";
+    break;
+#endif
   case 0:
     break;
   default:
@@ -1571,7 +1567,7 @@ static void ssl_tls_trace(int direction, int ssl_ver, int content_type,
     else
       tls_rt_name = "";
 
-    msg_type = *(char*)buf;
+    msg_type = *(char *)buf;
     msg_name = ssl_msg_type(ssl_ver, msg_type);
 
     txt_len = snprintf(ssl_buf, sizeof(ssl_buf), "%s (%s), %s, %s (%d):\n",
@@ -1677,6 +1673,10 @@ get_ssl_version_txt(SSL *ssl)
     return "";
 
   switch(SSL_version(ssl)) {
+#ifdef TLS1_3_VERSION
+  case TLS1_3_VERSION:
+    return "TLSv1.3";
+#endif
 #if OPENSSL_VERSION_NUMBER >= 0x1000100FL
   case TLS1_2_VERSION:
     return "TLSv1.2";
@@ -1711,23 +1711,39 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
   struct in_addr addr;
 #endif
 #endif
+  long * const certverifyresult = SSL_IS_PROXY() ?
+    &data->set.proxy_ssl.certverifyresult : &data->set.ssl.certverifyresult;
+  const long int ssl_version = SSL_CONN_CONFIG(version);
+#ifdef USE_TLS_SRP
+  const enum CURL_TLSAUTH ssl_authtype = SSL_SET_OPTION(authtype);
+#endif
+  char * const ssl_cert = SSL_SET_OPTION(cert);
+  const char * const ssl_cert_type = SSL_SET_OPTION(cert_type);
+  const char * const ssl_cafile = SSL_CONN_CONFIG(CAfile);
+  const char * const ssl_capath = SSL_CONN_CONFIG(CApath);
+  const bool verifypeer = SSL_CONN_CONFIG(verifypeer);
+  const char * const ssl_crlfile = SSL_SET_OPTION(CRLfile);
+  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
+    conn->host.name;
 
   DEBUGASSERT(ssl_connect_1 == connssl->connecting_state);
 
   /* Make funny stuff to get random input */
-  Curl_ossl_seed(data);
+  result = Curl_ossl_seed(data);
+  if(result)
+    return result;
 
-  data->set.ssl.certverifyresult = !X509_V_OK;
+  *certverifyresult = !X509_V_OK;
 
   /* check to see if we've been told to use an explicit SSL/TLS version */
 
-  switch(data->set.ssl.version) {
-  default:
+  switch(ssl_version) {
   case CURL_SSLVERSION_DEFAULT:
   case CURL_SSLVERSION_TLSv1:
   case CURL_SSLVERSION_TLSv1_0:
   case CURL_SSLVERSION_TLSv1_1:
   case CURL_SSLVERSION_TLSv1_2:
+  case CURL_SSLVERSION_TLSv1_3:
     /* it will be handled later with the context options */
 #if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && \
     !defined(LIBRESSL_VERSION_NUMBER)
@@ -1743,7 +1759,7 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
     return CURLE_NOT_BUILT_IN;
 #else
 #ifdef USE_TLS_SRP
-    if(data->set.ssl.authtype == CURL_TLSAUTH_SRP)
+    if(ssl_authtype == CURL_TLSAUTH_SRP)
       return CURLE_SSL_CONNECT_ERROR;
 #endif
     req_method = SSLv2_client_method();
@@ -1756,13 +1772,16 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
     return CURLE_NOT_BUILT_IN;
 #else
 #ifdef USE_TLS_SRP
-    if(data->set.ssl.authtype == CURL_TLSAUTH_SRP)
+    if(ssl_authtype == CURL_TLSAUTH_SRP)
       return CURLE_SSL_CONNECT_ERROR;
 #endif
     req_method = SSLv3_client_method();
     use_sni(FALSE);
     break;
 #endif
+  default:
+    failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
+    return CURLE_SSL_CONNECT_ERROR;
   }
 
   if(connssl->ctx)
@@ -1841,14 +1860,14 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
 #ifdef SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS
   /* unless the user explicitly ask to allow the protocol vulnerability we
      use the work-around */
-  if(!conn->data->set.ssl_enable_beast)
+  if(!SSL_SET_OPTION(enable_beast))
     ctx_options &= ~SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS;
 #endif
 
-  switch(data->set.ssl.version) {
+  switch(ssl_version) {
   case CURL_SSLVERSION_SSLv3:
 #ifdef USE_TLS_SRP
-    if(data->set.ssl.authtype == CURL_TLSAUTH_SRP) {
+    if(ssl_authtype == CURL_TLSAUTH_SRP) {
       infof(data, "Set version TLSv1.x for SRP authorisation\n");
     }
 #endif
@@ -1857,6 +1876,9 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
 #if OPENSSL_VERSION_NUMBER >= 0x1000100FL
     ctx_options |= SSL_OP_NO_TLSv1_1;
     ctx_options |= SSL_OP_NO_TLSv1_2;
+#ifdef TLS1_3_VERSION
+    ctx_options |= SSL_OP_NO_TLSv1_3;
+#endif
 #endif
     break;
 
@@ -1872,38 +1894,75 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
 #if OPENSSL_VERSION_NUMBER >= 0x1000100FL
     ctx_options |= SSL_OP_NO_TLSv1_1;
     ctx_options |= SSL_OP_NO_TLSv1_2;
+#ifdef TLS1_3_VERSION
+    ctx_options |= SSL_OP_NO_TLSv1_3;
+#endif
 #endif
     break;
 
-#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
   case CURL_SSLVERSION_TLSv1_1:
+#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
     ctx_options |= SSL_OP_NO_SSLv2;
     ctx_options |= SSL_OP_NO_SSLv3;
     ctx_options |= SSL_OP_NO_TLSv1;
     ctx_options |= SSL_OP_NO_TLSv1_2;
+#ifdef TLS1_3_VERSION
+    ctx_options |= SSL_OP_NO_TLSv1_3;
+#endif
     break;
+#else
+    failf(data, OSSL_PACKAGE " was built without TLS 1.1 support");
+    return CURLE_NOT_BUILT_IN;
+#endif
 
   case CURL_SSLVERSION_TLSv1_2:
+#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
     ctx_options |= SSL_OP_NO_SSLv2;
     ctx_options |= SSL_OP_NO_SSLv3;
     ctx_options |= SSL_OP_NO_TLSv1;
     ctx_options |= SSL_OP_NO_TLSv1_1;
+#ifdef TLS1_3_VERSION
+    ctx_options |= SSL_OP_NO_TLSv1_3;
+#endif
     break;
+#else
+    failf(data, OSSL_PACKAGE " was built without TLS 1.2 support");
+    return CURLE_NOT_BUILT_IN;
+#endif
+
+  case CURL_SSLVERSION_TLSv1_3:
+#ifdef TLS1_3_VERSION
+    SSL_CTX_set_max_proto_version(connssl->ctx, TLS1_3_VERSION);
+    ctx_options |= SSL_OP_NO_SSLv2;
+    ctx_options |= SSL_OP_NO_SSLv3;
+    ctx_options |= SSL_OP_NO_TLSv1;
+    ctx_options |= SSL_OP_NO_TLSv1_1;
+    ctx_options |= SSL_OP_NO_TLSv1_2;
+    break;
+#else
+    failf(data, OSSL_PACKAGE " was built without TLS 1.3 support");
+    return CURLE_NOT_BUILT_IN;
 #endif
 
-#ifndef OPENSSL_NO_SSL2
   case CURL_SSLVERSION_SSLv2:
+#ifndef OPENSSL_NO_SSL2
     ctx_options |= SSL_OP_NO_SSLv3;
     ctx_options |= SSL_OP_NO_TLSv1;
 #if OPENSSL_VERSION_NUMBER >= 0x1000100FL
     ctx_options |= SSL_OP_NO_TLSv1_1;
     ctx_options |= SSL_OP_NO_TLSv1_2;
+#ifdef TLS1_3_VERSION
+    ctx_options |= SSL_OP_NO_TLSv1_3;
+#endif
 #endif
     break;
+#else
+    failf(data, OSSL_PACKAGE " was built without SSLv2 support");
+    return CURLE_NOT_BUILT_IN;
 #endif
 
   default:
-    failf(data, "Unsupported SSL protocol version");
+    failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
     return CURLE_SSL_CONNECT_ERROR;
   }
 
@@ -1942,19 +2001,16 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
   }
 #endif
 
-  if(data->set.str[STRING_CERT] || data->set.str[STRING_CERT_TYPE]) {
-    if(!cert_stuff(conn,
-                   connssl->ctx,
-                   data->set.str[STRING_CERT],
-                   data->set.str[STRING_CERT_TYPE],
-                   data->set.str[STRING_KEY],
-                   data->set.str[STRING_KEY_TYPE])) {
+  if(ssl_cert || ssl_cert_type) {
+    if(!cert_stuff(conn, connssl->ctx, ssl_cert, ssl_cert_type,
+                   SSL_SET_OPTION(key), SSL_SET_OPTION(key_type),
+                   SSL_SET_OPTION(key_passwd))) {
       /* failf() is already done in cert_stuff() */
       return CURLE_SSL_CERTPROBLEM;
     }
   }
 
-  ciphers = data->set.str[STRING_SSL_CIPHER_LIST];
+  ciphers = SSL_CONN_CONFIG(cipher_list);
   if(!ciphers)
     ciphers = (char *)DEFAULT_CIPHER_SELECTION;
   if(!SSL_CTX_set_cipher_list(connssl->ctx, ciphers)) {
@@ -1964,18 +2020,20 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
   infof(data, "Cipher selection: %s\n", ciphers);
 
 #ifdef USE_TLS_SRP
-  if(data->set.ssl.authtype == CURL_TLSAUTH_SRP) {
-    infof(data, "Using TLS-SRP username: %s\n", data->set.ssl.username);
+  if(ssl_authtype == CURL_TLSAUTH_SRP) {
+    char * const ssl_username = SSL_SET_OPTION(username);
+
+    infof(data, "Using TLS-SRP username: %s\n", ssl_username);
 
-    if(!SSL_CTX_set_srp_username(connssl->ctx, data->set.ssl.username)) {
+    if(!SSL_CTX_set_srp_username(connssl->ctx, ssl_username)) {
       failf(data, "Unable to set SRP user name");
       return CURLE_BAD_FUNCTION_ARGUMENT;
     }
-    if(!SSL_CTX_set_srp_password(connssl->ctx, data->set.ssl.password)) {
+    if(!SSL_CTX_set_srp_password(connssl->ctx, SSL_SET_OPTION(password))) {
       failf(data, "failed setting SRP password");
       return CURLE_BAD_FUNCTION_ARGUMENT;
     }
-    if(!data->set.str[STRING_SSL_CIPHER_LIST]) {
+    if(!SSL_CONN_CONFIG(cipher_list)) {
       infof(data, "Setting cipher list SRP\n");
 
       if(!SSL_CTX_set_cipher_list(connssl->ctx, "SRP")) {
@@ -1985,20 +2043,17 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
     }
   }
 #endif
-  if(data->set.str[STRING_SSL_CAFILE] || data->set.str[STRING_SSL_CAPATH]) {
+
+  if(ssl_cafile || ssl_capath) {
     /* tell SSL where to find CA certificates that are used to verify
        the servers certificate. */
-    if(!SSL_CTX_load_verify_locations(connssl->ctx,
-                                       data->set.str[STRING_SSL_CAFILE],
-                                       data->set.str[STRING_SSL_CAPATH])) {
-      if(data->set.ssl.verifypeer) {
+    if(!SSL_CTX_load_verify_locations(connssl->ctx, ssl_cafile, ssl_capath)) {
+      if(verifypeer) {
         /* Fail if we insist on successfully verifying the server. */
         failf(data, "error setting certificate verify locations:\n"
               "  CAfile: %s\n  CApath: %s",
-              data->set.str[STRING_SSL_CAFILE]?
-              data->set.str[STRING_SSL_CAFILE]: "none",
-              data->set.str[STRING_SSL_CAPATH]?
-              data->set.str[STRING_SSL_CAPATH] : "none");
+              ssl_cafile ? ssl_cafile : "none",
+              ssl_capath ? ssl_capath : "none");
         return CURLE_SSL_CACERT_BADFILE;
       }
       else {
@@ -2015,29 +2070,25 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
     infof(data,
           "  CAfile: %s\n"
           "  CApath: %s\n",
-          data->set.str[STRING_SSL_CAFILE] ? data->set.str[STRING_SSL_CAFILE]:
-          "none",
-          data->set.str[STRING_SSL_CAPATH] ? data->set.str[STRING_SSL_CAPATH]:
-          "none");
+          ssl_cafile ? ssl_cafile : "none",
+          ssl_capath ? ssl_capath : "none");
   }
 #ifdef CURL_CA_FALLBACK
-  else if(data->set.ssl.verifypeer) {
+  else if(verifypeer) {
     /* verfying the peer without any CA certificates won't
        work so use openssl's built in default as fallback */
     SSL_CTX_set_default_verify_paths(connssl->ctx);
   }
 #endif
 
-  if(data->set.str[STRING_SSL_CRLFILE]) {
+  if(ssl_crlfile) {
     /* tell SSL where to find CRL file that is used to check certificate
      * revocation */
     lookup=X509_STORE_add_lookup(SSL_CTX_get_cert_store(connssl->ctx),
                                  X509_LOOKUP_file());
     if(!lookup ||
-       (!X509_load_crl_file(lookup, data->set.str[STRING_SSL_CRLFILE],
-                            X509_FILETYPE_PEM)) ) {
-      failf(data, "error loading CRL file: %s",
-            data->set.str[STRING_SSL_CRLFILE]);
+       (!X509_load_crl_file(lookup, ssl_crlfile, X509_FILETYPE_PEM)) ) {
+      failf(data, "error loading CRL file: %s", ssl_crlfile);
       return CURLE_SSL_CRL_BADFILE;
     }
     else {
@@ -2046,9 +2097,7 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
       X509_STORE_set_flags(SSL_CTX_get_cert_store(connssl->ctx),
                            X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
     }
-    infof(data,
-          "  CRLfile: %s\n", data->set.str[STRING_SSL_CRLFILE] ?
-          data->set.str[STRING_SSL_CRLFILE]: "none");
+    infof(data, "  CRLfile: %s\n", ssl_crlfile);
   }
 
   /* Try building a chain using issuers in the trusted store first to avoid
@@ -2059,7 +2108,7 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
   https://rt.openssl.org/Ticket/Display.html?id=3621&user=guest&pass=guest
   */
 #if defined(X509_V_FLAG_TRUSTED_FIRST) && !defined(X509_V_FLAG_NO_ALT_CHAINS)
-  if(data->set.ssl.verifypeer) {
+  if(verifypeer) {
     X509_STORE_set_flags(SSL_CTX_get_cert_store(connssl->ctx),
                          X509_V_FLAG_TRUSTED_FIRST);
   }
@@ -2070,8 +2119,7 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
    * anyway. In the latter case the result of the verification is checked with
    * SSL_get_verify_result() below. */
   SSL_CTX_set_verify(connssl->ctx,
-                     data->set.ssl.verifypeer?SSL_VERIFY_PEER:SSL_VERIFY_NONE,
-                     NULL);
+                     verifypeer ? SSL_VERIFY_PEER : SSL_VERIFY_NONE, NULL);
 
   /* give application a chance to interfere with SSL set up. */
   if(data->set.ssl.fsslctx) {
@@ -2094,31 +2142,30 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
 
 #if (OPENSSL_VERSION_NUMBER >= 0x0090808fL) && !defined(OPENSSL_NO_TLSEXT) && \
     !defined(OPENSSL_NO_OCSP)
-  if(data->set.ssl.verifystatus)
+  if(SSL_CONN_CONFIG(verifystatus))
     SSL_set_tlsext_status_type(connssl->handle, TLSEXT_STATUSTYPE_ocsp);
 #endif
 
   SSL_set_connect_state(connssl->handle);
 
   connssl->server_cert = 0x0;
-
 #ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
-  if((0 == Curl_inet_pton(AF_INET, conn->host.name, &addr)) &&
+  if((0 == Curl_inet_pton(AF_INET, hostname, &addr)) &&
 #ifdef ENABLE_IPV6
-     (0 == Curl_inet_pton(AF_INET6, conn->host.name, &addr)) &&
+     (0 == Curl_inet_pton(AF_INET6, hostname, &addr)) &&
 #endif
      sni &&
-     !SSL_set_tlsext_host_name(connssl->handle, conn->host.name))
+     !SSL_set_tlsext_host_name(connssl->handle, hostname))
     infof(data, "WARNING: failed to configure server name indication (SNI) "
           "TLS extension\n");
 #endif
 
   /* Check if there's a cached ID we can/should use here! */
-  if(conn->ssl_config.sessionid) {
+  if(data->set.general_ssl.sessionid) {
     void *ssl_sessionid = NULL;
 
     Curl_ssl_sessionid_lock(conn);
-    if(!Curl_ssl_getsessionid(conn, &ssl_sessionid, NULL)) {
+    if(!Curl_ssl_getsessionid(conn, &ssl_sessionid, NULL, sockindex)) {
       /* we got a session id, use it! */
       if(!SSL_set_session(connssl->handle, ssl_sessionid)) {
         Curl_ssl_sessionid_unlock(conn);
@@ -2127,13 +2174,21 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
         return CURLE_SSL_CONNECT_ERROR;
       }
       /* Informational message */
-      infof (data, "SSL re-using session ID\n");
+      infof(data, "SSL re-using session ID\n");
     }
     Curl_ssl_sessionid_unlock(conn);
   }
 
-  /* pass the raw socket into the SSL layers */
-  if(!SSL_set_fd(connssl->handle, (int)sockfd)) {
+  if(conn->proxy_ssl[sockindex].use) {
+    BIO *const bio = BIO_new(BIO_f_ssl());
+    DEBUGASSERT(ssl_connection_complete == conn->proxy_ssl[sockindex].state);
+    DEBUGASSERT(conn->proxy_ssl[sockindex].handle != NULL);
+    DEBUGASSERT(bio != NULL);
+    BIO_set_ssl(bio, conn->proxy_ssl[sockindex].handle, FALSE);
+    SSL_set_bio(connssl->handle, bio, bio);
+  }
+  else if(!SSL_set_fd(connssl->handle, (int)sockfd)) {
+    /* pass the raw socket into the SSL layers */
     failf(data, "SSL: SSL_set_fd failed: %s",
           ERR_error_string(ERR_get_error(), NULL));
     return CURLE_SSL_CONNECT_ERROR;
@@ -2149,9 +2204,11 @@ static CURLcode ossl_connect_step2(struct connectdata *conn, int sockindex)
   struct Curl_easy *data = conn->data;
   int err;
   struct ssl_connect_data *connssl = &conn->ssl[sockindex];
+  long * const certverifyresult = SSL_IS_PROXY() ?
+    &data->set.proxy_ssl.certverifyresult : &data->set.ssl.certverifyresult;
   DEBUGASSERT(ssl_connect_2 == connssl->connecting_state
-             || ssl_connect_2_reading == connssl->connecting_state
-             || ssl_connect_2_writing == connssl->connecting_state);
+              || ssl_connect_2_reading == connssl->connecting_state
+              || ssl_connect_2_writing == connssl->connecting_state);
 
   ERR_clear_error();
 
@@ -2198,7 +2255,7 @@ static CURLcode ossl_connect_step2(struct connectdata *conn, int sockindex)
 
         lerr = SSL_get_verify_result(connssl->handle);
         if(lerr != X509_V_OK) {
-          data->set.ssl.certverifyresult = lerr;
+          *certverifyresult = lerr;
           snprintf(error_buffer, sizeof(error_buffer),
                    "SSL certificate problem: %s",
                    X509_verify_cert_error_string(lerr));
@@ -2220,8 +2277,11 @@ static CURLcode ossl_connect_step2(struct connectdata *conn, int sockindex)
        * the SO_ERROR is also lost.
        */
       if(CURLE_SSL_CONNECT_ERROR == result && errdetail == 0) {
+        const char * const hostname = SSL_IS_PROXY() ?
+          conn->http_proxy.host.name : conn->host.name;
+        const long int port = SSL_IS_PROXY() ? conn->port : conn->remote_port;
         failf(data, "Unknown SSL protocol error in connection to %s:%ld ",
-              conn->host.name, conn->remote_port);
+              hostname, port);
         return result;
       }
 
@@ -2245,7 +2305,7 @@ static CURLcode ossl_connect_step2(struct connectdata *conn, int sockindex)
      * negotiated
      */
     if(conn->bits.tls_enable_alpn) {
-      const unsigned char* neg_protocol;
+      const unsigned char *neg_protocol;
       unsigned int len;
       SSL_get0_alpn_selected(connssl->handle, &neg_protocol, &len);
       if(len != 0) {
@@ -2276,7 +2336,8 @@ static int asn1_object_dump(ASN1_OBJECT *a, char *buf, size_t len)
 {
   int i, ilen;
 
-  if((ilen = (int)len) < 0)
+  ilen = (int)len;
+  if(ilen < 0)
     return 1; /* buffer too big */
 
   i = i2t_ASN1_OBJECT(buf, ilen, a);
@@ -2698,6 +2759,8 @@ static CURLcode servercert(struct connectdata *conn,
   FILE *fp;
   char *buffer = data->state.buffer;
   const char *ptr;
+  long * const certverifyresult = SSL_IS_PROXY() ?
+    &data->set.proxy_ssl.certverifyresult : &data->set.ssl.certverifyresult;
   BIO *mem = BIO_new(BIO_s_mem());
 
   if(data->set.ssl.certinfo)
@@ -2713,7 +2776,7 @@ static CURLcode servercert(struct connectdata *conn,
     return CURLE_PEER_FAILED_VERIFICATION;
   }
 
-  infof(data, "Server certificate:\n");
+  infof(data, "%s certificate:\n", SSL_IS_PROXY() ? "Proxy" : "Server");
 
   rc = x509_name_oneline(X509_get_subject_name(connssl->server_cert),
                          buffer, BUFSIZE);
@@ -2731,7 +2794,7 @@ static CURLcode servercert(struct connectdata *conn,
 
   BIO_free(mem);
 
-  if(data->set.ssl.verifyhost) {
+  if(SSL_CONN_CONFIG(verifyhost)) {
     result = verifyhost(conn, connssl->server_cert);
     if(result) {
       X509_free(connssl->server_cert);
@@ -2754,12 +2817,12 @@ static CURLcode servercert(struct connectdata *conn,
        deallocating the certificate. */
 
     /* e.g. match issuer name with provided issuer certificate */
-    if(data->set.str[STRING_SSL_ISSUERCERT]) {
-      fp = fopen(data->set.str[STRING_SSL_ISSUERCERT], FOPEN_READTEXT);
+    if(SSL_SET_OPTION(issuercert)) {
+      fp = fopen(SSL_SET_OPTION(issuercert), FOPEN_READTEXT);
       if(!fp) {
         if(strict)
           failf(data, "SSL: Unable to open issuer cert (%s)",
-                data->set.str[STRING_SSL_ISSUERCERT]);
+                SSL_SET_OPTION(issuercert));
         X509_free(connssl->server_cert);
         connssl->server_cert = NULL;
         return CURLE_SSL_ISSUER_ERROR;
@@ -2769,7 +2832,7 @@ static CURLcode servercert(struct connectdata *conn,
       if(!issuer) {
         if(strict)
           failf(data, "SSL: Unable to read issuer cert (%s)",
-                data->set.str[STRING_SSL_ISSUERCERT]);
+                SSL_SET_OPTION(issuercert));
         X509_free(connssl->server_cert);
         X509_free(issuer);
         fclose(fp);
@@ -2781,23 +2844,22 @@ static CURLcode servercert(struct connectdata *conn,
       if(X509_check_issued(issuer, connssl->server_cert) != X509_V_OK) {
         if(strict)
           failf(data, "SSL: Certificate issuer check failed (%s)",
-                data->set.str[STRING_SSL_ISSUERCERT]);
+                SSL_SET_OPTION(issuercert));
         X509_free(connssl->server_cert);
         X509_free(issuer);
         connssl->server_cert = NULL;
         return CURLE_SSL_ISSUER_ERROR;
       }
 
       infof(data, " SSL certificate issuer check ok (%s)\n",
-            data->set.str[STRING_SSL_ISSUERCERT]);
+            SSL_SET_OPTION(issuercert));
       X509_free(issuer);
     }
 
-    lerr = data->set.ssl.certverifyresult =
-      SSL_get_verify_result(connssl->handle);
+    lerr = *certverifyresult = SSL_get_verify_result(connssl->handle);
 
-    if(data->set.ssl.certverifyresult != X509_V_OK) {
-      if(data->set.ssl.verifypeer) {
+    if(*certverifyresult != X509_V_OK) {
+      if(SSL_CONN_CONFIG(verifypeer)) {
         /* We probably never reach this, because SSL_connect() will fail
            and we return earlier if verifypeer is set? */
         if(strict)
@@ -2816,7 +2878,7 @@ static CURLcode servercert(struct connectdata *conn,
 
 #if (OPENSSL_VERSION_NUMBER >= 0x0090808fL) && !defined(OPENSSL_NO_TLSEXT) && \
     !defined(OPENSSL_NO_OCSP)
-  if(data->set.ssl.verifystatus) {
+  if(SSL_CONN_CONFIG(verifystatus)) {
     result = verifystatus(conn, connssl);
     if(result) {
       X509_free(connssl->server_cert);
@@ -2830,7 +2892,8 @@ static CURLcode servercert(struct connectdata *conn,
     /* when not strict, we don't bother about the verify cert problems */
     result = CURLE_OK;
 
-  ptr = data->set.str[STRING_SSL_PINNEDPUBLICKEY];
+  ptr = SSL_IS_PROXY() ? data->set.str[STRING_SSL_PINNEDPUBLICKEY_PROXY] :
+                         data->set.str[STRING_SSL_PINNEDPUBLICKEY_ORIG];
   if(!result && ptr) {
     result = pkp_pin_peer_pubkey(data, connssl->server_cert, ptr);
     if(result)
@@ -2852,7 +2915,7 @@ static CURLcode ossl_connect_step3(struct connectdata *conn, int sockindex)
 
   DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);
 
-  if(conn->ssl_config.sessionid) {
+  if(data->set.general_ssl.sessionid) {
     bool incache;
     SSL_SESSION *our_ssl_sessionid;
     void *old_ssl_sessionid = NULL;
@@ -2864,7 +2927,8 @@ static CURLcode ossl_connect_step3(struct connectdata *conn, int sockindex)
         regardless of its state. */
 
     Curl_ssl_sessionid_lock(conn);
-    incache = !(Curl_ssl_getsessionid(conn, &old_ssl_sessionid, NULL));
+    incache = !(Curl_ssl_getsessionid(conn, &old_ssl_sessionid, NULL,
+                                      sockindex));
     if(incache) {
       if(old_ssl_sessionid != our_ssl_sessionid) {
         infof(data, "old SSL session ID is stale, removing\n");
@@ -2875,7 +2939,7 @@ static CURLcode ossl_connect_step3(struct connectdata *conn, int sockindex)
 
     if(!incache) {
       result = Curl_ssl_addsessionid(conn, our_ssl_sessionid,
-                                      0 /* unknown size */);
+                                      0 /* unknown size */, sockindex);
       if(result) {
         Curl_ssl_sessionid_unlock(conn);
         failf(data, "failed to store ssl session");
@@ -2899,8 +2963,8 @@ static CURLcode ossl_connect_step3(struct connectdata *conn, int sockindex)
    * operations.
    */
 
-  result = servercert(conn, connssl,
-                      (data->set.ssl.verifypeer || data->set.ssl.verifyhost));
+  result = servercert(conn, connssl, (SSL_CONN_CONFIG(verifypeer) ||
+                                      SSL_CONN_CONFIG(verifyhost)));
 
   if(!result)
     connssl->connecting_state = ssl_connect_done;
@@ -2920,7 +2984,7 @@ static CURLcode ossl_connect_common(struct connectdata *conn,
   struct Curl_easy *data = conn->data;
   struct ssl_connect_data *connssl = &conn->ssl[sockindex];
   curl_socket_t sockfd = conn->sock[sockindex];
-  long timeout_ms;
+  time_t timeout_ms;
   int what;
 
   /* check if the connection has already been established */
@@ -3048,7 +3112,10 @@ bool Curl_ossl_data_pending(const struct connectdata *conn, int connindex)
 {
   if(conn->ssl[connindex].handle)
     /* SSL is in use */
-    return (0 != SSL_pending(conn->ssl[connindex].handle)) ? TRUE : FALSE;
+    return (0 != SSL_pending(conn->ssl[connindex].handle) ||
+           (conn->proxy_ssl[connindex].handle &&
+            0 != SSL_pending(conn->proxy_ssl[connindex].handle))) ?
+           TRUE : FALSE;
   else
     return FALSE;
 }
@@ -3093,8 +3160,18 @@ static ssize_t ossl_send(struct connectdata *conn,
       /*  A failure in the SSL library occurred, usually a protocol error.
           The OpenSSL error queue contains more information on the error. */
       sslerror = ERR_get_error();
-      failf(conn->data, "SSL_write() error: %s",
-            ossl_strerror(sslerror, error_buffer, sizeof(error_buffer)));
+      if(ERR_GET_LIB(sslerror) == ERR_LIB_SSL &&
+         ERR_GET_REASON(sslerror) == SSL_R_BIO_NOT_SET &&
+         conn->ssl[sockindex].state == ssl_connection_complete &&
+         conn->proxy_ssl[sockindex].state == ssl_connection_complete) {
+        char ver[120];
+        Curl_ossl_version(ver, 120);
+        failf(conn->data, "Error: %s does not support double SSL tunneling.",
+              ver);
+      }
+      else
+        failf(conn->data, "SSL_write() error: %s",
+              ossl_strerror(sslerror, error_buffer, sizeof(error_buffer)));
       *curlcode = CURLE_SEND_ERROR;
       return -1;
     }
@@ -3178,7 +3255,7 @@ size_t Curl_ossl_version(char *buffer, size_t size)
         sub[0] = 'z';
       }
       else {
-        sub[0]=(char)(((ssleay_value>>4)&0xff) + 'a' -1);
+        sub[0] = (char) (minor_ver + 'a' - 1);
       }
     }
     else
@@ -3199,7 +3276,12 @@ int Curl_ossl_random(struct Curl_easy *data, unsigned char *entropy,
                      size_t length)
 {
   if(data) {
-    Curl_ossl_seed(data); /* Initiate the seed if not already done */
+    if(Curl_ossl_seed(data)) /* Initiate the seed if not already done */
+      return 1; /* couldn't seed for some reason */
+  }
+  else {
+    if(!rand_enough())
+      return 1;
   }
   RAND_bytes(entropy, curlx_uztosi(length));
   return 0; /* 0 as in no problem */