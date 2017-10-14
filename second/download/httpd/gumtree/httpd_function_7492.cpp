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
    }

    if (pkp->cert_path) {
        SSL_X509_INFO_load_path(ptemp, sk, pkp->cert_path);
    }

    if ((ncerts = sk_X509_INFO_num(sk)) <= 0) {
        sk_X509_INFO_free(sk);
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(02206)
                     "no client certs found for SSL proxy");
        return APR_SUCCESS;
    }

    /* Check that all client certs have got certificates and private
     * keys. */
    for (n = 0; n < ncerts; n++) {
        X509_INFO *inf = sk_X509_INFO_value(sk, n);

        if (!inf->x509 || !inf->x_pkey || !inf->x_pkey->dec_pkey ||
            inf->enc_data) {
            sk_X509_INFO_free(sk);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, s, APLOGNO(02252)
                         "incomplete client cert configured for SSL proxy "
                         "(missing or encrypted private key?)");
            return ssl_die(s);
        }
        
        if (X509_check_private_key(inf->x509, inf->x_pkey->dec_pkey) != 1) {
            ssl_log_xerror(SSLLOG_MARK, APLOG_STARTUP, 0, ptemp, s, inf->x509,
                           APLOGNO(02326) "proxy client certificate and "
                           "private key do not match");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            return ssl_die(s);
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02207)
                 "loaded %d client certs for SSL proxy",
                 ncerts);
    pkp->certs = sk;


    if (!pkp->ca_cert_file || !store) {
        return APR_SUCCESS;
    }

    /* If SSLProxyMachineCertificateChainFile is configured, load all
     * the CA certs and have OpenSSL attempt to construct a full chain
     * from each configured end-entity cert up to a root.  This will
     * allow selection of the correct cert given a list of root CA
     * names in the certificate request from the server.  */
    pkp->ca_certs = (STACK_OF(X509) **) apr_pcalloc(p, ncerts * sizeof(sk));
    sctx = X509_STORE_CTX_new();

    if (!sctx) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02208)
                     "SSL proxy client cert initialization failed");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        return ssl_die(s);
    }

    X509_STORE_load_locations(store, pkp->ca_cert_file, NULL);

    for (n = 0; n < ncerts; n++) {
        int i;

        X509_INFO *inf = sk_X509_INFO_value(pkp->certs, n);
        X509_STORE_CTX_init(sctx, store, inf->x509, NULL);

        /* Attempt to verify the client cert */
        if (X509_verify_cert(sctx) != 1) {
            int err = X509_STORE_CTX_get_error(sctx);
            ssl_log_xerror(SSLLOG_MARK, APLOG_WARNING, 0, ptemp, s, inf->x509,
                           APLOGNO(02270) "SSL proxy client cert chain "
                           "verification failed: %s :",
                           X509_verify_cert_error_string(err));
        }

        /* Clear X509_verify_cert errors */
        ERR_clear_error();

        /* Obtain a copy of the verified chain */
        chain = X509_STORE_CTX_get1_chain(sctx);

        if (chain != NULL) {
            /* Discard end entity cert from the chain */
            X509_free(sk_X509_shift(chain));

            if ((i = sk_X509_num(chain)) > 0) {
                /* Store the chain for later use */
                pkp->ca_certs[n] = chain;
            }
            else {
                /* Discard empty chain */
                sk_X509_pop_free(chain, X509_free);
                pkp->ca_certs[n] = NULL;
            }

            ssl_log_xerror(SSLLOG_MARK, APLOG_DEBUG, 0, ptemp, s, inf->x509,
                           APLOGNO(02271)
                           "loaded %i intermediate CA%s for cert %i: ",
                           i, i == 1 ? "" : "s", n);
            if (i > 0) {
                int j;
                for (j = 0; j < i; j++) {
                    ssl_log_xerror(SSLLOG_MARK, APLOG_DEBUG, 0, ptemp, s,
                                   sk_X509_value(chain, j), "%i:", j);
                }
            }
        }

        /* get ready for next X509_STORE_CTX_init */
        X509_STORE_CTX_cleanup(sctx);
    }

    X509_STORE_CTX_free(sctx);

    return APR_SUCCESS;
}

static apr_status_t ssl_init_proxy_ctx(server_rec *s,
                                       apr_pool_t *p,
                                       apr_pool_t *ptemp,
                                       SSLSrvConfigRec *sc)
{
    apr_status_t rv;

    if ((rv = ssl_init_ctx(s, p, ptemp, sc->proxy)) != APR_SUCCESS) {
        return rv;
    }

    if ((rv = ssl_init_proxy_certs(s, p, ptemp, sc->proxy)) != APR_SUCCESS) {
        return rv;
    }

    return APR_SUCCESS;
}

static apr_status_t ssl_init_server_ctx(server_rec *s,
                                        apr_pool_t *p,
                                        apr_pool_t *ptemp,
                                        SSLSrvConfigRec *sc,
                                        apr_array_header_t *pphrases)
{
    apr_status_t rv;
#ifdef HAVE_SSL_CONF_CMD
    ssl_ctx_param_t *param = (ssl_ctx_param_t *)sc->server->ssl_ctx_param->elts;
    SSL_CONF_CTX *cctx = sc->server->ssl_ctx_config;
    int i;
#endif

    /*
     *  Check for problematic re-initializations
     */
    if (sc->server->ssl_ctx) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02569)
                     "Illegal attempt to re-initialise SSL for server "
                     "(SSLEngine On should go in the VirtualHost, not in global scope.)");
        return APR_EGENERAL;
    }

    if ((rv = ssl_init_ctx(s, p, ptemp, sc->server)) != APR_SUCCESS) {
        return rv;
    }

    if ((rv = ssl_init_server_certs(s, p, ptemp, sc->server, pphrases))
        != APR_SUCCESS) {
        return rv;
    }

#ifdef HAVE_SSL_CONF_CMD
    SSL_CONF_CTX_set_ssl_ctx(cctx, sc->server->ssl_ctx);
    for (i = 0; i < sc->server->ssl_ctx_param->nelts; i++, param++) {
        ERR_clear_error();
        if (SSL_CONF_cmd(cctx, param->name, param->value) <= 0) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02407)
                         "\"SSLOpenSSLConfCmd %s %s\" failed for %s",
                         param->name, param->value, sc->vhost_id);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            return ssl_die(s);
        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02556)
                         "\"SSLOpenSSLConfCmd %s %s\" applied to %s",
                         param->name, param->value, sc->vhost_id);
        }
    }

    if (SSL_CONF_CTX_finish(cctx) == 0) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02547)
                         "SSL_CONF_CTX_finish() failed");
            SSL_CONF_CTX_free(cctx);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            return ssl_die(s);
    }
    SSL_CONF_CTX_free(cctx);
#endif

    if (SSL_CTX_check_private_key(sc->server->ssl_ctx) != 1) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02572)
                     "Failed to configure at least one certificate and key "
                     "for %s", sc->vhost_id);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        return ssl_die(s);
    }

#if defined(HAVE_OCSP_STAPLING) && defined(SSL_CTRL_SET_CURRENT_CERT)
    /*
     * OpenSSL 1.0.2 and later allows iterating over all SSL_CTX certs
     * by means of SSL_CTX_set_current_cert. Enabling stapling at this
     * (late) point makes sure that we catch both certificates loaded
     * via SSLCertificateFile and SSLOpenSSLConfCmd Certificate.
     */
    if (sc->server->stapling_enabled == TRUE) {
        X509 *cert;
        int i = 0;
        int ret = SSL_CTX_set_current_cert(sc->server->ssl_ctx,
                                           SSL_CERT_SET_FIRST);
        while (ret) {
            cert = SSL_CTX_get0_certificate(sc->server->ssl_ctx);
            if (!cert || !ssl_stapling_init_cert(s, sc->server, cert)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02604)
                             "Unable to configure certificate %s:%d "
                             "for stapling", sc->vhost_id, i);
            }
            ret = SSL_CTX_set_current_cert(sc->server->ssl_ctx,
                                           SSL_CERT_SET_NEXT);
            i++;
        }
    }
#endif

#ifdef HAVE_TLS_SESSION_TICKETS
    if ((rv = ssl_init_ticket_key(s, p, ptemp, sc->server)) != APR_SUCCESS) {
        return rv;
    }
#endif

    return APR_SUCCESS;
}

/*
 * Configure a particular server
 */
apr_status_t ssl_init_ConfigureServer(server_rec *s,
                                      apr_pool_t *p,
                                      apr_pool_t *ptemp,
                                      SSLSrvConfigRec *sc,
                                      apr_array_header_t *pphrases)
{
    apr_status_t rv;

    /* Initialize the server if SSL is enabled or optional.
     */
    if ((sc->enabled == SSL_ENABLED_TRUE) || (sc->enabled == SSL_ENABLED_OPTIONAL)) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01914)
                     "Configuring server %s for SSL protocol", sc->vhost_id);
        if ((rv = ssl_init_server_ctx(s, p, ptemp, sc, pphrases))
            != APR_SUCCESS) {
            return rv;
        }
    }

    if (sc->proxy_enabled) {
        if ((rv = ssl_init_proxy_ctx(s, p, ptemp, sc)) != APR_SUCCESS) {
            return rv;
        }
    }

    return APR_SUCCESS;
}

apr_status_t ssl_init_CheckServers(server_rec *base_server, apr_pool_t *p)
{
    server_rec *s, *ps;
    SSLSrvConfigRec *sc;
    apr_hash_t *table;
    const char *key;
    apr_ssize_t klen;

    BOOL conflict = FALSE;

    /*
     * Give out warnings when a server has HTTPS configured
     * for the HTTP port or vice versa
     */
    for (s = base_server; s; s = s->next) {
        sc = mySrvConfig(s);

        if ((sc->enabled == SSL_ENABLED_TRUE) && (s->port == DEFAULT_HTTP_PORT)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         base_server, APLOGNO(01915)
                         "Init: (%s) You configured HTTPS(%d) "
                         "on the standard HTTP(%d) port!",
                         ssl_util_vhostid(p, s),
                         DEFAULT_HTTPS_PORT, DEFAULT_HTTP_PORT);
        }

        if ((sc->enabled == SSL_ENABLED_FALSE) && (s->port == DEFAULT_HTTPS_PORT)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         base_server, APLOGNO(01916)
                         "Init: (%s) You configured HTTP(%d) "
                         "on the standard HTTPS(%d) port!",
                         ssl_util_vhostid(p, s),
                         DEFAULT_HTTP_PORT, DEFAULT_HTTPS_PORT);
        }
    }

    /*
     * Give out warnings when more than one SSL-aware virtual server uses the
     * same IP:port. This doesn't work because mod_ssl then will always use
     * just the certificate/keys of one virtual host (which one cannot be said
     * easily - but that doesn't matter here).
     */
    table = apr_hash_make(p);

    for (s = base_server; s; s = s->next) {
        char *addr;

        sc = mySrvConfig(s);

        if (!((sc->enabled == SSL_ENABLED_TRUE) && s->addrs)) {
            continue;
        }

        apr_sockaddr_ip_get(&addr, s->addrs->host_addr);
        key = apr_psprintf(p, "%s:%u", addr, s->addrs->host_port);
        klen = strlen(key);

        if ((ps = (server_rec *)apr_hash_get(table, key, klen))) {
#ifndef HAVE_TLSEXT
            int level = APLOG_WARNING;
            const char *problem = "conflict";
#else
            int level = APLOG_DEBUG;
            const char *problem = "overlap";
#endif
            ap_log_error(APLOG_MARK, level, 0, base_server,
                         "Init: SSL server IP/port %s: "
                         "%s (%s:%d) vs. %s (%s:%d)",
                         problem, ssl_util_vhostid(p, s),
                         (s->defn_name ? s->defn_name : "unknown"),
                         s->defn_line_number,
                         ssl_util_vhostid(p, ps),
                         (ps->defn_name ? ps->defn_name : "unknown"),
                         ps->defn_line_number);
            conflict = TRUE;
            continue;
        }

        apr_hash_set(table, key, klen, s);
    }

    if (conflict) {
#ifndef HAVE_TLSEXT
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(01917)
                     "Init: You should not use name-based "
                     "virtual hosts in conjunction with SSL!!");
#else
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(02292)
                     "Init: Name-based SSL virtual hosts only "
                     "work for clients with TLS server name indication "
                     "support (RFC 4366)");
#endif
    }

    return APR_SUCCESS;
}

static int ssl_init_FindCAList_X509NameCmp(const X509_NAME * const *a,
                                           const X509_NAME * const *b)
{
    return(X509_NAME_cmp(*a, *b));
}

static void ssl_init_PushCAList(STACK_OF(X509_NAME) *ca_list,
                                server_rec *s, apr_pool_t *ptemp,
                                const char *file)
{
    int n;
    STACK_OF(X509_NAME) *sk;

    sk = (STACK_OF(X509_NAME) *)
             SSL_load_client_CA_file(file);

    if (!sk) {
        return;
    }

    for (n = 0; n < sk_X509_NAME_num(sk); n++) {
        X509_NAME *name = sk_X509_NAME_value(sk, n);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02209)
                     "CA certificate: %s",
                     SSL_X509_NAME_to_string(ptemp, name, 0));

        /*
         * note that SSL_load_client_CA_file() checks for duplicates,
         * but since we call it multiple times when reading a directory
         * we must also check for duplicates ourselves.
         */

        if (sk_X509_NAME_find(ca_list, name) < 0) {
            /* this will be freed when ca_list is */
            sk_X509_NAME_push(ca_list, name);
        }
        else {
            /* need to free this ourselves, else it will leak */
            X509_NAME_free(name);
        }
    }

    sk_X509_NAME_free(sk);
}

STACK_OF(X509_NAME) *ssl_init_FindCAList(server_rec *s,
                                         apr_pool_t *ptemp,
                                         const char *ca_file,
                                         const char *ca_path)
{
    STACK_OF(X509_NAME) *ca_list;

    /*
     * Start with a empty stack/list where new
     * entries get added in sorted order.
     */
    ca_list = sk_X509_NAME_new(ssl_init_FindCAList_X509NameCmp);

    /*
     * Process CA certificate bundle file
     */
    if (ca_file) {
        ssl_init_PushCAList(ca_list, s, ptemp, ca_file);
        /*
         * If ca_list is still empty after trying to load ca_file
         * then the file failed to load, and users should hear about that.
         */
        if (sk_X509_NAME_num(ca_list) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02210)
                    "Failed to load SSLCACertificateFile: %s", ca_file);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
        }
    }

    /*
     * Process CA certificate path files
     */
    if (ca_path) {
        apr_dir_t *dir;
        apr_finfo_t direntry;
        apr_int32_t finfo_flags = APR_FINFO_TYPE|APR_FINFO_NAME;
        apr_status_t rv;

        if ((rv = apr_dir_open(&dir, ca_path, ptemp)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02211)
                    "Failed to open Certificate Path `%s'",
                    ca_path);
            sk_X509_NAME_pop_free(ca_list, X509_NAME_free);
            return NULL;
        }

        while ((apr_dir_read(&direntry, finfo_flags, dir)) == APR_SUCCESS) {
            const char *file;
            if (direntry.filetype == APR_DIR) {
                continue; /* don't try to load directories */
            }
            file = apr_pstrcat(ptemp, ca_path, "/", direntry.name, NULL);
            ssl_init_PushCAList(ca_list, s, ptemp, file);
        }

        apr_dir_close(dir);
    }

    /*
     * Cleanup
     */
    (void) sk_X509_NAME_set_cmp_func(ca_list, NULL);

    return ca_list;
}