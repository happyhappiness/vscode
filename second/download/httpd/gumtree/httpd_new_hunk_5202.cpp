     * would accept all clients also issued by this CA. Obviously this
     * isn't what we want in this situation. So this feature here exists
     * to allow one to explicity configure CA certificates which are
     * used only for the server certificate chain.
     */
    if (!chain) {
        return APR_SUCCESS;
    }

    for (i = 0; (i < mctx->pks->cert_files->nelts) &&
         APR_ARRAY_IDX(mctx->pks->cert_files, i, const char *); i++) {
        if (strEQ(APR_ARRAY_IDX(mctx->pks->cert_files, i, const char *), chain)) {
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
        return ssl_die(s);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01904)
                 "Configuring server certificate chain "
                 "(%d CA certificate%s)",
                 n, n == 1 ? "" : "s");

    return APR_SUCCESS;
}

static apr_status_t ssl_init_ctx(server_rec *s,
                                 apr_pool_t *p,
                                 apr_pool_t *ptemp,
                                 modssl_ctx_t *mctx)
{
    apr_status_t rv;

    if ((rv = ssl_init_ctx_protocol(s, p, ptemp, mctx)) != APR_SUCCESS) {
        return rv;
    }

    ssl_init_ctx_session_cache(s, p, ptemp, mctx);

    ssl_init_ctx_callbacks(s, p, ptemp, mctx);

    if ((rv = ssl_init_ctx_verify(s, p, ptemp, mctx)) != APR_SUCCESS) {
        return rv;
    }

    if ((rv = ssl_init_ctx_cipher_suite(s, p, ptemp, mctx)) != APR_SUCCESS) {
        return rv;
    }

    if ((rv = ssl_init_ctx_crl(s, p, ptemp, mctx)) != APR_SUCCESS) {
        return rv;
    }

    if (mctx->pks) {
        /* XXX: proxy support? */
        if ((rv = ssl_init_ctx_cert_chain(s, p, ptemp, mctx)) != APR_SUCCESS) {
            return rv;
        }
#ifdef HAVE_TLSEXT
        if ((rv = ssl_init_ctx_tls_extensions(s, p, ptemp, mctx)) !=
            APR_SUCCESS) {
            return rv;
        }
#endif
    }

    return APR_SUCCESS;
}

static void ssl_check_public_cert(server_rec *s,
                                  apr_pool_t *ptemp,
                                  X509 *cert,
                                  const char *key_id)
{
    int is_ca, pathlen;

    if (!cert) {
        return;
    }

    /*
     * Some information about the certificate(s)
     */

    if (SSL_X509_getBC(cert, &is_ca, &pathlen)) {
        if (is_ca) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01906)
                         "%s server certificate is a CA certificate "
                         "(BasicConstraints: CA == TRUE !?)", key_id);
        }

        if (pathlen > 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01907)
                         "%s server certificate is not a leaf certificate "
                         "(BasicConstraints: pathlen == %d > 0 !?)",
                         key_id, pathlen);
        }
    }

    if (SSL_X509_match_name(ptemp, cert, (const char *)s->server_hostname,
                            TRUE, s) == FALSE) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01909)
                     "%s server certificate does NOT include an ID "
                     "which matches the server name", key_id);
    }
}

/* prevent OpenSSL from showing its "Enter PEM pass phrase:" prompt */
static int ssl_no_passwd_prompt_cb(char *buf, int size, int rwflag,
                                   void *userdata) {
   return 0;
}

static apr_status_t ssl_init_server_certs(server_rec *s,
                                          apr_pool_t *p,
                                          apr_pool_t *ptemp,
                                          modssl_ctx_t *mctx,
                                          apr_array_header_t *pphrases)
{
    SSLModConfigRec *mc = myModConfig(s);
    const char *vhost_id = mctx->sc->vhost_id, *key_id, *certfile, *keyfile;
    int i;
    X509 *cert;
    DH *dhparams;
#ifdef HAVE_ECC
    EC_GROUP *ecparams;
    int nid;
    EC_KEY *eckey;
#endif
#ifndef HAVE_SSL_CONF_CMD
    SSL *ssl;
#endif

    /* no OpenSSL default prompts for any of the SSL_CTX_use_* calls, please */
    SSL_CTX_set_default_passwd_cb(mctx->ssl_ctx, ssl_no_passwd_prompt_cb);

    /* Iterate over the SSLCertificateFile array */
    for (i = 0; (i < mctx->pks->cert_files->nelts) &&
                (certfile = APR_ARRAY_IDX(mctx->pks->cert_files, i,
                                          const char *));
         i++) {
        key_id = apr_psprintf(ptemp, "%s:%d", vhost_id, i);

        /* first the certificate (public key) */
        if (mctx->cert_chain) {
            if ((SSL_CTX_use_certificate_file(mctx->ssl_ctx, certfile,
                                              SSL_FILETYPE_PEM) < 1)) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02561)
                             "Failed to configure certificate %s, check %s",
                             key_id, certfile);
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                return APR_EGENERAL;
            }
        } else {
            if ((SSL_CTX_use_certificate_chain_file(mctx->ssl_ctx,
                                                    certfile) < 1)) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02562)
                             "Failed to configure certificate %s (with chain),"
                             " check %s", key_id, certfile);
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                return APR_EGENERAL;
            }
        }

        /* and second, the private key */
        keyfile = APR_ARRAY_IDX(mctx->pks->key_files, i, const char *);
        if (keyfile == NULL)
            keyfile = certfile;

        ERR_clear_error();

        if ((SSL_CTX_use_PrivateKey_file(mctx->ssl_ctx, keyfile,
                                         SSL_FILETYPE_PEM) < 1) &&
            (ERR_GET_FUNC(ERR_peek_last_error())
                != X509_F_X509_CHECK_PRIVATE_KEY)) {
            ssl_asn1_t *asn1;
            EVP_PKEY *pkey;
            const unsigned char *ptr;

            ERR_clear_error();

            /* perhaps it's an encrypted private key, so try again */
            ssl_load_encrypted_pkey(s, ptemp, i, keyfile, &pphrases);

            if (!(asn1 = ssl_asn1_table_get(mc->tPrivateKey, key_id)) ||
                !(ptr = asn1->cpData) ||
                !(pkey = d2i_AutoPrivateKey(NULL, &ptr, asn1->nData)) ||
                (SSL_CTX_use_PrivateKey(mctx->ssl_ctx, pkey) < 1)) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02564)
                             "Failed to configure encrypted (?) private key %s,"
                             " check %s", key_id, keyfile);
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                return APR_EGENERAL;
            }
        }

        if (SSL_CTX_check_private_key(mctx->ssl_ctx) < 1) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02565)
                         "Certificate and private key %s from %s and %s "
                         "do not match", key_id, certfile, keyfile);
            return APR_EGENERAL;
        }

#ifdef HAVE_SSL_CONF_CMD
        /* 
         * workaround for those OpenSSL versions where SSL_CTX_get0_certificate
         * is not yet available: create an SSL struct which we dispose of
         * as soon as we no longer need access to the cert. (Strictly speaking,
         * SSL_CTX_get0_certificate does not depend on the SSL_CONF stuff,
         * but there's no reliable way to check for its existence, so we
         * assume that if SSL_CONF is available, it's OpenSSL 1.0.2 or later,
         * and SSL_CTX_get0_certificate is implemented.)
         */
        if (!(cert = SSL_CTX_get0_certificate(mctx->ssl_ctx))) {
#else
        ssl = SSL_new(mctx->ssl_ctx);
	if (ssl) {
            /* Workaround bug in SSL_get_certificate in OpenSSL 0.9.8y */
            SSL_set_connect_state(ssl);
            cert = SSL_get_certificate(ssl);
        }
        if (!ssl || !cert) {
#endif
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02566)
                         "Unable to retrieve certificate %s", key_id);
#ifndef HAVE_SSL_CONF_CMD
            if (ssl)
                SSL_free(ssl);
#endif
            return APR_EGENERAL;
        }

        /* warn about potential cert issues */
        ssl_check_public_cert(s, ptemp, cert, key_id);

#if defined(HAVE_OCSP_STAPLING) && !defined(SSL_CTRL_SET_CURRENT_CERT)
        /* 
         * OpenSSL up to 1.0.1: configure stapling as we go. In 1.0.2
         * and later, there's SSL_CTX_set_current_cert, which allows
         * iterating over all certs in an SSL_CTX (including those possibly
         * loaded via SSLOpenSSLConfCmd Certificate), so for 1.0.2 and
         * later, we defer to the code in ssl_init_server_ctx.
         */
        if ((mctx->stapling_enabled == TRUE) &&
            !ssl_stapling_init_cert(s, mctx, cert)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02567)
                         "Unable to configure certificate %s for stapling",
                         key_id);
        }
#endif

#ifndef HAVE_SSL_CONF_CMD
        SSL_free(ssl);
#endif

        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02568)
                     "Certificate and private key %s configured from %s and %s",
                     key_id, certfile, keyfile);
    }

    /*
     * Try to read DH parameters from the (first) SSLCertificateFile
     */
    if ((certfile = APR_ARRAY_IDX(mctx->pks->cert_files, 0, const char *)) &&
        (dhparams = ssl_dh_GetParamFromFile(certfile))) {
        SSL_CTX_set_tmp_dh(mctx->ssl_ctx, dhparams);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02540)
                     "Custom DH parameters (%d bits) for %s loaded from %s",
                     BN_num_bits(dhparams->p), vhost_id, certfile);
    }

#ifdef HAVE_ECC
    /*
     * Similarly, try to read the ECDH curve name from SSLCertificateFile...
     */
    if ((certfile != NULL) && 
        (ecparams = ssl_ec_GetParamFromFile(certfile)) &&
        (nid = EC_GROUP_get_curve_name(ecparams)) &&
        (eckey = EC_KEY_new_by_curve_name(nid))) {
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx, eckey);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02541)
                     "ECDH curve %s for %s specified in %s",
                     OBJ_nid2sn(nid), vhost_id, certfile);
    }
    /*
     * ...otherwise, enable auto curve selection (OpenSSL 1.0.2 and later)
     * or configure NIST P-256 (required to enable ECDHE for earlier versions)
     */
    else {
#if defined(SSL_CTX_set_ecdh_auto)
        SSL_CTX_set_ecdh_auto(mctx->ssl_ctx, 1);
#else
        SSL_CTX_set_tmp_ecdh(mctx->ssl_ctx,
                             EC_KEY_new_by_curve_name(NID_X9_62_prime256v1));
#endif
    }
#endif

    return APR_SUCCESS;
}

#ifdef HAVE_TLS_SESSION_TICKETS
static apr_status_t ssl_init_ticket_key(server_rec *s,
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
        return APR_SUCCESS;
    }

    path = ap_server_root_relative(p, ticket_key->file_path);

    rv = apr_file_open(&fp, path, APR_READ|APR_BINARY,
                       APR_OS_DEFAULT, ptemp);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02286)
                     "Failed to open ticket key file %s: (%d) %pm",
                     path, rv, &rv);
        return ssl_die(s);
    }

    rv = apr_file_read_full(fp, &buf[0], TLSEXT_TICKET_KEY_LEN, &len);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02287)
                     "Failed to read %d bytes from %s: (%d) %pm",
                     TLSEXT_TICKET_KEY_LEN, path, rv, &rv);
        return ssl_die(s);
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
        return ssl_die(s);
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02288)
                 "TLS session ticket key for %s successfully loaded from %s",
                 (mySrvConfig(s))->vhost_id, path);

    return APR_SUCCESS;
}
#endif

static apr_status_t ssl_init_proxy_certs(server_rec *s,
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
        return APR_SUCCESS;
    }

    sk = sk_X509_INFO_new_null();

    if (pkp->cert_file) {
        SSL_X509_INFO_load_file(ptemp, sk, pkp->cert_file);
