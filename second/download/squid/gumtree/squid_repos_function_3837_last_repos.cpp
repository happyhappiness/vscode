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