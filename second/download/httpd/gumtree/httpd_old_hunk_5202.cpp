     * would accept all clients also issued by this CA. Obviously this
     * isn't what we want in this situation. So this feature here exists
     * to allow one to explicity configure CA certificates which are
     * used only for the server certificate chain.
     */
    if (!chain) {
        return;
    }

    for (i = 0; (i < SSL_AIDX_MAX) && mctx->pks->cert_files[i]; i++) {
        if (strEQ(mctx->pks->cert_files[i], chain)) {
            skip_first = TRUE;
            break;
        }
    }

    n = SSL_CTX_use_certificate_chain(mctx->ssl_ctx,
                                      (char *)chain,
                                      skip_first, NULL);
    if (n < 0) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01903)
                "Failed to configure CA certificate chain!");
        ssl_die(s);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01904)
                 "Configuring server certificate chain "
                 "(%d CA certificate%s)",
                 n, n == 1 ? "" : "s");
}

static void ssl_init_ctx(server_rec *s,
                         apr_pool_t *p,
                         apr_pool_t *ptemp,
                         modssl_ctx_t *mctx)
{
    ssl_init_ctx_protocol(s, p, ptemp, mctx);

    ssl_init_ctx_session_cache(s, p, ptemp, mctx);

    ssl_init_ctx_callbacks(s, p, ptemp, mctx);

    ssl_init_ctx_verify(s, p, ptemp, mctx);

    ssl_init_ctx_cipher_suite(s, p, ptemp, mctx);

    ssl_init_ctx_crl(s, p, ptemp, mctx);

    if (mctx->pks) {
        /* XXX: proxy support? */
        ssl_init_ctx_cert_chain(s, p, ptemp, mctx);
#ifdef HAVE_TLSEXT
        ssl_init_ctx_tls_extensions(s, p, ptemp, mctx);
#endif
    }
}

static int ssl_server_import_cert(server_rec *s,
                                  modssl_ctx_t *mctx,
                                  const char *id,
                                  int idx)
{
    SSLModConfigRec *mc = myModConfig(s);
    ssl_asn1_t *asn1;
    const unsigned char *ptr;
    const char *type = ssl_asn1_keystr(idx);
    X509 *cert;

    if (!(asn1 = ssl_asn1_table_get(mc->tPublicCert, id))) {
        return FALSE;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02232)
                 "Configuring %s server certificate", type);

    ptr = asn1->cpData;
    if (!(cert = d2i_X509(NULL, &ptr, asn1->nData))) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02233)
                "Unable to import %s server certificate", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }

    if (SSL_CTX_use_certificate(mctx->ssl_ctx, cert) <= 0) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02234)
                "Unable to configure %s server certificate", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }

#ifdef HAVE_OCSP_STAPLING
    if ((mctx->pkp == FALSE) && (mctx->stapling_enabled == TRUE)) {
        if (!ssl_stapling_init_cert(s, mctx, cert)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02235)
                         "Unable to configure server certificate for stapling");
        }
    }
#endif

    mctx->pks->certs[idx] = cert;

    return TRUE;
}

static int ssl_server_import_key(server_rec *s,
                                 modssl_ctx_t *mctx,
                                 const char *id,
                                 int idx)
{
    SSLModConfigRec *mc = myModConfig(s);
    ssl_asn1_t *asn1;
    const unsigned char *ptr;
    const char *type = ssl_asn1_keystr(idx);
    int pkey_type;
    EVP_PKEY *pkey;

#ifdef HAVE_ECC
    if (idx == SSL_AIDX_ECC)
      pkey_type = EVP_PKEY_EC;
    else
#endif
    pkey_type = (idx == SSL_AIDX_RSA) ? EVP_PKEY_RSA : EVP_PKEY_DSA;

    if (!(asn1 = ssl_asn1_table_get(mc->tPrivateKey, id))) {
        return FALSE;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02236)
                 "Configuring %s server private key", type);

    ptr = asn1->cpData;
    if (!(pkey = d2i_PrivateKey(pkey_type, NULL, &ptr, asn1->nData)))
    {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02237)
                "Unable to import %s server private key", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }

    if (SSL_CTX_use_PrivateKey(mctx->ssl_ctx, pkey) <= 0) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02238)
                "Unable to configure %s server private key", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }

    /*
     * XXX: wonder if this is still needed, this is old todo doc.
     * (see http://www.psy.uq.edu.au/~ftp/Crypto/ssleay/TODO.html)
     */
    if ((pkey_type == EVP_PKEY_DSA) && mctx->pks->certs[idx]) {
        EVP_PKEY *pubkey = X509_get_pubkey(mctx->pks->certs[idx]);

        if (pubkey && EVP_PKEY_missing_parameters(pubkey)) {
            EVP_PKEY_copy_parameters(pubkey, pkey);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02239)
                    "Copying DSA parameters from private key to certificate");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            EVP_PKEY_free(pubkey);
        }
    }

    mctx->pks->keys[idx] = pkey;

    return TRUE;
}

static void ssl_check_public_cert(server_rec *s,
                                  apr_pool_t *ptemp,
                                  X509 *cert,
                                  int type)
{
    int is_ca, pathlen;

    if (!cert) {
        return;
    }

    /*
     * Some information about the certificate(s)
     */

    if (SSL_X509_isSGC(cert)) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01905)
                     "%s server certificate enables "
                     "Server Gated Cryptography (SGC)",
                     ssl_asn1_keystr(type));
    }

    if (SSL_X509_getBC(cert, &is_ca, &pathlen)) {
        if (is_ca) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01906)
                         "%s server certificate is a CA certificate "
                         "(BasicConstraints: CA == TRUE !?)",
                         ssl_asn1_keystr(type));
        }

        if (pathlen > 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01907)
                         "%s server certificate is not a leaf certificate "
                         "(BasicConstraints: pathlen == %d > 0 !?)",
                         ssl_asn1_keystr(type), pathlen);
        }
    }

    if (SSL_X509_match_name(ptemp, cert, (const char *)s->server_hostname,
                            TRUE, s) == FALSE) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01909)
                     "%s certificate configured for %s does NOT include "
                     "an ID which matches the server name",
                     ssl_asn1_keystr(type), (mySrvConfig(s))->vhost_id);
    }
}

static void ssl_init_server_certs(server_rec *s,
                                  apr_pool_t *p,
                                  apr_pool_t *ptemp,
                                  modssl_ctx_t *mctx)
{
    const char *rsa_id, *dsa_id;
#ifdef HAVE_ECC
    const char *ecc_id;
    EC_GROUP *ecparams;
    int nid;
    EC_KEY *eckey;
#endif
    const char *vhost_id = mctx->sc->vhost_id;
    int i;
    int have_rsa, have_dsa;
    DH *dhparams;
#ifdef HAVE_ECC
    int have_ecc;
#endif

    rsa_id = ssl_asn1_table_keyfmt(ptemp, vhost_id, SSL_AIDX_RSA);
    dsa_id = ssl_asn1_table_keyfmt(ptemp, vhost_id, SSL_AIDX_DSA);
#ifdef HAVE_ECC
    ecc_id = ssl_asn1_table_keyfmt(ptemp, vhost_id, SSL_AIDX_ECC);
#endif

    have_rsa = ssl_server_import_cert(s, mctx, rsa_id, SSL_AIDX_RSA);
    have_dsa = ssl_server_import_cert(s, mctx, dsa_id, SSL_AIDX_DSA);
#ifdef HAVE_ECC
    have_ecc = ssl_server_import_cert(s, mctx, ecc_id, SSL_AIDX_ECC);
#endif

    if (!(have_rsa || have_dsa
#ifdef HAVE_ECC
        || have_ecc
#endif
)) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01910)
                "Oops, no " KEYTYPES " server certificate found "
                "for '%s:%d'?!", s->server_hostname, s->port);
        ssl_die(s);
    }

    for (i = 0; i < SSL_AIDX_MAX; i++) {
        ssl_check_public_cert(s, ptemp, mctx->pks->certs[i], i);
    }

    have_rsa = ssl_server_import_key(s, mctx, rsa_id, SSL_AIDX_RSA);
    have_dsa = ssl_server_import_key(s, mctx, dsa_id, SSL_AIDX_DSA);
#ifdef HAVE_ECC
    have_ecc = ssl_server_import_key(s, mctx, ecc_id, SSL_AIDX_ECC);
#endif

    if (!(have_rsa || have_dsa
#ifdef HAVE_ECC
        || have_ecc
#endif
          )) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01911)
                "Oops, no " KEYTYPES " server private key found?!");
        ssl_die(s);
    }

    /*
     * Try to read DH parameters from the (first) SSLCertificateFile
     */
    if ((mctx->pks->cert_files[0] != NULL) &&
        (dhparams = ssl_dh_GetParamFromFile(mctx->pks->cert_files[0]))) {
        SSL_CTX_set_tmp_dh(mctx->ssl_ctx, dhparams);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02540)
                     "Custom DH parameters (%d bits) for %s loaded from %s",
                     BN_num_bits(dhparams->p), vhost_id,
                     mctx->pks->cert_files[0]);
    }

#ifdef HAVE_ECC
    /*
     * Similarly, try to read the ECDH curve name from SSLCertificateFile...
     */
    if ((mctx->pks->cert_files[0] != NULL) &&
        (ecparams = ssl_ec_GetParamFromFile(mctx->pks->cert_files[0])) &&
        (nid = EC_GROUP_get_curve_name(ecparams)) &&
        (eckey = EC_KEY_new_by_curve_name(nid))) {
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx, eckey);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02541)
                     "ECDH curve %s for %s specified in %s",
                     OBJ_nid2sn(nid), vhost_id, mctx->pks->cert_files[0]);
    }
    /*
     * ...otherwise, configure NIST P-256 (required to enable ECDHE)
     */
    else {
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx,
                             EC_KEY_new_by_curve_name(NID_X9_62_prime256v1));
    }
#endif
}

#ifdef HAVE_TLS_SESSION_TICKETS
static void ssl_init_ticket_key(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,
                                modssl_ctx_t *mctx)
{
    apr_status_t rv;
    apr_file_t *fp;
    apr_size_t len;
    char buf[TLSEXT_TICKET_KEY_LEN];
    char *path;
    modssl_ticket_key_t *ticket_key = mctx->ticket_key;

    if (!ticket_key->file_path) {
        return;
    }

    path = ap_server_root_relative(p, ticket_key->file_path);

    rv = apr_file_open(&fp, path, APR_READ|APR_BINARY,
                       APR_OS_DEFAULT, ptemp);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02286)
                     "Failed to open ticket key file %s: (%d) %pm",
                     path, rv, &rv);
        ssl_die(s);
    }

    rv = apr_file_read_full(fp, &buf[0], TLSEXT_TICKET_KEY_LEN, &len);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02287)
                     "Failed to read %d bytes from %s: (%d) %pm",
                     TLSEXT_TICKET_KEY_LEN, path, rv, &rv);
        ssl_die(s);
    }

    memcpy(ticket_key->key_name, buf, 16);
    memcpy(ticket_key->hmac_secret, buf + 16, 16);
    memcpy(ticket_key->aes_key, buf + 32, 16);

    if (!SSL_CTX_set_tlsext_ticket_key_cb(mctx->ssl_ctx,
                                          ssl_callback_SessionTicket)) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01913)
                     "Unable to initialize TLS session ticket key callback "
                     "(incompatible OpenSSL version?)");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02288)
                 "TLS session ticket key for %s successfully loaded from %s",
                 (mySrvConfig(s))->vhost_id, path);
}
#endif

static void ssl_init_proxy_certs(server_rec *s,
                                 apr_pool_t *p,
                                 apr_pool_t *ptemp,
                                 modssl_ctx_t *mctx)
{
    int n, ncerts = 0;
    STACK_OF(X509_INFO) *sk;
    modssl_pk_proxy_t *pkp = mctx->pkp;
    STACK_OF(X509) *chain;
    X509_STORE_CTX *sctx;
    X509_STORE *store = SSL_CTX_get_cert_store(mctx->ssl_ctx);

    SSL_CTX_set_client_cert_cb(mctx->ssl_ctx,
                               ssl_callback_proxy_cert);

    if (!(pkp->cert_file || pkp->cert_path)) {
        return;
    }

    sk = sk_X509_INFO_new_null();

    if (pkp->cert_file) {
        SSL_X509_INFO_load_file(ptemp, sk, pkp->cert_file);
