bool
Ssl::setClientSNI(SSL *ssl, const char *fqdn)
{
    //The SSL_CTRL_SET_TLSEXT_HOSTNAME is a openssl macro which indicates
    // if the TLS servername extension (SNI) is enabled in openssl library.
#if defined(SSL_CTRL_SET_TLSEXT_HOSTNAME)
    if (!SSL_set_tlsext_host_name(ssl, fqdn)) {
        const int ssl_error = ERR_get_error();
        debugs(83, 3,  "WARNING: unable to set TLS servername extension (SNI): " <<
               ERR_error_string(ssl_error, NULL) << "\n");
        return false;
    }
    return true;
#else
    debugs(83, 7,  "no support for TLS servername extension (SNI)\n");
    return false;
#endif
}