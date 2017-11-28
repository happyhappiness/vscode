              int, long, void *)
{
    SBuf  *buf = static_cast <SBuf *>(ptr);
    delete buf;
}

void
Ssl::Initialize(void)
{
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;

    SSL_load_error_strings();
    SSLeay_add_ssl_algorithms();

#if HAVE_OPENSSL_ENGINE_H
    if (::Config.SSL.ssl_engine) {
        ENGINE *e;
        if (!(e = ENGINE_by_id(::Config.SSL.ssl_engine)))
            fatalf("Unable to find SSL engine '%s'\n", ::Config.SSL.ssl_engine);

        if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
            const int ssl_error = ERR_get_error();
            fatalf("Failed to initialise SSL engine: %s\n", Security::ErrorString(ssl_error));
        }
    }
#else
    if (::Config.SSL.ssl_engine)
        fatalf("Your OpenSSL has no SSL engine support\n");
#endif

    const char *defName = ::Config.SSL.certSignHash ? ::Config.SSL.certSignHash : SQUID_SSL_SIGN_HASH_IF_NONE;
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
    ssl_ex_index_ssl_untrusted_chain = SSL_get_ex_new_index(0, (void *) "ssl_untrusted_chain", NULL, NULL, &ssl_free_CertChain);
}

static bool
configureSslContext(Security::ContextPointer &ctx, AnyP::PortCfg &port)
{
    int ssl_error;
    SSL_CTX_set_options(ctx.get(), port.secure.parsedOptions);

    if (port.sslContextSessionId)
        SSL_CTX_set_session_id_context(ctx.get(), (const unsigned char *)port.sslContextSessionId, strlen(port.sslContextSessionId));

    if (port.secure.parsedFlags & SSL_FLAG_NO_SESSION_REUSE) {
        SSL_CTX_set_session_cache_mode(ctx.get(), SSL_SESS_CACHE_OFF);
    }

    if (Config.SSL.unclean_shutdown) {
        debugs(83, 5, "Enabling quiet SSL shutdowns (RFC violation).");

        SSL_CTX_set_quiet_shutdown(ctx.get(), 1);
    }

    if (!port.secure.sslCipher.isEmpty()) {
        debugs(83, 5, "Using chiper suite " << port.secure.sslCipher << ".");

        if (!SSL_CTX_set_cipher_list(ctx.get(), port.secure.sslCipher.c_str())) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to set SSL cipher suite '" << port.secure.sslCipher << "': " << Security::ErrorString(ssl_error));
            return false;
        }
    }

    maybeSetupRsaCallback(ctx);

    port.secure.updateContextEecdh(ctx);
    port.secure.updateContextCa(ctx);

    if (port.clientCA.get()) {
        ERR_clear_error();
        if (STACK_OF(X509_NAME) *clientca = SSL_dup_CA_list(port.clientCA.get())) {
            SSL_CTX_set_client_CA_list(ctx.get(), clientca);
        } else {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to dupe the client CA list: " << Security::ErrorString(ssl_error));
            return false;
        }

        if (port.secure.parsedFlags & SSL_FLAG_DELAYED_AUTH) {
            debugs(83, 9, "Not requesting client certificates until acl processing requires one");
            SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_NONE, NULL);
        } else {
            debugs(83, 9, "Requiring client certificates.");
            SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
        }

        port.secure.updateContextCrl(ctx);

    } else {
        debugs(83, 9, "Not requiring any client certificates");
        SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_NONE, NULL);
    }

    if (port.secure.parsedFlags & SSL_FLAG_DONT_VERIFY_DOMAIN)
        SSL_CTX_set_ex_data(ctx.get(), ssl_ctx_ex_index_dont_verify_domain, (void *) -1);

    Ssl::SetSessionCallbacks(ctx);

    return true;
}

bool
Ssl::InitServerContext(Security::ContextPointer &ctx, AnyP::PortCfg &port)
{
    if (!ctx)
        return false;

    if (!SSL_CTX_use_certificate(ctx.get(), port.signingCert.get())) {
        const int ssl_error = ERR_get_error();
        const auto &keys = port.secure.certs.front();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire TLS certificate '" << keys.certFile << "': " << Security::ErrorString(ssl_error));
        return false;
    }

    if (!SSL_CTX_use_PrivateKey(ctx.get(), port.signPkey.get())) {
        const int ssl_error = ERR_get_error();
        const auto &keys = port.secure.certs.front();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire TLS private key '" << keys.privateKeyFile << "': " << Security::ErrorString(ssl_error));
        return false;
    }

    Ssl::addChainToSslContext(ctx, port.certsToChain.get());

    /* Alternate code;
        debugs(83, DBG_IMPORTANT, "Using certificate in " << certfile);

        if (!SSL_CTX_use_certificate_chain_file(ctx.get(), certfile)) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL certificate '" << certfile << "': " << Security::ErrorString(ssl_error));
            return false;
        }

        debugs(83, DBG_IMPORTANT, "Using private key in " << keyfile);
        ssl_ask_password(ctx.get(), keyfile);

        if (!SSL_CTX_use_PrivateKey_file(ctx.get(), keyfile, SSL_FILETYPE_PEM)) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: Failed to acquire SSL private key '" << keyfile << "': " << Security::ErrorString(ssl_error));
            return false;
        }

        debugs(83, 5, "Comparing private and public SSL keys.");

        if (!SSL_CTX_check_private_key(ctx.get())) {
            ssl_error = ERR_get_error();
            debugs(83, DBG_CRITICAL, "ERROR: SSL private key '" << certfile << "' does not match public key '" <<
                   keyfile << "': " << Security::ErrorString(ssl_error));
            return false;
        }
    */

    if (!configureSslContext(ctx, port)) {
        debugs(83, DBG_CRITICAL, "ERROR: Configuring static SSL context");
        return false;
    }

    return true;
}

bool
Ssl::InitClientContext(Security::ContextPointer &ctx, Security::PeerOptions &peer, long fl)
{
    if (!ctx)
        return false;

    if (!peer.sslCipher.isEmpty()) {
        debugs(83, 5, "Using chiper suite " << peer.sslCipher << ".");

        const char *cipher = peer.sslCipher.c_str();
        if (!SSL_CTX_set_cipher_list(ctx.get(), cipher)) {
            const int ssl_error = ERR_get_error();
            fatalf("Failed to set SSL cipher suite '%s': %s\n",
                   cipher, Security::ErrorString(ssl_error));
        }
    }

    if (!peer.certs.empty()) {
        // TODO: support loading multiple cert/key pairs
        auto &keys = peer.certs.front();
        if (!keys.certFile.isEmpty()) {
            debugs(83, DBG_IMPORTANT, "Using certificate in " << keys.certFile);

            const char *certfile = keys.certFile.c_str();
            if (!SSL_CTX_use_certificate_chain_file(ctx.get(), certfile)) {
                const int ssl_error = ERR_get_error();
                fatalf("Failed to acquire SSL certificate '%s': %s\n",
                       certfile, Security::ErrorString(ssl_error));
            }

            debugs(83, DBG_IMPORTANT, "Using private key in " << keys.privateKeyFile);
            const char *keyfile = keys.privateKeyFile.c_str();
            ssl_ask_password(ctx.get(), keyfile);

            if (!SSL_CTX_use_PrivateKey_file(ctx.get(), keyfile, SSL_FILETYPE_PEM)) {
                const int ssl_error = ERR_get_error();
                fatalf("Failed to acquire SSL private key '%s': %s\n",
                       keyfile, Security::ErrorString(ssl_error));
            }

            debugs(83, 5, "Comparing private and public SSL keys.");

            if (!SSL_CTX_check_private_key(ctx.get())) {
                const int ssl_error = ERR_get_error();
                fatalf("SSL private key '%s' does not match public key '%s': %s\n",
                       certfile, keyfile, Security::ErrorString(ssl_error));
            }
        }
    }

    maybeSetupRsaCallback(ctx);

    if (fl & SSL_FLAG_DONT_VERIFY_PEER) {
        debugs(83, 2, "NOTICE: Peer certificates are not verified for validity!");
        SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_NONE, NULL);
    } else {
        debugs(83, 9, "Setting certificate verification callback.");
        SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, ssl_verify_cb);
    }

    return true;
}

/// \ingroup ServerProtocolSSLInternal
static const char *
ssl_get_attribute(X509_NAME * name, const char *attribute_name)
{
    static char buffer[1024];
    buffer[0] = '\0';

    if (strcmp(attribute_name, "DN") == 0) {
        X509_NAME_oneline(name, buffer, sizeof(buffer));
    } else {
        int nid = OBJ_txt2nid(const_cast<char *>(attribute_name));
        if (nid == 0) {
            debugs(83, DBG_IMPORTANT, "WARNING: Unknown SSL attribute name '" << attribute_name << "'");
            return nullptr;
        }
        X509_NAME_get_text_by_NID(name, nid, buffer, sizeof(buffer));
    }

    return *buffer ? buffer : nullptr;
}

/// \ingroup ServerProtocolSSLInternal
const char *
Ssl::GetX509UserAttribute(X509 * cert, const char *attribute_name)
{
