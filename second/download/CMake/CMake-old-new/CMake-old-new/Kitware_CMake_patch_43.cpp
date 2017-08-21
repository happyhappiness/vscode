@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2017, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -55,7 +55,9 @@
 #include <openssl/ssl.h>
 #include <openssl/rand.h>
 #include <openssl/x509v3.h>
+#ifndef OPENSSL_NO_DSA
 #include <openssl/dsa.h>
+#endif
 #include <openssl/dh.h>
 #include <openssl/err.h>
 #include <openssl/md5.h>
@@ -156,10 +158,56 @@ static unsigned long OpenSSL_version_num(void)
  * Number of bytes to read from the random number seed file. This must be
  * a finite value (because some entropy "files" like /dev/urandom have
  * an infinite length), but must be large enough to provide enough
- * entopy to properly seed OpenSSL's PRNG.
+ * entropy to properly seed OpenSSL's PRNG.
  */
 #define RAND_LOAD_LENGTH 1024
 
+static const char *SSL_ERROR_to_str(int err)
+{
+  switch(err) {
+  case SSL_ERROR_NONE:
+    return "SSL_ERROR_NONE";
+  case SSL_ERROR_SSL:
+    return "SSL_ERROR_SSL";
+  case SSL_ERROR_WANT_READ:
+    return "SSL_ERROR_WANT_READ";
+  case SSL_ERROR_WANT_WRITE:
+    return "SSL_ERROR_WANT_WRITE";
+  case SSL_ERROR_WANT_X509_LOOKUP:
+    return "SSL_ERROR_WANT_X509_LOOKUP";
+  case SSL_ERROR_SYSCALL:
+    return "SSL_ERROR_SYSCALL";
+  case SSL_ERROR_ZERO_RETURN:
+    return "SSL_ERROR_ZERO_RETURN";
+  case SSL_ERROR_WANT_CONNECT:
+    return "SSL_ERROR_WANT_CONNECT";
+  case SSL_ERROR_WANT_ACCEPT:
+    return "SSL_ERROR_WANT_ACCEPT";
+#if defined(SSL_ERROR_WANT_ASYNC)
+  case SSL_ERROR_WANT_ASYNC:
+    return "SSL_ERROR_WANT_ASYNC";
+#endif
+#if defined(SSL_ERROR_WANT_ASYNC_JOB)
+  case SSL_ERROR_WANT_ASYNC_JOB:
+    return "SSL_ERROR_WANT_ASYNC_JOB";
+#endif
+#if defined(SSL_ERROR_WANT_EARLY)
+  case SSL_ERROR_WANT_EARLY:
+    return "SSL_ERROR_WANT_EARLY";
+#endif
+  default:
+    return "SSL_ERROR unknown";
+  }
+}
+
+/* Return error string for last OpenSSL error
+ */
+static char *ossl_strerror(unsigned long error, char *buf, size_t size)
+{
+  ERR_error_string_n(error, buf, size);
+  return buf;
+}
+
 static int passwd_callback(char *buf, int num, int encrypting,
                            void *global_passwd)
 {
@@ -335,6 +383,7 @@ int cert_stuff(struct connectdata *conn,
                char *key_passwd)
 {
   struct Curl_easy *data = conn->data;
+  char error_buffer[256];
 
   int file_type = do_file_type(cert_type);
 
@@ -360,7 +409,8 @@ int cert_stuff(struct connectdata *conn,
               "could not load PEM client certificate, " OSSL_PACKAGE
               " error %s, "
               "(no key found, wrong pass phrase, or wrong file format?)",
-              ERR_error_string(ERR_get_error(), NULL) );
+              ossl_strerror(ERR_get_error(), error_buffer,
+                            sizeof(error_buffer)) );
         return 0;
       }
       break;
@@ -376,7 +426,8 @@ int cert_stuff(struct connectdata *conn,
               "could not load ASN1 client certificate, " OSSL_PACKAGE
               " error %s, "
               "(no key found, wrong pass phrase, or wrong file format?)",
-              ERR_error_string(ERR_get_error(), NULL) );
+              ossl_strerror(ERR_get_error(), error_buffer,
+                            sizeof(error_buffer)) );
         return 0;
       }
       break;
@@ -405,7 +456,8 @@ int cert_stuff(struct connectdata *conn,
                               0, &params, NULL, 1)) {
             failf(data, "ssl engine cannot load client cert with id"
                   " '%s' [%s]", cert_file,
-                  ERR_error_string(ERR_get_error(), NULL));
+                  ossl_strerror(ERR_get_error(), error_buffer,
+                                sizeof(error_buffer)));
             return 0;
           }
 
@@ -461,7 +513,8 @@ int cert_stuff(struct connectdata *conn,
         failf(data,
               "could not parse PKCS12 file, check password, " OSSL_PACKAGE
               " error %s",
-              ERR_error_string(ERR_get_error(), NULL) );
+              ossl_strerror(ERR_get_error(), error_buffer,
+                            sizeof(error_buffer)) );
         PKCS12_free(p12);
         return 0;
       }
@@ -472,7 +525,8 @@ int cert_stuff(struct connectdata *conn,
         failf(data,
               "could not load PKCS12 client certificate, " OSSL_PACKAGE
               " error %s",
-              ERR_error_string(ERR_get_error(), NULL) );
+              ossl_strerror(ERR_get_error(), error_buffer,
+                            sizeof(error_buffer)) );
         goto fail;
       }
 
@@ -493,21 +547,19 @@ int cert_stuff(struct connectdata *conn,
           /*
            * Note that sk_X509_pop() is used below to make sure the cert is
            * removed from the stack properly before getting passed to
-           * SSL_CTX_add_extra_chain_cert(). Previously we used
-           * sk_X509_value() instead, but then we'd clean it in the subsequent
-           * sk_X509_pop_free() call.
+           * SSL_CTX_add_extra_chain_cert(), which takes ownership. Previously
+           * we used sk_X509_value() instead, but then we'd clean it in the
+           * subsequent sk_X509_pop_free() call.
            */
           X509 *x = sk_X509_pop(ca);
-          if(!SSL_CTX_add_extra_chain_cert(ctx, x)) {
+          if(!SSL_CTX_add_client_CA(ctx, x)) {
             X509_free(x);
-            failf(data, "cannot add certificate to certificate chain");
+            failf(data, "cannot add certificate to client CA list");
             goto fail;
           }
-          /* SSL_CTX_add_client_CA() seems to work with either sk_* function,
-           * presumably because it duplicates what we pass to it.
-           */
-          if(!SSL_CTX_add_client_CA(ctx, x)) {
-            failf(data, "cannot add certificate to client CA list");
+          if(!SSL_CTX_add_extra_chain_cert(ctx, x)) {
+            X509_free(x);
+            failf(data, "cannot add certificate to certificate chain");
             goto fail;
           }
         }
@@ -541,6 +593,7 @@ int cert_stuff(struct connectdata *conn,
       if(!key_file)
         /* cert & key can only be in PEM case in the same file */
         key_file=cert_file;
+      /* FALLTHROUGH */
     case SSL_FILETYPE_ASN1:
       if(SSL_CTX_use_PrivateKey_file(ctx, key_file, file_type) != 1) {
         failf(data, "unable to set private key file: '%s' type %s",
@@ -664,17 +717,6 @@ static int x509_name_oneline(X509_NAME *a, char *buf, size_t size)
 #endif
 }
 
-/* Return error string for last OpenSSL error
- */
-static char *ossl_strerror(unsigned long error, char *buf, size_t size)
-{
-  /* OpenSSL 0.9.6 and later has a function named
-     ERR_error_string_n() that takes the size of the buffer as a
-     third argument */
-  ERR_error_string_n(error, buf, size);
-  return buf;
-}
-
 /**
  * Global SSL init
  *
@@ -776,7 +818,7 @@ int Curl_ossl_check_cxn(struct connectdata *conn)
                (RECV_TYPE_ARG3)1, (RECV_TYPE_ARG4)MSG_PEEK);
   if(nread == 0)
     return 0; /* connection has been closed */
-  else if(nread == 1)
+  if(nread == 1)
     return 1; /* connection still in place */
   else if(nread == -1) {
       int err = SOCKERRNO;
@@ -981,8 +1023,10 @@ int Curl_ossl_shutdown(struct connectdata *conn, int sockindex)
         default:
           /* openssl/ssl.h says "look at error stack/return value/errno" */
           sslerror = ERR_get_error();
-          failf(conn->data, OSSL_PACKAGE " SSL read: %s, errno %d",
-                ossl_strerror(sslerror, buf, sizeof(buf)),
+          failf(conn->data, OSSL_PACKAGE " SSL_read on shutdown: %s, errno %d",
+                (sslerror ?
+                 ossl_strerror(sslerror, buf, sizeof(buf)) :
+                 SSL_ERROR_to_str(err)),
                 SOCKERRNO);
           done = 1;
           break;
@@ -1609,7 +1653,7 @@ static void ssl_tls_trace(int direction, int ssl_ver, int content_type,
 #ifdef HAS_NPN
 
 /*
- * in is a list of lenght prefixed strings. this function has to select
+ * in is a list of length prefixed strings. this function has to select
  * the protocol we want to use from the list and write its string into out.
  */
 
@@ -1693,6 +1737,85 @@ get_ssl_version_txt(SSL *ssl)
   return "unknown";
 }
 
+static CURLcode
+set_ssl_version_min_max(long *ctx_options, struct connectdata *conn,
+                        int sockindex)
+{
+#if (OPENSSL_VERSION_NUMBER < 0x1000100FL) || !defined(TLS1_3_VERSION)
+  /* convoluted #if condition just to avoid compiler warnings on unused
+     variable */
+  struct Curl_easy *data = conn->data;
+#endif
+  long ssl_version = SSL_CONN_CONFIG(version);
+  long ssl_version_max = SSL_CONN_CONFIG(version_max);
+
+  if(ssl_version_max == CURL_SSLVERSION_MAX_NONE) {
+    ssl_version_max = ssl_version << 16;
+  }
+
+  switch(ssl_version) {
+    case CURL_SSLVERSION_TLSv1_3:
+#ifdef TLS1_3_VERSION
+    {
+      struct ssl_connect_data *connssl = &conn->ssl[sockindex];
+      SSL_CTX_set_max_proto_version(connssl->ctx, TLS1_3_VERSION);
+      *ctx_options |= SSL_OP_NO_TLSv1_2;
+    }
+#else
+      (void)sockindex;
+      failf(data, OSSL_PACKAGE " was built without TLS 1.3 support");
+      return CURLE_NOT_BUILT_IN;
+#endif
+    case CURL_SSLVERSION_TLSv1_2:
+#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
+      *ctx_options |= SSL_OP_NO_TLSv1_1;
+#else
+      failf(data, OSSL_PACKAGE " was built without TLS 1.2 support");
+      return CURLE_NOT_BUILT_IN;
+#endif
+      /* FALLTHROUGH */
+    case CURL_SSLVERSION_TLSv1_1:
+#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
+      *ctx_options |= SSL_OP_NO_TLSv1;
+#else
+      failf(data, OSSL_PACKAGE " was built without TLS 1.1 support");
+      return CURLE_NOT_BUILT_IN;
+#endif
+      /* FALLTHROUGH */
+    case CURL_SSLVERSION_TLSv1_0:
+      *ctx_options |= SSL_OP_NO_SSLv2;
+      *ctx_options |= SSL_OP_NO_SSLv3;
+      break;
+  }
+
+  switch(ssl_version_max) {
+    case CURL_SSLVERSION_MAX_TLSv1_0:
+#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
+      *ctx_options |= SSL_OP_NO_TLSv1_1;
+#endif
+      /* FALLTHROUGH */
+    case CURL_SSLVERSION_MAX_TLSv1_1:
+#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
+      *ctx_options |= SSL_OP_NO_TLSv1_2;
+#endif
+      /* FALLTHROUGH */
+    case CURL_SSLVERSION_MAX_TLSv1_2:
+    case CURL_SSLVERSION_MAX_DEFAULT:
+#ifdef TLS1_3_VERSION
+      *ctx_options |= SSL_OP_NO_TLSv1_3;
+#endif
+      break;
+    case CURL_SSLVERSION_MAX_TLSv1_3:
+#ifdef TLS1_3_VERSION
+      break;
+#else
+      failf(data, OSSL_PACKAGE " was built without TLS 1.3 support");
+      return CURLE_NOT_BUILT_IN;
+#endif
+  }
+  return CURLE_OK;
+}
+
 static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
 {
   CURLcode result = CURLE_OK;
@@ -1702,9 +1825,11 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
   X509_LOOKUP *lookup = NULL;
   curl_socket_t sockfd = conn->sock[sockindex];
   struct ssl_connect_data *connssl = &conn->ssl[sockindex];
-  long ctx_options;
+  long ctx_options = 0;
 #ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
   bool sni;
+  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
+    conn->host.name;
 #ifdef ENABLE_IPV6
   struct in6_addr addr;
 #else
@@ -1723,8 +1848,7 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
   const char * const ssl_capath = SSL_CONN_CONFIG(CApath);
   const bool verifypeer = SSL_CONN_CONFIG(verifypeer);
   const char * const ssl_crlfile = SSL_SET_OPTION(CRLfile);
-  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
-    conn->host.name;
+  char error_buffer[256];
 
   DEBUGASSERT(ssl_connect_1 == connssl->connecting_state);
 
@@ -1790,7 +1914,7 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
 
   if(!connssl->ctx) {
     failf(data, "SSL: couldn't create a context: %s",
-          ERR_error_string(ERR_peek_error(), NULL));
+          ossl_strerror(ERR_peek_error(), error_buffer, sizeof(error_buffer)));
     return CURLE_OUT_OF_MEMORY;
   }
 
@@ -1889,60 +2013,13 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
     break;
 
   case CURL_SSLVERSION_TLSv1_0:
-    ctx_options |= SSL_OP_NO_SSLv2;
-    ctx_options |= SSL_OP_NO_SSLv3;
-#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
-    ctx_options |= SSL_OP_NO_TLSv1_1;
-    ctx_options |= SSL_OP_NO_TLSv1_2;
-#ifdef TLS1_3_VERSION
-    ctx_options |= SSL_OP_NO_TLSv1_3;
-#endif
-#endif
-    break;
-
   case CURL_SSLVERSION_TLSv1_1:
-#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
-    ctx_options |= SSL_OP_NO_SSLv2;
-    ctx_options |= SSL_OP_NO_SSLv3;
-    ctx_options |= SSL_OP_NO_TLSv1;
-    ctx_options |= SSL_OP_NO_TLSv1_2;
-#ifdef TLS1_3_VERSION
-    ctx_options |= SSL_OP_NO_TLSv1_3;
-#endif
-    break;
-#else
-    failf(data, OSSL_PACKAGE " was built without TLS 1.1 support");
-    return CURLE_NOT_BUILT_IN;
-#endif
-
   case CURL_SSLVERSION_TLSv1_2:
-#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
-    ctx_options |= SSL_OP_NO_SSLv2;
-    ctx_options |= SSL_OP_NO_SSLv3;
-    ctx_options |= SSL_OP_NO_TLSv1;
-    ctx_options |= SSL_OP_NO_TLSv1_1;
-#ifdef TLS1_3_VERSION
-    ctx_options |= SSL_OP_NO_TLSv1_3;
-#endif
-    break;
-#else
-    failf(data, OSSL_PACKAGE " was built without TLS 1.2 support");
-    return CURLE_NOT_BUILT_IN;
-#endif
-
   case CURL_SSLVERSION_TLSv1_3:
-#ifdef TLS1_3_VERSION
-    SSL_CTX_set_max_proto_version(connssl->ctx, TLS1_3_VERSION);
-    ctx_options |= SSL_OP_NO_SSLv2;
-    ctx_options |= SSL_OP_NO_SSLv3;
-    ctx_options |= SSL_OP_NO_TLSv1;
-    ctx_options |= SSL_OP_NO_TLSv1_1;
-    ctx_options |= SSL_OP_NO_TLSv1_2;
+    result = set_ssl_version_min_max(&ctx_options, conn, sockindex);
+    if(result != CURLE_OK)
+       return result;
     break;
-#else
-    failf(data, OSSL_PACKAGE " was built without TLS 1.3 support");
-    return CURLE_NOT_BUILT_IN;
-#endif
 
   case CURL_SSLVERSION_SSLv2:
 #ifndef OPENSSL_NO_SSL2
@@ -2056,12 +2133,10 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
               ssl_capath ? ssl_capath : "none");
         return CURLE_SSL_CACERT_BADFILE;
       }
-      else {
-        /* Just continue with a warning if no strict  certificate verification
-           is required. */
-        infof(data, "error setting certificate verify locations,"
-              " continuing anyway:\n");
-      }
+      /* Just continue with a warning if no strict  certificate verification
+         is required. */
+      infof(data, "error setting certificate verify locations,"
+            " continuing anyway:\n");
     }
     else {
       /* Everything is fine. */
@@ -2091,12 +2166,11 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
       failf(data, "error loading CRL file: %s", ssl_crlfile);
       return CURLE_SSL_CRL_BADFILE;
     }
-    else {
-      /* Everything is fine. */
-      infof(data, "successfully load CRL file:\n");
-      X509_STORE_set_flags(SSL_CTX_get_cert_store(connssl->ctx),
-                           X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
-    }
+    /* Everything is fine. */
+    infof(data, "successfully load CRL file:\n");
+    X509_STORE_set_flags(SSL_CTX_get_cert_store(connssl->ctx),
+                         X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
+
     infof(data, "  CRLfile: %s\n", ssl_crlfile);
   }
 
@@ -2161,7 +2235,7 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
 #endif
 
   /* Check if there's a cached ID we can/should use here! */
-  if(data->set.general_ssl.sessionid) {
+  if(SSL_SET_OPTION(primary.sessionid)) {
     void *ssl_sessionid = NULL;
 
     Curl_ssl_sessionid_lock(conn);
@@ -2170,7 +2244,8 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
       if(!SSL_set_session(connssl->handle, ssl_sessionid)) {
         Curl_ssl_sessionid_unlock(conn);
         failf(data, "SSL: SSL_set_session failed: %s",
-              ERR_error_string(ERR_get_error(), NULL));
+              ossl_strerror(ERR_get_error(), error_buffer,
+                            sizeof(error_buffer)));
         return CURLE_SSL_CONNECT_ERROR;
       }
       /* Informational message */
@@ -2190,7 +2265,7 @@ static CURLcode ossl_connect_step1(struct connectdata *conn, int sockindex)
   else if(!SSL_set_fd(connssl->handle, (int)sockfd)) {
     /* pass the raw socket into the SSL layers */
     failf(data, "SSL: SSL_set_fd failed: %s",
-          ERR_error_string(ERR_get_error(), NULL));
+          ossl_strerror(ERR_get_error(), error_buffer, sizeof(error_buffer)));
     return CURLE_SSL_CONNECT_ERROR;
   }
 
@@ -2224,15 +2299,14 @@ static CURLcode ossl_connect_step2(struct connectdata *conn, int sockindex)
       connssl->connecting_state = ssl_connect_2_reading;
       return CURLE_OK;
     }
-    else if(SSL_ERROR_WANT_WRITE == detail) {
+    if(SSL_ERROR_WANT_WRITE == detail) {
       connssl->connecting_state = ssl_connect_2_writing;
       return CURLE_OK;
     }
     else {
       /* untreated error */
       unsigned long errdetail;
-      char error_buffer[256]=""; /* OpenSSL documents that this must be at
-                                    least 256 bytes long. */
+      char error_buffer[256]="";
       CURLcode result;
       long lerr;
       int lib;
@@ -2280,8 +2354,8 @@ static CURLcode ossl_connect_step2(struct connectdata *conn, int sockindex)
         const char * const hostname = SSL_IS_PROXY() ?
           conn->http_proxy.host.name : conn->host.name;
         const long int port = SSL_IS_PROXY() ? conn->port : conn->remote_port;
-        failf(data, "Unknown SSL protocol error in connection to %s:%ld ",
-              hostname, port);
+        failf(data, OSSL_PACKAGE " SSL_connect: %s in connection to %s:%ld ",
+              SSL_ERROR_to_str(detail), hostname, port);
         return result;
       }
 
@@ -2554,44 +2628,25 @@ static CURLcode get_cert_chain(struct connectdata *conn,
         {
           const BIGNUM *n;
           const BIGNUM *e;
-          const BIGNUM *d;
-          const BIGNUM *p;
-          const BIGNUM *q;
-          const BIGNUM *dmp1;
-          const BIGNUM *dmq1;
-          const BIGNUM *iqmp;
 
-          RSA_get0_key(rsa, &n, &e, &d);
-          RSA_get0_factors(rsa, &p, &q);
-          RSA_get0_crt_params(rsa, &dmp1, &dmq1, &iqmp);
+          RSA_get0_key(rsa, &n, &e, NULL);
           BN_print(mem, n);
           push_certinfo("RSA Public Key", i);
           print_pubkey_BN(rsa, n, i);
           print_pubkey_BN(rsa, e, i);
-          print_pubkey_BN(rsa, d, i);
-          print_pubkey_BN(rsa, p, i);
-          print_pubkey_BN(rsa, q, i);
-          print_pubkey_BN(rsa, dmp1, i);
-          print_pubkey_BN(rsa, dmq1, i);
-          print_pubkey_BN(rsa, iqmp, i);
         }
 #else
         BIO_printf(mem, "%d", BN_num_bits(rsa->n));
         push_certinfo("RSA Public Key", i);
         print_pubkey_BN(rsa, n, i);
         print_pubkey_BN(rsa, e, i);
-        print_pubkey_BN(rsa, d, i);
-        print_pubkey_BN(rsa, p, i);
-        print_pubkey_BN(rsa, q, i);
-        print_pubkey_BN(rsa, dmp1, i);
-        print_pubkey_BN(rsa, dmq1, i);
-        print_pubkey_BN(rsa, iqmp, i);
 #endif
 
         break;
       }
       case EVP_PKEY_DSA:
       {
+#ifndef OPENSSL_NO_DSA
         DSA *dsa;
 #ifdef HAVE_OPAQUE_EVP_PKEY
         dsa = EVP_PKEY_get0_DSA(pubkey);
@@ -2603,25 +2658,23 @@ static CURLcode get_cert_chain(struct connectdata *conn,
           const BIGNUM *p;
           const BIGNUM *q;
           const BIGNUM *g;
-          const BIGNUM *priv_key;
           const BIGNUM *pub_key;
 
           DSA_get0_pqg(dsa, &p, &q, &g);
-          DSA_get0_key(dsa, &pub_key, &priv_key);
+          DSA_get0_key(dsa, &pub_key, NULL);
 
           print_pubkey_BN(dsa, p, i);
           print_pubkey_BN(dsa, q, i);
           print_pubkey_BN(dsa, g, i);
-          print_pubkey_BN(dsa, priv_key, i);
           print_pubkey_BN(dsa, pub_key, i);
         }
 #else
         print_pubkey_BN(dsa, p, i);
         print_pubkey_BN(dsa, q, i);
         print_pubkey_BN(dsa, g, i);
-        print_pubkey_BN(dsa, priv_key, i);
         print_pubkey_BN(dsa, pub_key, i);
 #endif
+#endif /* !OPENSSL_NO_DSA */
         break;
       }
       case EVP_PKEY_DH:
@@ -2637,20 +2690,17 @@ static CURLcode get_cert_chain(struct connectdata *conn,
           const BIGNUM *p;
           const BIGNUM *q;
           const BIGNUM *g;
-          const BIGNUM *priv_key;
           const BIGNUM *pub_key;
           DH_get0_pqg(dh, &p, &q, &g);
-          DH_get0_key(dh, &pub_key, &priv_key);
+          DH_get0_key(dh, &pub_key, NULL);
           print_pubkey_BN(dh, p, i);
           print_pubkey_BN(dh, q, i);
           print_pubkey_BN(dh, g, i);
-          print_pubkey_BN(dh, priv_key, i);
           print_pubkey_BN(dh, pub_key, i);
        }
 #else
         print_pubkey_BN(dh, p, i);
         print_pubkey_BN(dh, g, i);
-        print_pubkey_BN(dh, priv_key, i);
         print_pubkey_BN(dh, pub_key, i);
 #endif
         break;
@@ -2915,7 +2965,7 @@ static CURLcode ossl_connect_step3(struct connectdata *conn, int sockindex)
 
   DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);
 
-  if(data->set.general_ssl.sessionid) {
+  if(SSL_SET_OPTION(primary.sessionid)) {
     bool incache;
     SSL_SESSION *our_ssl_sessionid;
     void *old_ssl_sessionid = NULL;
@@ -3037,16 +3087,14 @@ static CURLcode ossl_connect_common(struct connectdata *conn,
         failf(data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
         return CURLE_SSL_CONNECT_ERROR;
       }
-      else if(0 == what) {
+      if(0 == what) {
         if(nonblocking) {
           *done = FALSE;
           return CURLE_OK;
         }
-        else {
-          /* timeout */
-          failf(data, "SSL connection timeout");
-          return CURLE_OPERATION_TIMEDOUT;
-        }
+        /* timeout */
+        failf(data, "SSL connection timeout");
+        return CURLE_OPERATION_TIMEDOUT;
       }
       /* socket is readable or writable */
     }
@@ -3116,8 +3164,7 @@ bool Curl_ossl_data_pending(const struct connectdata *conn, int connindex)
            (conn->proxy_ssl[connindex].handle &&
             0 != SSL_pending(conn->proxy_ssl[connindex].handle))) ?
            TRUE : FALSE;
-  else
-    return FALSE;
+  return FALSE;
 }
 
 static ssize_t ossl_send(struct connectdata *conn,
@@ -3129,8 +3176,7 @@ static ssize_t ossl_send(struct connectdata *conn,
   /* SSL_write() is said to return 'int' while write() and send() returns
      'size_t' */
   int err;
-  char error_buffer[256]; /* OpenSSL documents that this must be at least 256
-                             bytes long. */
+  char error_buffer[256];
   unsigned long sslerror;
   int memlen;
   int rc;
@@ -3176,7 +3222,8 @@ static ssize_t ossl_send(struct connectdata *conn,
       return -1;
     }
     /* a true error */
-    failf(conn->data, "SSL_write() return error %d", err);
+    failf(conn->data, OSSL_PACKAGE " SSL_write: %s, errno %d",
+          SSL_ERROR_to_str(err), SOCKERRNO);
     *curlcode = CURLE_SEND_ERROR;
     return -1;
   }
@@ -3190,8 +3237,7 @@ static ssize_t ossl_recv(struct connectdata *conn, /* connection data */
                          size_t buffersize,        /* max amount to read */
                          CURLcode *curlcode)
 {
-  char error_buffer[256]; /* OpenSSL documents that this must be at
-                             least 256 bytes long. */
+  char error_buffer[256];
   unsigned long sslerror;
   ssize_t nread;
   int buffsize;
@@ -3221,8 +3267,10 @@ static ssize_t ossl_recv(struct connectdata *conn, /* connection data */
       if((nread < 0) || sslerror) {
         /* If the return code was negative or there actually is an error in the
            queue */
-        failf(conn->data, "SSL read: %s, errno %d",
-              ossl_strerror(sslerror, error_buffer, sizeof(error_buffer)),
+        failf(conn->data, OSSL_PACKAGE " SSL_read: %s, errno %d",
+              (sslerror ?
+               ossl_strerror(sslerror, error_buffer, sizeof(error_buffer)) :
+               SSL_ERROR_to_str(err)),
               SOCKERRNO);
         *curlcode = CURLE_RECV_ERROR;
         return -1;
@@ -3272,19 +3320,21 @@ size_t Curl_ossl_version(char *buffer, size_t size)
 }
 
 /* can be called with data == NULL */
-int Curl_ossl_random(struct Curl_easy *data, unsigned char *entropy,
-                     size_t length)
+CURLcode Curl_ossl_random(struct Curl_easy *data, unsigned char *entropy,
+                          size_t length)
 {
+  int rc;
   if(data) {
     if(Curl_ossl_seed(data)) /* Initiate the seed if not already done */
-      return 1; /* couldn't seed for some reason */
+      return CURLE_FAILED_INIT; /* couldn't seed for some reason */
   }
   else {
     if(!rand_enough())
-      return 1;
+      return CURLE_FAILED_INIT;
   }
-  RAND_bytes(entropy, curlx_uztosi(length));
-  return 0; /* 0 as in no problem */
+  /* RAND_bytes() returns 1 on success, 0 otherwise.  */
+  rc = RAND_bytes(entropy, curlx_uztosi(length));
+  return (rc == 1 ? CURLE_OK : CURLE_FAILED_INIT);
 }
 
 void Curl_ossl_md5sum(unsigned char *tmp, /* input */