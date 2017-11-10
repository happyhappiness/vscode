const char  *ssl_cmd_SSLStrictSNIVHostCheck(cmd_parms *cmd, void *dcfg, int flag)
{
#ifndef OPENSSL_NO_TLSEXT
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    sc->strict_sni_vhost_check = flag ? SSL_ENABLED_TRUE : SSL_ENABLED_FALSE;

    return NULL;
#else
    return "SSLStrictSNIVHostCheck failed; OpenSSL is not built with support "
           "for TLS extensions and SNI indication. Refer to the "
           "documentation, and build a compatible version of OpenSSL.";
#endif
}