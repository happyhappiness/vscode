static bool
adjustSSL(SSL *ssl, Ssl::Bio::sslFeatures &features)
{
#if SQUID_USE_OPENSSL_HELLO_OVERWRITE_HACK
    if (!features.initialized_)
        return false;

    if (!ssl->s3) {
        debugs(83, 5, "No SSLv3 data found!");
        return false;
    }

    // If the client supports compression but our context does not support
    // we can not adjust.
#if !defined(OPENSSL_NO_COMP)
    const bool requireCompression = (features.compressMethod && ssl->ctx->comp_methods == NULL);
#else
    const bool requireCompression = features.compressMethod;
#endif
    if (requireCompression) {
        debugs(83, 5, "Client Hello Data supports compression, but we do not!");
        return false;
    }

    // Check ciphers list
    size_t token = 0;
    size_t end = 0;
    while (token != std::string::npos) {
        end = features.clientRequestedCiphers.find(':',token);
        std::string cipher;
        cipher.assign(features.clientRequestedCiphers, token, end - token);
        token = (end != std::string::npos ? end + 1 : std::string::npos);
        bool found = false;
        STACK_OF(SSL_CIPHER) *cipher_stack = SSL_get_ciphers(ssl);
        for (int i = 0; i < sk_SSL_CIPHER_num(cipher_stack); i++) {
            SSL_CIPHER *c = sk_SSL_CIPHER_value(cipher_stack, i);
            const char *cname = SSL_CIPHER_get_name(c);
            if (cipher.compare(cname)) {
                found = true;
                break;
            }
        }
        if (!found) {
            debugs(83, 5, "Client Hello Data supports cipher '"<< cipher <<"' but we do not support it!");
            return false;
        }
    }

#if !defined(SSL_TLSEXT_HB_ENABLED)
    if (features.doHeartBeats) {
        debugs(83, 5, "Client Hello Data supports HeartBeats but we do not support!");
        return false;
    }
#endif

    for (std::list<int>::iterator it = features.extensions.begin(); it != features.extensions.end(); ++it) {
        static int supportedExtensions[] = {
#if defined(TLSEXT_TYPE_server_name)
            TLSEXT_TYPE_server_name,
#endif
#if defined(TLSEXT_TYPE_opaque_prf_input)
            TLSEXT_TYPE_opaque_prf_input,
#endif
#if defined(TLSEXT_TYPE_heartbeat)
            TLSEXT_TYPE_heartbeat,
#endif
#if defined(TLSEXT_TYPE_renegotiate)
            TLSEXT_TYPE_renegotiate,
#endif
#if defined(TLSEXT_TYPE_ec_point_formats)
            TLSEXT_TYPE_ec_point_formats,
#endif
#if defined(TLSEXT_TYPE_elliptic_curves)
            TLSEXT_TYPE_elliptic_curves,
#endif
#if defined(TLSEXT_TYPE_session_ticket)
            TLSEXT_TYPE_session_ticket,
#endif
#if defined(TLSEXT_TYPE_status_request)
            TLSEXT_TYPE_status_request,
#endif
#if defined(TLSEXT_TYPE_use_srtp)
            TLSEXT_TYPE_use_srtp,
#endif
#if 0 //Allow 13172 Firefox supported extension for testing purposes
            13172,
#endif
            -1
        };
        bool found = false;
        for (int i = 0; supportedExtensions[i] != -1; i++) {
            if (*it == supportedExtensions[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            debugs(83, 5, "Extension " << *it <<  " does not supported!");
            return false;
        }
    }

    SSL3_BUFFER *wb=&(ssl->s3->wbuf);
    if (wb->len < (size_t)features.helloMessage.length())
        return false;

    debugs(83, 5, "OpenSSL SSL struct will be adjusted to mimic client hello data!");

    //Adjust ssl structure data.
    // We need to fix the random in SSL struct:
    memcpy(ssl->s3->client_random, features.client_random, SSL3_RANDOM_SIZE);
    memcpy(wb->buf, features.helloMessage.rawContent(), features.helloMessage.length());
    wb->left = features.helloMessage.length();

    size_t mainHelloSize = features.helloMessage.length() - 5;
    const char *mainHello = features.helloMessage.rawContent() + 5;
    assert((size_t)ssl->init_buf->max > mainHelloSize);
    memcpy(ssl->init_buf->data, mainHello, mainHelloSize);
    debugs(83, 5, "Hello Data init and adjustd sizes :" << ssl->init_num << " = "<< mainHelloSize);
    ssl->init_num = mainHelloSize;
    ssl->s3->wpend_ret = mainHelloSize;
    ssl->s3->wpend_tot = mainHelloSize;
    return true;
#else
    return false;
#endif
}