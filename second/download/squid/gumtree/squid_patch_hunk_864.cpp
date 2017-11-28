         return NULL;
     }
 
     return sslContext;
 }
 
-SSL_CTX *
-sslCreateClientContext(const char *certfile, const char *keyfile, int version, const char *cipher, const char *options, const char *flags, const char *CAfile, const char *CApath, const char *CRLfile)
+int Ssl::OpenSSLtoSquidSSLVersion(int sslVersion)
 {
-    int ssl_error;
-    Ssl::ContextMethod method;
-    SSL_CTX * sslContext;
-    long fl = Ssl::parse_flags(flags);
+    if (sslVersion == SSL2_VERSION)
+        return 2;
+    else if (sslVersion == SSL3_VERSION)
+        return 3;
+    else if (sslVersion == TLS1_VERSION)
+        return 4;
+#if OPENSSL_VERSION_NUMBER >= 0x10001000L
+    else if (sslVersion == TLS1_1_VERSION)
+        return 5;
+    else if (sslVersion == TLS1_2_VERSION)
+        return 6;
+#endif
+    else
+        return 1;
+}
 
-    ssl_initialize();
+#if OPENSSL_VERSION_NUMBER < 0x00909000L
+SSL_METHOD *
+#else
+const SSL_METHOD *
+#endif
+Ssl::method(int version)
+{
+    switch (version) {
 
-    if (!keyfile)
-        keyfile = certfile;
+    case 2:
+#if !defined(OPENSSL_NO_SSL2)
+        debugs(83, 5, "Using SSLv2.");
+        return SSLv2_client_method();
+#else
+        debugs(83, DBG_IMPORTANT, "SSLv2 is not available in this Proxy.");
+        return NULL;
+#endif
+        break;
 
-    if (!certfile)
-        certfile = keyfile;
+    case 3:
+#if !defined(OPENSSL_NO_SSL3)
+        debugs(83, 5, "Using SSLv3.");
+        return SSLv3_client_method();
+#else
+        debugs(83, DBG_IMPORTANT, "SSLv3 is not available in this Proxy.");
+        return NULL;
+#endif
+        break;
+
+    case 4:
+        debugs(83, 5, "Using TLSv1.");
+        return TLSv1_client_method();
+        break;
 
+    case 5:
+#if OPENSSL_VERSION_NUMBER >= 0x10001000L  // NP: not sure exactly which sub-version yet.
+        debugs(83, 5, "Using TLSv1.1.");
+        return TLSv1_1_client_method();
+#else
+        debugs(83, DBG_IMPORTANT, "TLSv1.1 is not available in this Proxy.");
+        return NULL;
+#endif
+        break;
+
+    case 6:
+#if OPENSSL_VERSION_NUMBER >= 0x10001000L // NP: not sure exactly which sub-version yet.
+        debugs(83, 5, "Using TLSv1.2");
+        return TLSv1_2_client_method();
+#else
+        debugs(83, DBG_IMPORTANT, "TLSv1.2 is not available in this Proxy.");
+        return NULL;
+#endif
+        break;
+
+    case 1:
+
+    default:
+        debugs(83, 5, "Using SSLv2/SSLv3.");
+        return SSLv23_client_method();
+        break;
+    }
+
+    //Not reached
+    return NULL;
+}
+
+const SSL_METHOD *
+Ssl::serverMethod(int version)
+{
     switch (version) {
 
     case 2:
-#ifndef OPENSSL_NO_SSL2
+#if !defined(OPENSSL_NO_SSL2)
         debugs(83, 5, "Using SSLv2.");
-        method = SSLv2_client_method();
+        return SSLv2_server_method();
 #else
         debugs(83, DBG_IMPORTANT, "SSLv2 is not available in this Proxy.");
         return NULL;
 #endif
         break;
 
     case 3:
+#if !defined(OPENSSL_NO_SSL3)
         debugs(83, 5, "Using SSLv3.");
-        method = SSLv3_client_method();
+        return SSLv3_server_method();
+#else
+        debugs(83, DBG_IMPORTANT, "SSLv3 is not available in this Proxy.");
+        return NULL;
+#endif
         break;
 
     case 4:
         debugs(83, 5, "Using TLSv1.");
-        method = TLSv1_client_method();
+        return TLSv1_server_method();
         break;
 
     case 5:
 #if OPENSSL_VERSION_NUMBER >= 0x10001000L  // NP: not sure exactly which sub-version yet.
         debugs(83, 5, "Using TLSv1.1.");
-        method = TLSv1_1_client_method();
+        return TLSv1_1_server_method();
 #else
         debugs(83, DBG_IMPORTANT, "TLSv1.1 is not available in this Proxy.");
         return NULL;
 #endif
         break;
 
     case 6:
 #if OPENSSL_VERSION_NUMBER >= 0x10001000L // NP: not sure exactly which sub-version yet.
         debugs(83, 5, "Using TLSv1.2");
-        method = TLSv1_2_client_method();
+        return TLSv1_2_server_method();
 #else
         debugs(83, DBG_IMPORTANT, "TLSv1.2 is not available in this Proxy.");
         return NULL;
 #endif
         break;
 
     case 1:
 
     default:
         debugs(83, 5, "Using SSLv2/SSLv3.");
-        method = SSLv23_client_method();
+        return SSLv23_server_method();
         break;
     }
 
+    //Not reached
+    return NULL;
+}
+
+#if defined(TLSEXT_TYPE_next_proto_neg)
+//Dummy next_proto_neg callback
+static int
+ssl_next_proto_cb(SSL *s, unsigned char **out, unsigned char *outlen, const unsigned char *in, unsigned int inlen, void *arg)
+{
+    static const unsigned char supported_protos[] = {8, 'h','t','t', 'p', '/', '1', '.', '1'};
+    (void)SSL_select_next_proto(out, outlen, in, inlen, supported_protos, sizeof(supported_protos));
+    return SSL_TLSEXT_ERR_OK;
+}
+#endif
+
+SSL_CTX *
+sslCreateClientContext(const char *certfile, const char *keyfile, int version, const char *cipher, const char *options, const char *flags, const char *CAfile, const char *CApath, const char *CRLfile)
+{
+    int ssl_error;
+    Ssl::ContextMethod method;
+    SSL_CTX * sslContext;
+    long fl = Ssl::parse_flags(flags);
+
+    ssl_initialize();
+
+    if (!keyfile)
+        keyfile = certfile;
+
+    if (!certfile)
+        certfile = keyfile;
+
+    if (!(method = Ssl::method(version)))
+        return NULL;
+
     sslContext = SSL_CTX_new(method);
 
     if (sslContext == NULL) {
         ssl_error = ERR_get_error();
         fatalf("Failed to allocate SSL context: %s\n",
                ERR_error_string(ssl_error, NULL));
