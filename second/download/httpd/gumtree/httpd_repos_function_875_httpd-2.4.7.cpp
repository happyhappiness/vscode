DH *ssl_callback_TmpDH(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    EVP_PKEY *pkey = SSL_get_privatekey(ssl);
    int type = pkey ? EVP_PKEY_type(pkey->type) : EVP_PKEY_NONE;

    /*
     * OpenSSL will call us with either keylen == 512 or keylen == 1024
     * (see the definition of SSL_EXPORT_PKEYLENGTH in ssl_locl.h).
     * Adjust the DH parameter length according to the size of the
     * RSA/DSA private key used for the current connection, and always
     * use at least 1024-bit parameters.
     * Note: This may cause interoperability issues with implementations
     * which limit their DH support to 1024 bit - e.g. Java 7 and earlier.
     * In this case, SSLCertificateFile can be used to specify fixed
     * 1024-bit DH parameters (with the effect that OpenSSL skips this
     * callback).
     */
    if ((type == EVP_PKEY_RSA) || (type == EVP_PKEY_DSA)) {
        keylen = EVP_PKEY_bits(pkey);
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                  "handing out built-in DH parameters for %d-bit authenticated connection", keylen);

    if (keylen >= 4096)
        return get_dh4096();
    else if (keylen >= 3072)
        return get_dh3072();
    else if (keylen >= 2048)
        return get_dh2048();
    else
        return get_dh1024();
}