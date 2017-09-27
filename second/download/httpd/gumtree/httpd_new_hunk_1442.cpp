**
**  OpenSSL Callback Functions
**  _________________________________________________________________
*/

/*
 * Hand out the already generated DH parameters...
 * Based on the authentication strength.
 */
DH *ssl_callback_TmpDH(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    EVP_PKEY *pkey;
    int type;

    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                  "handing out built-in DH parameters for %d-bit "
                  "authenticated connection", keylen);

#ifdef SSL_CERT_SET_SERVER
    /*
     * When multiple certs/keys are configured for the SSL_CTX: make sure
     * that we get the private key which is indeed used for the current
     * SSL connection (available in OpenSSL 1.0.2 or later only)
     */
    SSL_set_current_cert(ssl, SSL_CERT_SET_SERVER);
#endif
    pkey = SSL_get_privatekey(ssl);
    type = pkey ? EVP_PKEY_type(pkey->type) : EVP_PKEY_NONE;

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

    return ssl_dh_GetTmpParam(keylen);
}

/*
 * This OpenSSL callback function is called when OpenSSL
 * does client authentication and verifies the certificate chain.
 */
int ssl_callback_SSLVerify(int ok, X509_STORE_CTX *ctx)
