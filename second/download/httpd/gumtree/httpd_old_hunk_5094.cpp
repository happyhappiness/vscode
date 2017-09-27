**
**  OpenSSL Callback Functions
**  _________________________________________________________________
*/

/*
 * Handle out temporary RSA private keys on demand
 *
 * The background of this as the TLSv1 standard explains it:
 *
 * | D.1. Temporary RSA keys
 * |
 * |    US Export restrictions limit RSA keys used for encryption to 512
 * |    bits, but do not place any limit on lengths of RSA keys used for
 * |    signing operations. Certificates often need to be larger than 512
 * |    bits, since 512-bit RSA keys are not secure enough for high-value
 * |    transactions or for applications requiring long-term security. Some
 * |    certificates are also designated signing-only, in which case they
 * |    cannot be used for key exchange.
 * |
 * |    When the public key in the certificate cannot be used for encryption,
 * |    the server signs a temporary RSA key, which is then exchanged. In
 * |    exportable applications, the temporary RSA key should be the maximum
 * |    allowable length (i.e., 512 bits). Because 512-bit RSA keys are
 * |    relatively insecure, they should be changed often. For typical
 * |    electronic commerce applications, it is suggested that keys be
 * |    changed daily or every 500 transactions, and more often if possible.
 * |    Note that while it is acceptable to use the same temporary key for
 * |    multiple transactions, it must be signed each time it is used.
 * |
 * |    RSA key generation is a time-consuming process. In many cases, a
 * |    low-priority process can be assigned the task of key generation.
 * |    Whenever a new key is completed, the existing temporary key can be
 * |    replaced with the new one.
 *
 * XXX: base on comment above, if thread support is enabled,
 * we should spawn a low-priority thread to generate new keys
 * on the fly.
 *
 * So we generated 512 and 1024 bit temporary keys on startup
 * which we now just hand out on demand....
 */

RSA *ssl_callback_TmpRSA(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfigFromConn(c);
    int idx;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                  "handing out temporary %d bit RSA key", keylen);

    /* doesn't matter if export flag is on,
     * we won't be asked for keylen > 512 in that case.
     * if we are asked for a keylen > 1024, it is too expensive
     * to generate on the fly.
     * XXX: any reason not to generate 2048 bit keys at startup?
     */

    switch (keylen) {
      case 512:
        idx = SSL_TMP_KEY_RSA_512;
        break;

      case 1024:
      default:
        idx = SSL_TMP_KEY_RSA_1024;
    }

    return (RSA *)mc->pTmpKeys[idx];
}

/*
 * Hand out the already generated DH parameters...
 */
DH *ssl_callback_TmpDH(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfigFromConn(c);
    int idx;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                  "handing out temporary %d bit DH key", keylen);

    switch (keylen) {
      case 512:
        idx = SSL_TMP_KEY_DH_512;
        break;

      case 1024:
      default:
        idx = SSL_TMP_KEY_DH_1024;
    }

    return (DH *)mc->pTmpKeys[idx];
}

#ifndef OPENSSL_NO_EC
EC_KEY *ssl_callback_TmpECDH(SSL *ssl, int export, int keylen)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    SSLModConfigRec *mc = myModConfigFromConn(c);
    int idx;

    /* XXX Uses 256-bit key for now. TODO: support other sizes. */
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                  "handing out temporary 256 bit ECC key");

    switch (keylen) {
      case 256:
      default:
        idx = SSL_TMP_KEY_EC_256;
    }

    return (EC_KEY *)mc->pTmpKeys[idx];
}
#endif

/*
 * This OpenSSL callback function is called when OpenSSL
 * does client authentication and verifies the certificate chain.
 */
int ssl_callback_SSLVerify(int ok, X509_STORE_CTX *ctx)
