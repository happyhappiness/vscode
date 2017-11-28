static bool
configureSslContext(SSL_CTX *sslContext, AnyP::PortCfg &port)
{
    int ssl_error;
    SSL_CTX_set_options(sslContext, port.sslOptions);

    if (port.sslContextSessionId)
        SSL_CTX_set_session_id_context(sslContext, (const unsigned char *)port.sslContextSessionId, strlen(port.sslContextSessionId));

    if (port.sslContextFlags & SSL_FLAG_NO_SESSION_REUSE) {
        SSL_CTX_set_session_cache_mode(sslContext, SSL_SESS_CACHE_OFF);
    }

    if (Config.SSL.unclean_shutdown) {
        debugs(83, 5, "Enabling quiet SSL shutdowns (RFC violation).");

        SSL_CTX_set_quiet_shutdown(sslContext, 1);
    }

    if (port.cipher) {
        debugs(83, 5, "Using chiper suite " << port.cipher << ".");

        if (!SSL_CTX_set_cipher_list(sslContext, port.cipher)) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to set SSL cipher suite '" << port.cipher << "': " << ERR_error_string(ssl_error, NULL));
            return false;
        }
    }

    debugs(83, 9, "Setting RSA key generation callback.");
    SSL_CTX_set_tmp_rsa_callback(sslContext, ssl_temp_rsa_cb);

    if (port.eecdhCurve) {
        debugs(83, 9, "Setting Ephemeral ECDH curve to " << port.eecdhCurve << ".");

        if (!configureSslEECDH(sslContext, port.eecdhCurve)) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Unable to configure Ephemeral ECDH: " << ERR_error_string(ssl_error, NULL));
            return false;
        }
    }

    debugs(83, 9, "Setting CA certificate locations.");

    const char *cafile = port.cafile ? port.cafile : port.clientca;
    if ((cafile || port.capath) && !SSL_CTX_load_verify_locations(sslContext, cafile, port.capath)) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting CA certificate locations: " << ERR_error_string(ssl_error, NULL));
    }

    if (!(port.sslContextFlags & SSL_FLAG_NO_DEFAULT_CA) &&
            !SSL_CTX_set_default_verify_paths(sslContext)) {
        ssl_error = ERR_get_error();
        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting default CA certificate location: " << ERR_error_string(ssl_error, NULL));
    }

    if (port.clientCA.get()) {
        ERR_clear_error();
        if (STACK_OF(X509_NAME) *clientca = SSL_dup_CA_list(port.clientCA.get())) {
            SSL_CTX_set_client_CA_list(sslContext, clientca);
        } else {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to dupe the client CA list: " << ERR_error_string(ssl_error, NULL));
            return false;
        }

        if (port.sslContextFlags & SSL_FLAG_DELAYED_AUTH) {
            debugs(83, 9, "Not requesting client certificates until acl processing requires one");
            SSL_CTX_set_verify(sslContext, SSL_VERIFY_NONE, NULL);
        } else {
            debugs(83, 9, "Requiring client certificates.");
            SSL_CTX_set_verify(sslContext, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
        }

        if (port.clientVerifyCrls.get()) {
            X509_STORE *st = SSL_CTX_get_cert_store(sslContext);
            for (int i = 0; i < sk_X509_CRL_num(port.clientVerifyCrls.get()); ++i) {
                X509_CRL *crl = sk_X509_CRL_value(port.clientVerifyCrls.get(), i);
                if (!X509_STORE_add_crl(st, crl))
                    debugs(83, 2, "WARNING: Failed to add CRL");
            }
        }

#if X509_V_FLAG_CRL_CHECK
        if (port.sslContextFlags & SSL_FLAG_VERIFY_CRL_ALL)
            X509_STORE_set_flags(SSL_CTX_get_cert_store(sslContext), X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
        else if (port.sslContextFlags & SSL_FLAG_VERIFY_CRL)
            X509_STORE_set_flags(SSL_CTX_get_cert_store(sslContext), X509_V_FLAG_CRL_CHECK);
#endif

    } else {
        debugs(83, 9, "Not requiring any client certificates");
        SSL_CTX_set_verify(sslContext, SSL_VERIFY_NONE, NULL);
    }

    if (port.dhParams.get()) {
        SSL_CTX_set_tmp_dh(sslContext, port.dhParams.get());
    }

    if (port.sslContextFlags & SSL_FLAG_DONT_VERIFY_DOMAIN)
        SSL_CTX_set_ex_data(sslContext, ssl_ctx_ex_index_dont_verify_domain, (void *) -1);

    setSessionCallbacks(sslContext);

    return true;
}