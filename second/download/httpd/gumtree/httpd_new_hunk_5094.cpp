**
**  OpenSSL Callback Functions
**  _________________________________________________________________
*/

/*
 * Grab well-defined DH parameters from OpenSSL, see <openssl/bn.h>
 * (get_rfc*) for all available primes.
 */
#define make_get_dh(rfc,size,gen) \
static DH *get_dh##size(void) \
{ \
    DH *dh; \
    if (!(dh = DH_new())) { \
        return NULL; \
    } \
    dh->p = get_##rfc##_prime_##size(NULL); \
    BN_dec2bn(&dh->g, #gen); \
    if (!dh->p || !dh->g) { \
        DH_free(dh); \
        return NULL; \
    } \
    return dh; \
}

/*
 * Prepare DH parameters from 1024 to 4096 bits, in 1024-bit increments
 */
make_get_dh(rfc2409, 1024, 2)
make_get_dh(rfc3526, 2048, 2)
make_get_dh(rfc3526, 3072, 2)
make_get_dh(rfc3526, 4096, 2)

/*
 * Hand out standard DH parameters, based on the authentication strength
 */
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

/*
 * This OpenSSL callback function is called when OpenSSL
 * does client authentication and verifies the certificate chain.
 */
int ssl_callback_SSLVerify(int ok, X509_STORE_CTX *ctx)
