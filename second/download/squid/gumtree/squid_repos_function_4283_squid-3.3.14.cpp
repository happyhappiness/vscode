SSL_CTX *
sslCreateClientContext(const char *certfile, const char *keyfile, int version, const char *cipher, const char *options, const char *flags, const char *CAfile, const char *CApath, const char *CRLfile)
{
    int ssl_error;
    Ssl::ContextMethod method;
    SSL_CTX * sslContext;
    long fl = Ssl::parse_flags(flags);

    ssl_initialize();

    if (!keyfile)
        keyfile = certfile;

    if (!certfile)
        certfile = keyfile;

    switch (version) {

    case 2:
#ifndef OPENSSL_NO_SSL2
        debugs(83, 5, "Using SSLv2.");
        method = SSLv2_client_method();
#else
        debugs(83, DBG_IMPORTANT, "SSLv2 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 3:
        debugs(83, 5, "Using SSLv3.");
        method = SSLv3_client_method();
        break;

    case 4:
        debugs(83, 5, "Using TLSv1.");
        method = TLSv1_client_method();
        break;

    case 5:
#if OPENSSL_VERSION_NUMBER >= 0x10001000L  // NP: not sure exactly which sub-version yet.
        debugs(83, 5, "Using TLSv1.1.");
        method = TLSv1_1_client_method();
#else
        debugs(83, DBG_IMPORTANT, "TLSv1.1 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 6:
#if OPENSSL_VERSION_NUMBER >= 0x10001000L // NP: not sure exactly which sub-version yet.
        debugs(83, 5, "Using TLSv1.2");
        method = TLSv1_2_client_method();
#else
        debugs(83, DBG_IMPORTANT, "TLSv1.2 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 1:

    default:
        debugs(83, 5, "Using SSLv2/SSLv3.");
        method = SSLv23_client_method();
        break;
    }

    sslContext = SSL_CTX_new(method);

    if (sslContext == NULL) {
        ssl_error = ERR_get_error();
        fatalf("Failed to allocate SSL context: %s\n",
               ERR_error_string(ssl_error, NULL));
    }

    SSL_CTX_set_options(sslContext, Ssl::parse_options(options));

    if (cipher) {
        debugs(83, 5, "Using chiper suite " << cipher << ".");

        if (!SSL_CTX_set_cipher_list(sslContext, cipher)) {
            ssl_error = ERR_get_error();
            fatalf("Failed to set SSL cipher suite '%s': %s\n",
                   cipher, ERR_error_string(ssl_error, NULL));
        }
    }

    if (certfile) {
        debugs(83, DBG_IMPORTANT, "Using certificate in " << certfile);

        if (!SSL_CTX_use_certificate_chain_file(sslContext, certfile)) {
            ssl_error = ERR_get_error();
            fatalf("Failed to acquire SSL certificate '%s': %s\n",
                   certfile, ERR_error_string(ssl_error, NULL));
        }

        debugs(83, DBG_IMPORTANT, "Using private key in " << keyfile);
        ssl_ask_password(sslContext, keyfile);

        if (!SSL_CTX_use_PrivateKey_file(sslContext, keyfile, SSL_FILETYPE_PEM)) {
            ssl_error = ERR_get_error();
            fatalf("Failed to acquire SSL private key '%s': %s\n",
                   keyfile, ERR_error_string(ssl_error, NULL));
        }

        debugs(83, 5, "Comparing private and public SSL keys.");

        if (!SSL_CTX_check_private_key(sslContext)) {
            ssl_error = ERR_get_error();
            fatalf("SSL private key '%s' does not match public key '%s': %s\n",
                   certfile, keyfile, ERR_error_string(ssl_error, NULL));
        }
    }

    debugs(83, 9, "Setting RSA key generation callback.");
    SSL_CTX_set_tmp_rsa_callback(sslContext, ssl_temp_rsa_cb);

    if (fl & SSL_FLAG_DONT_VERIFY_PEER) {
        debugs(83, 2, "NOTICE: Peer certificates are not verified for validity!");
        SSL_CTX_set_verify(sslContext, SSL_VERIFY_NONE, NULL);
    } else {
        debugs(83, 9, "Setting certificate verification callback.");
        SSL_CTX_set_verify(sslContext, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
    }

    debugs(83, 9, "Setting CA certificate locations.");

    if ((CAfile || CApath) && !SSL_CTX_load_verify_locations(sslContext, CAfile, CApath)) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting CA certificate locations: " << ERR_error_string(ssl_error, NULL));
    }

    if (CRLfile) {
        ssl_load_crl(sslContext, CRLfile);
        fl |= SSL_FLAG_VERIFY_CRL;
    }

#if X509_V_FLAG_CRL_CHECK
    if (fl & SSL_FLAG_VERIFY_CRL_ALL)
        X509_STORE_set_flags(SSL_CTX_get_cert_store(sslContext), X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
    else if (fl & SSL_FLAG_VERIFY_CRL)
        X509_STORE_set_flags(SSL_CTX_get_cert_store(sslContext), X509_V_FLAG_CRL_CHECK);

#endif

    if (!(fl & SSL_FLAG_NO_DEFAULT_CA) &&
            !SSL_CTX_set_default_verify_paths(sslContext)) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting default CA certificate location: " << ERR_error_string(ssl_error, NULL));
    }

    return sslContext;
}