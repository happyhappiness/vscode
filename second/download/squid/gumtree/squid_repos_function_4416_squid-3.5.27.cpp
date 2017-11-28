int Ssl::Bio::sslFeatures::toSquidSSLVersion() const
{
    if (sslVersion == SSL2_VERSION)
        return 2;
    else if (sslVersion == SSL3_VERSION)
        return 3;
    else if (sslVersion == TLS1_VERSION)
        return 4;
#if OPENSSL_VERSION_NUMBER >= 0x10001000L
    else if (sslVersion == TLS1_1_VERSION)
        return 5;
    else if (sslVersion == TLS1_2_VERSION)
        return 6;
#endif
    else
        return 1;
}