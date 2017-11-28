static bool
adjustSSL(SSL *ssl, Security::TlsDetails::Pointer const &details, SBuf &helloMessage)
{
#if SQUID_USE_OPENSSL_HELLO_OVERWRITE_HACK
    if (!details)
        return false;

    if (!ssl->s3) {
        debugs(83, 5, "No SSLv3 data found!");
        return false;
    }

    // If the client supports compression but our context does not support
    // we can not adjust.
#if !defined(OPENSSL_NO_COMP)
    const bool requireCompression = (details->compressionSupported && ssl->ctx->comp_methods == nullptr);
#else
    const bool requireCompression = details->compressionSupported;
#endif
    if (requireCompression) {
        debugs(83, 5, "Client Hello Data supports compression, but we do not!");
        return false;
    }

#if !defined(SSL_TLSEXT_HB_ENABLED)
    if (details->doHeartBeats) {
        debugs(83, 5, "Client Hello Data supports HeartBeats but we do not support!");
        return false;
    }
#endif

    if (details->unsupportedExtensions) {
        debugs(83, 5, "Client Hello contains extensions that we do not support!");
        return false;
    }

    SSL3_BUFFER *wb=&(ssl->s3->wbuf);
    if (wb->len < (size_t)helloMessage.length()) {
        debugs(83, 5, "Client Hello exceeds OpenSSL buffer: " << helloMessage.length() << " >= " << wb->len);
        return false;
    }

    /* Check whether all on-the-wire ciphers are supported by OpenSSL. */

    const auto &wireCiphers = details->ciphers;
    Security::TlsDetails::Ciphers::size_type ciphersToFind = wireCiphers.size();

    // RFC 5746: "TLS_EMPTY_RENEGOTIATION_INFO_SCSV is not a true cipher suite".
    // It is commonly seen on the wire, including in from-OpenSSL traffic, but
    // SSL_get_ciphers() does not return this _pseudo_ cipher suite in my tests.
    // If OpenSSL supports scsvCipher, we count it (at most once) further below.
#if defined(TLSEXT_TYPE_renegotiate)
    // the 0x00FFFF mask converts 3-byte OpenSSL cipher to our 2-byte cipher
    const uint16_t scsvCipher = SSL3_CK_SCSV & 0x00FFFF;
#else
    const uint16_t scsvCipher = 0;
#endif

    STACK_OF(SSL_CIPHER) *cipher_stack = SSL_get_ciphers(ssl);
    const int supportedCipherCount = sk_SSL_CIPHER_num(cipher_stack);
    for (int idx = 0; idx < supportedCipherCount && ciphersToFind > 0; ++idx) {
        const SSL_CIPHER *cipher = sk_SSL_CIPHER_value(cipher_stack, idx);
        const auto id = SSL_CIPHER_get_id(cipher) & 0x00FFFF;
        if (wireCiphers.find(id) != wireCiphers.end() && (!scsvCipher || id != scsvCipher))
            --ciphersToFind;
    }

    if (ciphersToFind > 0 && scsvCipher && wireCiphers.find(scsvCipher) != wireCiphers.end())
        --ciphersToFind;

    if (ciphersToFind > 0) {
        // TODO: Add slowlyReportUnsupportedCiphers() to slowly find and report each of them
        debugs(83, 5, "Client Hello Data has " << ciphersToFind << " ciphers that we do not support!");
        return false;
    }

    debugs(83, 5, "OpenSSL SSL struct will be adjusted to mimic client hello data!");

    //Adjust ssl structure data.
    // We need to fix the random in SSL struct:
    if (details->clientRandom.length() == SSL3_RANDOM_SIZE)
        memcpy(ssl->s3->client_random, details->clientRandom.c_str(), SSL3_RANDOM_SIZE);
    memcpy(wb->buf, helloMessage.rawContent(), helloMessage.length());
    wb->left = helloMessage.length();

    size_t mainHelloSize = helloMessage.length() - 5;
    const char *mainHello = helloMessage.rawContent() + 5;
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