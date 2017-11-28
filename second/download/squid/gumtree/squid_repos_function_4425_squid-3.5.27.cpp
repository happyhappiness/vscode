void
Ssl::Bio::sslFeatures::applyToSSL(SSL *ssl, Ssl::BumpMode bumpMode) const
{
    // To increase the possibility for bumping after peek mode selection or
    // splicing after stare mode selection it is good to set the
    // SSL protocol version.
    // The SSL_set_ssl_method is not the correct method because it will strict
    // SSL version which can be used to the SSL version used for client hello message.
    // For example will prevent comunnicating with a tls1.0 server if the
    // client sent and tlsv1.2 Hello message.
    //SSL_set_ssl_method(ssl, Ssl::method(features.toSquidSSLVersion()));
#if defined(TLSEXT_NAMETYPE_host_name)
    if (!serverName.isEmpty()) {
        SSL_set_tlsext_host_name(ssl, serverName.c_str());
    }
#endif
    if (!clientRequestedCiphers.empty())
        SSL_set_cipher_list(ssl, clientRequestedCiphers.c_str());
#if defined(SSL_OP_NO_COMPRESSION) /* XXX: OpenSSL 0.9.8k lacks SSL_OP_NO_COMPRESSION */
    if (compressMethod == 0)
        SSL_set_options(ssl, SSL_OP_NO_COMPRESSION);
#endif

#if defined(TLSEXT_STATUSTYPE_ocsp)
    if (tlsStatusRequest)
        SSL_set_tlsext_status_type(ssl, TLSEXT_STATUSTYPE_ocsp);
#endif

#if defined(TLSEXT_TYPE_application_layer_protocol_negotiation)
    if (!tlsAppLayerProtoNeg.isEmpty()) {
        if (bumpMode == Ssl::bumpPeek)
            SSL_set_alpn_protos(ssl, (const unsigned char*)tlsAppLayerProtoNeg.rawContent(), tlsAppLayerProtoNeg.length());
        else {
            static const unsigned char supported_protos[] = {8, 'h','t','t', 'p', '/', '1', '.', '1'};
            SSL_set_alpn_protos(ssl, supported_protos, sizeof(supported_protos));
        }
    }
#endif
}