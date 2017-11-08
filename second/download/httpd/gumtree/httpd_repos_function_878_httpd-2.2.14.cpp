static char *ssl_var_lookup_ssl_compress_meth(SSL *ssl)
{
    char *result = "NULL";
#ifdef OPENSSL_VERSION_NUMBER
#if (OPENSSL_VERSION_NUMBER >= 0x00908000)
    SSL_SESSION *pSession = SSL_get_session(ssl);

    if (pSession) {
        switch (pSession->compress_meth) {
        case 0:
            /* default "NULL" already set */
            break;

            /* Defined by RFC 3749, deflate is coded by "1" */
        case 1:
            result = "DEFLATE";
            break;

            /* IANA assigned compression number for LZS */
        case 0x40:
            result = "LZS";
            break;

        default:
            result = "UNKNOWN";
            break;
        }
    }
#endif
#endif
    return result;
}