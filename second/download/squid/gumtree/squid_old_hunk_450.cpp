    }

    BIO_free(in);
    return count;
}

SSL_CTX *
sslCreateServerContext(const char *certfile, const char *keyfile, int version, const char *cipher, const char *options, const char *flags, const char *clientCA, const char *CAfile, const char *CApath, const char *CRLfile, const char *dhfile, const char *context)
{
    int ssl_error;
#if OPENSSL_VERSION_NUMBER < 0x00909000L
    SSL_METHOD *method;
#else
    const SSL_METHOD *method;
#endif
    SSL_CTX *sslContext;
    long fl = ssl_parse_flags(flags);

    ssl_initialize();

    if (!keyfile)
        keyfile = certfile;

    if (!certfile)
        certfile = keyfile;

    if (!CAfile)
        CAfile = clientCA;

    switch (version) {

    case 2:
#ifndef OPENSSL_NO_SSL2
        debugs(83, 5, "Using SSLv2.");
        method = SSLv2_server_method();
#else
        debugs(83, DBG_IMPORTANT, "SSLv2 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 3:
        debugs(83, 5, "Using SSLv3.");
        method = SSLv3_server_method();
        break;

    case 4:
        debugs(83, 5, "Using TLSv1.");
        method = TLSv1_server_method();
        break;

    case 5:
#if OPENSSL_VERSION_NUMBER >= 0x10001000L  // NP: not sure exactly which sub-version yet.
        debugs(83, 5, "Using TLSv1.1.");
        method = TLSv1_1_server_method();
#else
        debugs(83, DBG_IMPORTANT, "TLSv1.1 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 6:
#if OPENSSL_VERSION_NUMBER >= 0x10001000L // NP: not sure exactly which sub-version yet.
        debugs(83, 5, "Using TLSv1.2");
        method = TLSv1_2_server_method();
#else
        debugs(83, DBG_IMPORTANT, "TLSv1.2 is not available in this Proxy.");
        return NULL;
#endif
        break;

    case 1:

    default:
        debugs(83, 5, "Using SSLv2/SSLv3.");
        method = SSLv23_server_method();
        break;
    }

    sslContext = SSL_CTX_new(method);

    if (sslContext == NULL) {
        ssl_error = ERR_get_error();
        fatalf("Failed to allocate SSL context: %s\n",
               ERR_error_string(ssl_error, NULL));
    }

    SSL_CTX_set_options(sslContext, ssl_parse_options(options));

    if (context && *context) {
        SSL_CTX_set_session_id_context(sslContext, (const unsigned char *)context, strlen(context));
    }

    if (fl & SSL_FLAG_NO_SESSION_REUSE) {
        SSL_CTX_set_session_cache_mode(sslContext, SSL_SESS_CACHE_OFF);
    }

    if (Config.SSL.unclean_shutdown) {
        debugs(83, 5, "Enabling quiet SSL shutdowns (RFC violation).");

        SSL_CTX_set_quiet_shutdown(sslContext, 1);
    }

    if (cipher) {
        debugs(83, 5, "Using chiper suite " << cipher << ".");

        if (!SSL_CTX_set_cipher_list(sslContext, cipher)) {
            ssl_error = ERR_get_error();
            fatalf("Failed to set SSL cipher suite '%s': %s\n",
                   cipher, ERR_error_string(ssl_error, NULL));
        }
    }

    debugs(83, DBG_IMPORTANT, "Using certificate in " << certfile);

    if (!SSL_CTX_use_certificate_chain_file(sslContext, certfile)) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL certificate '" << certfile << "': " << ERR_error_string(ssl_error, NULL));
        SSL_CTX_free(sslContext);
        return NULL;
    }

    debugs(83, DBG_IMPORTANT, "Using private key in " << keyfile);
    ssl_ask_password(sslContext, keyfile);

    if (!SSL_CTX_use_PrivateKey_file(sslContext, keyfile, SSL_FILETYPE_PEM)) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL private key '" << keyfile << "': " << ERR_error_string(ssl_error, NULL));
        SSL_CTX_free(sslContext);
        return NULL;
    }

    debugs(83, 5, "Comparing private and public SSL keys.");

    if (!SSL_CTX_check_private_key(sslContext)) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_CRITICAL, "ERROR: SSL private key '" << certfile << "' does not match public key '" <<
               keyfile << "': " << ERR_error_string(ssl_error, NULL));
        SSL_CTX_free(sslContext);
        return NULL;
    }

    debugs(83, 9, "Setting RSA key generation callback.");
    SSL_CTX_set_tmp_rsa_callback(sslContext, ssl_temp_rsa_cb);

    debugs(83, 9, "Setting CA certificate locations.");

    if ((CAfile || CApath) && !SSL_CTX_load_verify_locations(sslContext, CAfile, CApath)) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting CA certificate locations: " << ERR_error_string(ssl_error, NULL));
    }

    if (!(fl & SSL_FLAG_NO_DEFAULT_CA) &&
            !SSL_CTX_set_default_verify_paths(sslContext)) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting default CA certificate location: " << ERR_error_string(ssl_error, NULL));
    }

    if (clientCA) {
        STACK_OF(X509_NAME) *cert_names;
        debugs(83, 9, "Set client certifying authority list.");
        cert_names = SSL_load_client_CA_file(clientCA);

        if (cert_names == NULL) {
            debugs(83, DBG_IMPORTANT, "ERROR: loading the client CA certificates from '" << clientCA << "\': " << ERR_error_string(ERR_get_error(),NULL));
            SSL_CTX_free(sslContext);
            return NULL;
        }

        ERR_clear_error();
        SSL_CTX_set_client_CA_list(sslContext, cert_names);

        if (fl & SSL_FLAG_DELAYED_AUTH) {
            debugs(83, 9, "Not requesting client certificates until acl processing requires one");
            SSL_CTX_set_verify(sslContext, SSL_VERIFY_NONE, NULL);
        } else {
            debugs(83, 9, "Requiring client certificates.");
            SSL_CTX_set_verify(sslContext, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
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

    } else {
        debugs(83, 9, "Not requiring any client certificates");
        SSL_CTX_set_verify(sslContext, SSL_VERIFY_NONE, NULL);
    }
