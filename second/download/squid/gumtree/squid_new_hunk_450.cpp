    }

    BIO_free(in);
    return count;
}

STACK_OF(X509_CRL) *
Ssl::loadCrl(const char *CRLFile, long &flags)
{
    X509_CRL *crl;
    BIO *in = BIO_new_file(CRLFile, "r");
    if (!in) {
        debugs(83, 2, "WARNING: Failed to open CRL file '" << CRLFile << "'");
        return NULL;
    }

    STACK_OF(X509_CRL) *CRLs = sk_X509_CRL_new_null();
    if (!CRLs) {
        debugs(83, 2, "WARNING: Failed to allocate X509_CRL stack  to load file '" << CRLFile << "'");
        return NULL;
    }

    int count = 0;
    while ((crl = PEM_read_bio_X509_CRL(in,NULL,NULL,NULL))) {
        if (!sk_X509_CRL_push(CRLs, crl))
            debugs(83, 2, "WARNING: Failed to add CRL from file '" << CRLFile << "'");
        else
            ++count;
    }
    BIO_free(in);

    if (count)
        flags |= SSL_FLAG_VERIFY_CRL;

    return CRLs;
}

DH *
Ssl::readDHParams(const char *dhfile)
{
    FILE *in = fopen(dhfile, "r");
    DH *dh = NULL;
    int codes;

    if (in) {
        dh = PEM_read_DHparams(in, NULL, NULL, NULL);
        fclose(in);
    }

    if (!dh)
        debugs(83, DBG_IMPORTANT, "WARNING: Failed to read DH parameters '" << dhfile << "'");
    else if (dh && DH_check(dh, &codes) == 0) {
        if (codes) {
            debugs(83, DBG_IMPORTANT, "WARNING: Failed to verify DH parameters '" << dhfile  << "' (" << std::hex << codes  << ")");
            DH_free(dh);
            dh = NULL;
        }
    }
    return dh;
}

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
        SSL_CTX_set_client_CA_list(sslContext, port.clientCA.get());

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
