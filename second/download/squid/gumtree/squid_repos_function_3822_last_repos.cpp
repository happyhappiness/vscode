void
applyTlsDetailsToSSL(SSL *ssl, Security::TlsDetails::Pointer const &details, Ssl::BumpMode bumpMode)
{
    // To increase the possibility for bumping after peek mode selection or
    // splicing after stare mode selection it is good to set the
    // SSL protocol version.
    // The SSL_set_ssl_method is wrong here because it will restrict the
    // permitted transport version to be identical to the version used in the
    // ClientHello message.
    // For example will prevent comunnicating with a tls1.0 server if the
    // client sent and tlsv1.2 Hello message.
#if defined(TLSEXT_NAMETYPE_host_name)
    if (!details->serverName.isEmpty()) {
        SSL_set_tlsext_host_name(ssl, details->serverName.c_str());
    }
#endif

    if (!details->ciphers.empty()) {
        SBuf strCiphers;
        for (auto cipherId: details->ciphers) {
            unsigned char cbytes[3];
            cbytes[0] = (cipherId >> 8) & 0xFF;
            cbytes[1] = cipherId & 0xFF;
            cbytes[2] = 0;
#if HAVE_LIBSSL_SSL_CIPHER_FIND
            const SSL_CIPHER *c = SSL_CIPHER_find(ssl, cbytes);
#else
            const SSL_METHOD *method = SSLv23_method();
            const SSL_CIPHER *c = method->get_cipher_by_char(cbytes);
#endif
            if (c != NULL) {
                if (!strCiphers.isEmpty())
                    strCiphers.append(":");
                strCiphers.append(SSL_CIPHER_get_name(c));
            }
        }
        if (!strCiphers.isEmpty())
            SSL_set_cipher_list(ssl, strCiphers.c_str());
    }

#if defined(SSL_OP_NO_COMPRESSION) /* XXX: OpenSSL 0.9.8k lacks SSL_OP_NO_COMPRESSION */
    if (!details->compressionSupported)
        SSL_set_options(ssl, SSL_OP_NO_COMPRESSION);
#endif

#if defined(TLSEXT_STATUSTYPE_ocsp)
    if (details->tlsStatusRequest)
        SSL_set_tlsext_status_type(ssl, TLSEXT_STATUSTYPE_ocsp);
#endif

#if defined(TLSEXT_TYPE_application_layer_protocol_negotiation)
    if (!details->tlsAppLayerProtoNeg.isEmpty()) {
        if (bumpMode == Ssl::bumpPeek)
            SSL_set_alpn_protos(ssl, (const unsigned char*)details->tlsAppLayerProtoNeg.rawContent(), details->tlsAppLayerProtoNeg.length());
        else {
            static const unsigned char supported_protos[] = {8, 'h','t','t', 'p', '/', '1', '.', '1'};
            SSL_set_alpn_protos(ssl, supported_protos, sizeof(supported_protos));
        }
    }
#endif
}