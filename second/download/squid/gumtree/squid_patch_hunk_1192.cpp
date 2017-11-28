               int, long, void *)
 {
     SBuf  *buf = static_cast <SBuf *>(ptr);
     delete buf;
 }
 
-/// \ingroup ServerProtocolSSLInternal
-static void
-ssl_initialize(void)
+void
+Ssl::Initialize(void)
 {
     static bool initialized = false;
     if (initialized)
         return;
     initialized = true;
 
     SSL_load_error_strings();
     SSLeay_add_ssl_algorithms();
 
 #if HAVE_OPENSSL_ENGINE_H
-    if (Config.SSL.ssl_engine) {
-        ENGINE_load_builtin_engines();
+    if (::Config.SSL.ssl_engine) {
         ENGINE *e;
-        if (!(e = ENGINE_by_id(Config.SSL.ssl_engine)))
-            fatalf("Unable to find SSL engine '%s'\n", Config.SSL.ssl_engine);
+        if (!(e = ENGINE_by_id(::Config.SSL.ssl_engine)))
+            fatalf("Unable to find SSL engine '%s'\n", ::Config.SSL.ssl_engine);
 
         if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
-            int ssl_error = ERR_get_error();
-            fatalf("Failed to initialise SSL engine: %s\n", ERR_error_string(ssl_error, NULL));
+            const int ssl_error = ERR_get_error();
+            fatalf("Failed to initialise SSL engine: %s\n", Security::ErrorString(ssl_error));
         }
     }
 #else
-    if (Config.SSL.ssl_engine)
+    if (::Config.SSL.ssl_engine)
         fatalf("Your OpenSSL has no SSL engine support\n");
 #endif
 
-    const char *defName = Config.SSL.certSignHash ? Config.SSL.certSignHash : SQUID_SSL_SIGN_HASH_IF_NONE;
+    const char *defName = ::Config.SSL.certSignHash ? ::Config.SSL.certSignHash : SQUID_SSL_SIGN_HASH_IF_NONE;
     Ssl::DefaultSignHash = EVP_get_digestbyname(defName);
     if (!Ssl::DefaultSignHash)
         fatalf("Sign hash '%s' is not supported\n", defName);
 
     ssl_ex_index_server = SSL_get_ex_new_index(0, (void *) "server", NULL, NULL, ssl_free_SBuf);
     ssl_ctx_ex_index_dont_verify_domain = SSL_CTX_get_ex_new_index(0, (void *) "dont_verify_domain", NULL, NULL, NULL);
     ssl_ex_index_cert_error_check = SSL_get_ex_new_index(0, (void *) "cert_error_check", NULL, &ssl_dupAclChecklist, &ssl_freeAclChecklist);
     ssl_ex_index_ssl_error_detail = SSL_get_ex_new_index(0, (void *) "ssl_error_detail", NULL, NULL, &ssl_free_ErrorDetail);
     ssl_ex_index_ssl_peeked_cert  = SSL_get_ex_new_index(0, (void *) "ssl_peeked_cert", NULL, NULL, &ssl_free_X509);
     ssl_ex_index_ssl_errors =  SSL_get_ex_new_index(0, (void *) "ssl_errors", NULL, NULL, &ssl_free_SslErrors);
     ssl_ex_index_ssl_cert_chain = SSL_get_ex_new_index(0, (void *) "ssl_cert_chain", NULL, NULL, &ssl_free_CertChain);
     ssl_ex_index_ssl_validation_counter = SSL_get_ex_new_index(0, (void *) "ssl_validation_counter", NULL, NULL, &ssl_free_int);
-}
-
-/// \ingroup ServerProtocolSSLInternal
-static int
-ssl_load_crl(SSL_CTX *sslContext, const char *CRLfile)
-{
-    X509_STORE *st = SSL_CTX_get_cert_store(sslContext);
-    X509_CRL *crl;
-    BIO *in = BIO_new_file(CRLfile, "r");
-    int count = 0;
-
-    if (!in) {
-        debugs(83, 2, "WARNING: Failed to open CRL file '" << CRLfile << "'");
-        return 0;
-    }
-
-    while ((crl = PEM_read_bio_X509_CRL(in,NULL,NULL,NULL))) {
-        if (!X509_STORE_add_crl(st, crl))
-            debugs(83, 2, "WARNING: Failed to add CRL from file '" << CRLfile << "'");
-        else
-            ++count;
-
-        X509_CRL_free(crl);
-    }
-
-    BIO_free(in);
-    return count;
-}
-
-STACK_OF(X509_CRL) *
-Ssl::loadCrl(const char *CRLFile, long &flags)
-{
-    X509_CRL *crl;
-    BIO *in = BIO_new_file(CRLFile, "r");
-    if (!in) {
-        debugs(83, 2, "WARNING: Failed to open CRL file '" << CRLFile << "'");
-        return NULL;
-    }
-
-    STACK_OF(X509_CRL) *CRLs = sk_X509_CRL_new_null();
-    if (!CRLs) {
-        debugs(83, 2, "WARNING: Failed to allocate X509_CRL stack  to load file '" << CRLFile << "'");
-        return NULL;
-    }
-
-    int count = 0;
-    while ((crl = PEM_read_bio_X509_CRL(in,NULL,NULL,NULL))) {
-        if (!sk_X509_CRL_push(CRLs, crl))
-            debugs(83, 2, "WARNING: Failed to add CRL from file '" << CRLFile << "'");
-        else
-            ++count;
-    }
-    BIO_free(in);
-
-    if (count)
-        flags |= SSL_FLAG_VERIFY_CRL;
-
-    return CRLs;
-}
-
-DH *
-Ssl::readDHParams(const char *dhfile)
-{
-    FILE *in = fopen(dhfile, "r");
-    DH *dh = NULL;
-    int codes;
-
-    if (in) {
-        dh = PEM_read_DHparams(in, NULL, NULL, NULL);
-        fclose(in);
-    }
-
-    if (!dh)
-        debugs(83, DBG_IMPORTANT, "WARNING: Failed to read DH parameters '" << dhfile << "'");
-    else if (dh && DH_check(dh, &codes) == 0) {
-        if (codes) {
-            debugs(83, DBG_IMPORTANT, "WARNING: Failed to verify DH parameters '" << dhfile  << "' (" << std::hex << codes  << ")");
-            DH_free(dh);
-            dh = NULL;
-        }
-    }
-    return dh;
+    ssl_ex_index_ssl_untrusted_chain = SSL_get_ex_new_index(0, (void *) "ssl_untrusted_chain", NULL, NULL, &ssl_free_CertChain);
 }
 
 static bool
-configureSslEECDH(SSL_CTX *sslContext, const char *curve)
-{
-#if OPENSSL_VERSION_NUMBER >= 0x0090800fL && !defined(OPENSSL_NO_ECDH)
-    int nid = OBJ_sn2nid(curve);
-    if (!nid) {
-        debugs(83, DBG_CRITICAL, "ERROR: Unknown EECDH curve '" << curve << "'");
-        return false;
-    }
-
-    EC_KEY *ecdh = EC_KEY_new_by_curve_name(nid);
-    if (ecdh == NULL)
-        return false;
-
-    const bool ok = SSL_CTX_set_tmp_ecdh(sslContext, ecdh) != 0;
-    EC_KEY_free(ecdh);
-    return ok;
-#else
-    debugs(83, DBG_CRITICAL, "ERROR: EECDH is not available in this build. Please link against OpenSSL>=0.9.8 and ensure OPENSSL_NO_ECDH is not set.");
-    return false;
-#endif
-}
-
-static bool
-configureSslContext(SSL_CTX *sslContext, AnyP::PortCfg &port)
+configureSslContext(Security::ContextPointer &ctx, AnyP::PortCfg &port)
 {
     int ssl_error;
-    SSL_CTX_set_options(sslContext, port.sslOptions);
+    SSL_CTX_set_options(ctx.get(), port.secure.parsedOptions);
 
     if (port.sslContextSessionId)
-        SSL_CTX_set_session_id_context(sslContext, (const unsigned char *)port.sslContextSessionId, strlen(port.sslContextSessionId));
+        SSL_CTX_set_session_id_context(ctx.get(), (const unsigned char *)port.sslContextSessionId, strlen(port.sslContextSessionId));
 
-    if (port.sslContextFlags & SSL_FLAG_NO_SESSION_REUSE) {
-        SSL_CTX_set_session_cache_mode(sslContext, SSL_SESS_CACHE_OFF);
+    if (port.secure.parsedFlags & SSL_FLAG_NO_SESSION_REUSE) {
+        SSL_CTX_set_session_cache_mode(ctx.get(), SSL_SESS_CACHE_OFF);
     }
 
     if (Config.SSL.unclean_shutdown) {
         debugs(83, 5, "Enabling quiet SSL shutdowns (RFC violation).");
 
-        SSL_CTX_set_quiet_shutdown(sslContext, 1);
-    }
-
-    if (port.cipher) {
-        debugs(83, 5, "Using chiper suite " << port.cipher << ".");
-
-        if (!SSL_CTX_set_cipher_list(sslContext, port.cipher)) {
-            ssl_error = ERR_get_error();
-            debugs(83, DBG_CRITICAL, "ERROR: Failed to set SSL cipher suite '" << port.cipher << "': " << ERR_error_string(ssl_error, NULL));
-            return false;
-        }
+        SSL_CTX_set_quiet_shutdown(ctx.get(), 1);
     }
 
-    debugs(83, 9, "Setting RSA key generation callback.");
-    SSL_CTX_set_tmp_rsa_callback(sslContext, ssl_temp_rsa_cb);
+    if (!port.secure.sslCipher.isEmpty()) {
+        debugs(83, 5, "Using chiper suite " << port.secure.sslCipher << ".");
 
-    if (port.eecdhCurve) {
-        debugs(83, 9, "Setting Ephemeral ECDH curve to " << port.eecdhCurve << ".");
-
-        if (!configureSslEECDH(sslContext, port.eecdhCurve)) {
+        if (!SSL_CTX_set_cipher_list(ctx.get(), port.secure.sslCipher.c_str())) {
             ssl_error = ERR_get_error();
-            debugs(83, DBG_CRITICAL, "ERROR: Unable to configure Ephemeral ECDH: " << ERR_error_string(ssl_error, NULL));
+            debugs(83, DBG_CRITICAL, "ERROR: Failed to set SSL cipher suite '" << port.secure.sslCipher << "': " << Security::ErrorString(ssl_error));
             return false;
         }
     }
 
-    debugs(83, 9, "Setting CA certificate locations.");
-
-    const char *cafile = port.cafile ? port.cafile : port.clientca;
-    if ((cafile || port.capath) && !SSL_CTX_load_verify_locations(sslContext, cafile, port.capath)) {
-        ssl_error = ERR_get_error();
-        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting CA certificate locations: " << ERR_error_string(ssl_error, NULL));
-    }
+    maybeSetupRsaCallback(ctx);
 
-    if (!(port.sslContextFlags & SSL_FLAG_NO_DEFAULT_CA) &&
-            !SSL_CTX_set_default_verify_paths(sslContext)) {
-        ssl_error = ERR_get_error();
-        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting default CA certificate location: " << ERR_error_string(ssl_error, NULL));
-    }
+    port.secure.updateContextEecdh(ctx);
+    port.secure.updateContextCa(ctx);
 
     if (port.clientCA.get()) {
         ERR_clear_error();
         if (STACK_OF(X509_NAME) *clientca = SSL_dup_CA_list(port.clientCA.get())) {
-            SSL_CTX_set_client_CA_list(sslContext, clientca);
+            SSL_CTX_set_client_CA_list(ctx.get(), clientca);
         } else {
             ssl_error = ERR_get_error();
-            debugs(83, DBG_CRITICAL, "ERROR: Failed to dupe the client CA list: " << ERR_error_string(ssl_error, NULL));
+            debugs(83, DBG_CRITICAL, "ERROR: Failed to dupe the client CA list: " << Security::ErrorString(ssl_error));
             return false;
         }
 
-        if (port.sslContextFlags & SSL_FLAG_DELAYED_AUTH) {
+        if (port.secure.parsedFlags & SSL_FLAG_DELAYED_AUTH) {
             debugs(83, 9, "Not requesting client certificates until acl processing requires one");
-            SSL_CTX_set_verify(sslContext, SSL_VERIFY_NONE, NULL);
+            SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_NONE, NULL);
         } else {
             debugs(83, 9, "Requiring client certificates.");
-            SSL_CTX_set_verify(sslContext, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
-        }
-
-        if (port.clientVerifyCrls.get()) {
-            X509_STORE *st = SSL_CTX_get_cert_store(sslContext);
-            for (int i = 0; i < sk_X509_CRL_num(port.clientVerifyCrls.get()); ++i) {
-                X509_CRL *crl = sk_X509_CRL_value(port.clientVerifyCrls.get(), i);
-                if (!X509_STORE_add_crl(st, crl))
-                    debugs(83, 2, "WARNING: Failed to add CRL");
-            }
+            SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
         }
 
-#if X509_V_FLAG_CRL_CHECK
-        if (port.sslContextFlags & SSL_FLAG_VERIFY_CRL_ALL)
-            X509_STORE_set_flags(SSL_CTX_get_cert_store(sslContext), X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
-        else if (port.sslContextFlags & SSL_FLAG_VERIFY_CRL)
-            X509_STORE_set_flags(SSL_CTX_get_cert_store(sslContext), X509_V_FLAG_CRL_CHECK);
-#endif
+        port.secure.updateContextCrl(ctx);
 
     } else {
         debugs(83, 9, "Not requiring any client certificates");
-        SSL_CTX_set_verify(sslContext, SSL_VERIFY_NONE, NULL);
-    }
-
-    if (port.dhParams.get()) {
-        SSL_CTX_set_tmp_dh(sslContext, port.dhParams.get());
+        SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_NONE, NULL);
     }
 
-    if (port.sslContextFlags & SSL_FLAG_DONT_VERIFY_DOMAIN)
-        SSL_CTX_set_ex_data(sslContext, ssl_ctx_ex_index_dont_verify_domain, (void *) -1);
+    if (port.secure.parsedFlags & SSL_FLAG_DONT_VERIFY_DOMAIN)
+        SSL_CTX_set_ex_data(ctx.get(), ssl_ctx_ex_index_dont_verify_domain, (void *) -1);
 
-    setSessionCallbacks(sslContext);
+    Ssl::SetSessionCallbacks(ctx);
 
     return true;
 }
 
-SSL_CTX *
-sslCreateServerContext(AnyP::PortCfg &port)
-{
-    int ssl_error;
-    SSL_CTX *sslContext;
-    const char *keyfile, *certfile;
-    certfile = port.cert;
-    keyfile = port.key;
-
-    ssl_initialize();
-
-    if (!keyfile)
-        keyfile = certfile;
-
-    if (!certfile)
-        certfile = keyfile;
-
-    sslContext = SSL_CTX_new(port.contextMethod);
-
-    if (sslContext == NULL) {
-        ssl_error = ERR_get_error();
-        debugs(83, DBG_CRITICAL, "ERROR: Failed to allocate SSL context: " << ERR_error_string(ssl_error, NULL));
-        return NULL;
-    }
-
-    if (!SSL_CTX_use_certificate(sslContext, port.signingCert.get())) {
-        ssl_error = ERR_get_error();
-        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL certificate '" << certfile << "': " << ERR_error_string(ssl_error, NULL));
-        SSL_CTX_free(sslContext);
-        return NULL;
-    }
-
-    if (!SSL_CTX_use_PrivateKey(sslContext, port.signPkey.get())) {
-        ssl_error = ERR_get_error();
-        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL private key '" << keyfile << "': " << ERR_error_string(ssl_error, NULL));
-        SSL_CTX_free(sslContext);
-        return NULL;
-    }
-
-    Ssl::addChainToSslContext(sslContext, port.certsToChain.get());
-
-    /* Alternate code;
-        debugs(83, DBG_IMPORTANT, "Using certificate in " << certfile);
-
-        if (!SSL_CTX_use_certificate_chain_file(sslContext, certfile)) {
-            ssl_error = ERR_get_error();
-            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL certificate '" << certfile << "': " << ERR_error_string(ssl_error, NULL));
-            SSL_CTX_free(sslContext);
-            return NULL;
-        }
-
-        debugs(83, DBG_IMPORTANT, "Using private key in " << keyfile);
-        ssl_ask_password(sslContext, keyfile);
-
-        if (!SSL_CTX_use_PrivateKey_file(sslContext, keyfile, SSL_FILETYPE_PEM)) {
-            ssl_error = ERR_get_error();
-            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL private key '" << keyfile << "': " << ERR_error_string(ssl_error, NULL));
-            SSL_CTX_free(sslContext);
-            return NULL;
-        }
-
-        debugs(83, 5, "Comparing private and public SSL keys.");
-
-        if (!SSL_CTX_check_private_key(sslContext)) {
-            ssl_error = ERR_get_error();
-            debugs(83, DBG_CRITICAL, "ERROR: SSL private key '" << certfile << "' does not match public key '" <<
-                   keyfile << "': " << ERR_error_string(ssl_error, NULL));
-            SSL_CTX_free(sslContext);
-            return NULL;
-        }
-    */
-
-    if (!configureSslContext(sslContext, port)) {
-        debugs(83, DBG_CRITICAL, "ERROR: Configuring static SSL context");
-        SSL_CTX_free(sslContext);
-        return NULL;
-    }
-
-    return sslContext;
-}
-
-int Ssl::OpenSSLtoSquidSSLVersion(int sslVersion)
-{
-    if (sslVersion == SSL2_VERSION)
-        return 2;
-    else if (sslVersion == SSL3_VERSION)
-        return 3;
-    else if (sslVersion == TLS1_VERSION)
-        return 4;
-#if OPENSSL_VERSION_NUMBER >= 0x10001000L
-    else if (sslVersion == TLS1_1_VERSION)
-        return 5;
-    else if (sslVersion == TLS1_2_VERSION)
-        return 6;
-#endif
-    else
-        return 1;
-}
-
-#if OPENSSL_VERSION_NUMBER < 0x00909000L
-SSL_METHOD *
-#else
-const SSL_METHOD *
-#endif
-Ssl::method(int version)
-{
-    switch (version) {
-
-    case 2:
-#if !defined(OPENSSL_NO_SSL2)
-        debugs(83, 5, "Using SSLv2.");
-        return SSLv2_client_method();
-#else
-        debugs(83, DBG_IMPORTANT, "SSLv2 is not available in this Proxy.");
-        return NULL;
-#endif
-        break;
-
-    case 3:
-#if !defined(OPENSSL_NO_SSL3)
-        debugs(83, 5, "Using SSLv3.");
-        return SSLv3_client_method();
-#else
-        debugs(83, DBG_IMPORTANT, "SSLv3 is not available in this Proxy.");
-        return NULL;
-#endif
-        break;
-
-    case 4:
-        debugs(83, 5, "Using TLSv1.");
-        return TLSv1_client_method();
-        break;
-
-    case 5:
-#if OPENSSL_VERSION_NUMBER >= 0x10001000L  // NP: not sure exactly which sub-version yet.
-        debugs(83, 5, "Using TLSv1.1.");
-        return TLSv1_1_client_method();
-#else
-        debugs(83, DBG_IMPORTANT, "TLSv1.1 is not available in this Proxy.");
-        return NULL;
-#endif
-        break;
-
-    case 6:
-#if OPENSSL_VERSION_NUMBER >= 0x10001000L // NP: not sure exactly which sub-version yet.
-        debugs(83, 5, "Using TLSv1.2");
-        return TLSv1_2_client_method();
-#else
-        debugs(83, DBG_IMPORTANT, "TLSv1.2 is not available in this Proxy.");
-        return NULL;
-#endif
-        break;
-
-    case 1:
-
-    default:
-        debugs(83, 5, "Using SSLv2/SSLv3.");
-        return SSLv23_client_method();
-        break;
-    }
-
-    //Not reached
-    return NULL;
-}
-
-const SSL_METHOD *
-Ssl::serverMethod(int version)
-{
-    switch (version) {
-
-    case 2:
-#if !defined(OPENSSL_NO_SSL2)
-        debugs(83, 5, "Using SSLv2.");
-        return SSLv2_server_method();
-#else
-        debugs(83, DBG_IMPORTANT, "SSLv2 is not available in this Proxy.");
-        return NULL;
-#endif
-        break;
-
-    case 3:
-#if !defined(OPENSSL_NO_SSL3)
-        debugs(83, 5, "Using SSLv3.");
-        return SSLv3_server_method();
-#else
-        debugs(83, DBG_IMPORTANT, "SSLv3 is not available in this Proxy.");
-        return NULL;
-#endif
-        break;
-
-    case 4:
-        debugs(83, 5, "Using TLSv1.");
-        return TLSv1_server_method();
-        break;
-
-    case 5:
-#if OPENSSL_VERSION_NUMBER >= 0x10001000L  // NP: not sure exactly which sub-version yet.
-        debugs(83, 5, "Using TLSv1.1.");
-        return TLSv1_1_server_method();
-#else
-        debugs(83, DBG_IMPORTANT, "TLSv1.1 is not available in this Proxy.");
-        return NULL;
-#endif
-        break;
-
-    case 6:
-#if OPENSSL_VERSION_NUMBER >= 0x10001000L // NP: not sure exactly which sub-version yet.
-        debugs(83, 5, "Using TLSv1.2");
-        return TLSv1_2_server_method();
-#else
-        debugs(83, DBG_IMPORTANT, "TLSv1.2 is not available in this Proxy.");
-        return NULL;
-#endif
-        break;
-
-    case 1:
-
-    default:
-        debugs(83, 5, "Using SSLv2/SSLv3.");
-        return SSLv23_server_method();
-        break;
-    }
-
-    //Not reached
-    return NULL;
-}
-
-#if defined(TLSEXT_TYPE_next_proto_neg)
-//Dummy next_proto_neg callback
-static int
-ssl_next_proto_cb(SSL *s, unsigned char **out, unsigned char *outlen, const unsigned char *in, unsigned int inlen, void *arg)
-{
-    static const unsigned char supported_protos[] = {8, 'h','t','t', 'p', '/', '1', '.', '1'};
-    (void)SSL_select_next_proto(out, outlen, in, inlen, supported_protos, sizeof(supported_protos));
-    return SSL_TLSEXT_ERR_OK;
-}
-#endif
-
-SSL_CTX *
-sslCreateClientContext(const char *certfile, const char *keyfile, int version, const char *cipher, const char *options, const char *flags, const char *CAfile, const char *CApath, const char *CRLfile)
+bool
+Ssl::InitServerContext(Security::ContextPointer &ctx, AnyP::PortCfg &port)
 {
-    int ssl_error;
-    Ssl::ContextMethod method;
-    SSL_CTX * sslContext;
-    long fl = Ssl::parse_flags(flags);
-
-    ssl_initialize();
-
-    if (!keyfile)
-        keyfile = certfile;
-
-    if (!certfile)
-        certfile = keyfile;
-
-    if (!(method = Ssl::method(version)))
-        return NULL;
-
-    sslContext = SSL_CTX_new(method);
-
-    if (sslContext == NULL) {
-        ssl_error = ERR_get_error();
-        fatalf("Failed to allocate SSL context: %s\n",
-               ERR_error_string(ssl_error, NULL));
-    }
-
-    SSL_CTX_set_options(sslContext, Ssl::parse_options(options));
-
-    if (cipher) {
-        debugs(83, 5, "Using chiper suite " << cipher << ".");
+    if (!ctx)
+        return false;
 
-        if (!SSL_CTX_set_cipher_list(sslContext, cipher)) {
-            ssl_error = ERR_get_error();
-            fatalf("Failed to set SSL cipher suite '%s': %s\n",
-                   cipher, ERR_error_string(ssl_error, NULL));
-        }
+    if (!SSL_CTX_use_certificate(ctx.get(), port.signingCert.get())) {
+        const int ssl_error = ERR_get_error();
+        const auto &keys = port.secure.certs.front();
+        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire TLS certificate '" << keys.certFile << "': " << Security::ErrorString(ssl_error));
+        return false;
     }
 
-    if (certfile) {
+    if (!SSL_CTX_use_PrivateKey(ctx.get(), port.signPkey.get())) {
+        const int ssl_error = ERR_get_error();
+        const auto &keys = port.secure.certs.front();
+        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire TLS private key '" << keys.privateKeyFile << "': " << Security::ErrorString(ssl_error));
+        return false;
+    }
+
+    Ssl::addChainToSslContext(ctx, port.certsToChain.get());
+
+    /* Alternate code;
         debugs(83, DBG_IMPORTANT, "Using certificate in " << certfile);
 
-        if (!SSL_CTX_use_certificate_chain_file(sslContext, certfile)) {
+        if (!SSL_CTX_use_certificate_chain_file(ctx.get(), certfile)) {
             ssl_error = ERR_get_error();
-            fatalf("Failed to acquire SSL certificate '%s': %s\n",
-                   certfile, ERR_error_string(ssl_error, NULL));
+            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL certificate '" << certfile << "': " << Security::ErrorString(ssl_error));
+            return false;
         }
 
         debugs(83, DBG_IMPORTANT, "Using private key in " << keyfile);
-        ssl_ask_password(sslContext, keyfile);
+        ssl_ask_password(ctx.get(), keyfile);
 
-        if (!SSL_CTX_use_PrivateKey_file(sslContext, keyfile, SSL_FILETYPE_PEM)) {
+        if (!SSL_CTX_use_PrivateKey_file(ctx.get(), keyfile, SSL_FILETYPE_PEM)) {
             ssl_error = ERR_get_error();
-            fatalf("Failed to acquire SSL private key '%s': %s\n",
-                   keyfile, ERR_error_string(ssl_error, NULL));
+            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL private key '" << keyfile << "': " << Security::ErrorString(ssl_error));
+            return false;
         }
 
         debugs(83, 5, "Comparing private and public SSL keys.");
 
-        if (!SSL_CTX_check_private_key(sslContext)) {
+        if (!SSL_CTX_check_private_key(ctx.get())) {
             ssl_error = ERR_get_error();
-            fatalf("SSL private key '%s' does not match public key '%s': %s\n",
-                   certfile, keyfile, ERR_error_string(ssl_error, NULL));
+            debugs(83, DBG_CRITICAL, "ERROR: SSL private key '" << certfile << "' does not match public key '" <<
+                   keyfile << "': " << Security::ErrorString(ssl_error));
+            return false;
         }
-    }
-
-    debugs(83, 9, "Setting RSA key generation callback.");
-    SSL_CTX_set_tmp_rsa_callback(sslContext, ssl_temp_rsa_cb);
-
-    if (fl & SSL_FLAG_DONT_VERIFY_PEER) {
-        debugs(83, 2, "NOTICE: Peer certificates are not verified for validity!");
-        SSL_CTX_set_verify(sslContext, SSL_VERIFY_NONE, NULL);
-    } else {
-        debugs(83, 9, "Setting certificate verification callback.");
-        SSL_CTX_set_verify(sslContext, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
-    }
-
-    debugs(83, 9, "Setting CA certificate locations.");
-
-    if ((CAfile || CApath) && !SSL_CTX_load_verify_locations(sslContext, CAfile, CApath)) {
-        ssl_error = ERR_get_error();
-        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting CA certificate locations: " << ERR_error_string(ssl_error, NULL));
-    }
-
-    if (CRLfile) {
-        ssl_load_crl(sslContext, CRLfile);
-        fl |= SSL_FLAG_VERIFY_CRL;
-    }
-
-#if X509_V_FLAG_CRL_CHECK
-    if (fl & SSL_FLAG_VERIFY_CRL_ALL)
-        X509_STORE_set_flags(SSL_CTX_get_cert_store(sslContext), X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
-    else if (fl & SSL_FLAG_VERIFY_CRL)
-        X509_STORE_set_flags(SSL_CTX_get_cert_store(sslContext), X509_V_FLAG_CRL_CHECK);
-
-#endif
+    */
 
-    if (!(fl & SSL_FLAG_NO_DEFAULT_CA) &&
-            !SSL_CTX_set_default_verify_paths(sslContext)) {
-        ssl_error = ERR_get_error();
-        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting default CA certificate location: " << ERR_error_string(ssl_error, NULL));
+    if (!configureSslContext(ctx, port)) {
+        debugs(83, DBG_CRITICAL, "ERROR: Configuring static SSL context");
+        return false;
     }
 
-#if defined(TLSEXT_TYPE_next_proto_neg)
-    SSL_CTX_set_next_proto_select_cb(sslContext, &ssl_next_proto_cb, NULL);
-#endif
-    return sslContext;
+    return true;
 }
 
-/// \ingroup ServerProtocolSSLInternal
-int
-ssl_read_method(int fd, char *buf, int len)
+bool
+Ssl::InitClientContext(Security::ContextPointer &ctx, Security::PeerOptions &peer, long fl)
 {
-    SSL *ssl = fd_table[fd].ssl;
+    if (!ctx)
+        return false;
 
-#if DONT_DO_THIS
+    if (!peer.sslCipher.isEmpty()) {
+        debugs(83, 5, "Using chiper suite " << peer.sslCipher << ".");
 
-    if (!SSL_is_init_finished(ssl)) {
-        errno = ENOTCONN;
-        return -1;
+        const char *cipher = peer.sslCipher.c_str();
+        if (!SSL_CTX_set_cipher_list(ctx.get(), cipher)) {
+            const int ssl_error = ERR_get_error();
+            fatalf("Failed to set SSL cipher suite '%s': %s\n",
+                   cipher, Security::ErrorString(ssl_error));
+        }
     }
 
-#endif
-
-    int i = SSL_read(ssl, buf, len);
-    if (i > 0) {
-        (void)VALGRIND_MAKE_MEM_DEFINED(buf, i);
-    }
+    if (!peer.certs.empty()) {
+        // TODO: support loading multiple cert/key pairs
+        auto &keys = peer.certs.front();
+        if (!keys.certFile.isEmpty()) {
+            debugs(83, DBG_IMPORTANT, "Using certificate in " << keys.certFile);
 
-    if (i > 0 && SSL_pending(ssl) > 0) {
-        debugs(83, 2, "SSL FD " << fd << " is pending");
-        fd_table[fd].flags.read_pending = true;
-    } else
-        fd_table[fd].flags.read_pending = false;
+            const char *certfile = keys.certFile.c_str();
+            if (!SSL_CTX_use_certificate_chain_file(ctx.get(), certfile)) {
+                const int ssl_error = ERR_get_error();
+                fatalf("Failed to acquire SSL certificate '%s': %s\n",
+                       certfile, Security::ErrorString(ssl_error));
+            }
 
-    return i;
-}
+            debugs(83, DBG_IMPORTANT, "Using private key in " << keys.privateKeyFile);
+            const char *keyfile = keys.privateKeyFile.c_str();
+            ssl_ask_password(ctx.get(), keyfile);
+
+            if (!SSL_CTX_use_PrivateKey_file(ctx.get(), keyfile, SSL_FILETYPE_PEM)) {
+                const int ssl_error = ERR_get_error();
+                fatalf("Failed to acquire SSL private key '%s': %s\n",
+                       keyfile, Security::ErrorString(ssl_error));
+            }
 
-/// \ingroup ServerProtocolSSLInternal
-int
-ssl_write_method(int fd, const char *buf, int len)
-{
-    SSL *ssl = fd_table[fd].ssl;
-    int i;
+            debugs(83, 5, "Comparing private and public SSL keys.");
 
-    if (!SSL_is_init_finished(ssl)) {
-        errno = ENOTCONN;
-        return -1;
+            if (!SSL_CTX_check_private_key(ctx.get())) {
+                const int ssl_error = ERR_get_error();
+                fatalf("SSL private key '%s' does not match public key '%s': %s\n",
+                       certfile, keyfile, Security::ErrorString(ssl_error));
+            }
+        }
     }
 
-    i = SSL_write(ssl, buf, len);
+    maybeSetupRsaCallback(ctx);
 
-    return i;
-}
+    if (fl & SSL_FLAG_DONT_VERIFY_PEER) {
+        debugs(83, 2, "NOTICE: Peer certificates are not verified for validity!");
+        SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_NONE, NULL);
+    } else {
+        debugs(83, 9, "Setting certificate verification callback.");
+        SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
+    }
 
-void
-ssl_shutdown_method(SSL *ssl)
-{
-    SSL_shutdown(ssl);
+    return true;
 }
 
 /// \ingroup ServerProtocolSSLInternal
 static const char *
 ssl_get_attribute(X509_NAME * name, const char *attribute_name)
 {
     static char buffer[1024];
-    int nid;
-
     buffer[0] = '\0';
 
     if (strcmp(attribute_name, "DN") == 0) {
         X509_NAME_oneline(name, buffer, sizeof(buffer));
-        goto done;
-    }
-
-    nid = OBJ_txt2nid((char *) attribute_name);
-
-    if (nid == 0) {
-        debugs(83, DBG_IMPORTANT, "WARNING: Unknown SSL attribute name '" << attribute_name << "'");
-        return NULL;
+    } else {
+        int nid = OBJ_txt2nid(const_cast<char *>(attribute_name));
+        if (nid == 0) {
+            debugs(83, DBG_IMPORTANT, "WARNING: Unknown SSL attribute name '" << attribute_name << "'");
+            return nullptr;
+        }
+        X509_NAME_get_text_by_NID(name, nid, buffer, sizeof(buffer));
     }
 
-    X509_NAME_get_text_by_NID(name, nid, buffer, sizeof(buffer));
-
-done:
-    return *buffer ? buffer : NULL;
+    return *buffer ? buffer : nullptr;
 }
 
 /// \ingroup ServerProtocolSSLInternal
 const char *
 Ssl::GetX509UserAttribute(X509 * cert, const char *attribute_name)
 {
