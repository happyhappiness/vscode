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
    }

    if (pkp->cert_path) {
        SSL_X509_INFO_load_path(ptemp, sk, pkp->cert_path);
    }

    if ((ncerts = sk_X509_INFO_num(sk)) <= 0) {
        sk_X509_INFO_free(sk);
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(02206)
                     "no client certs found for SSL proxy");
        return;
    }

    /* Check that all client certs have got certificates and private
     * keys. */
    for (n = 0; n < ncerts; n++) {
        X509_INFO *inf = sk_X509_INFO_value(sk, n);

        if (!inf->x509 || !inf->x_pkey) {
            sk_X509_INFO_free(sk);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, s, APLOGNO(02252)
                         "incomplete client cert configured for SSL proxy "
                         "(missing or encrypted private key?)");
            ssl_die();
            return;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02207)
                 "loaded %d client certs for SSL proxy",
                 ncerts);
    pkp->certs = sk;


    if (!pkp->ca_cert_file || !store) {
        return;
    }

    /* Load all of the CA certs and construct a chain */
    pkp->ca_certs = (STACK_OF(X509) **) apr_pcalloc(p, ncerts * sizeof(sk));
    sctx = X509_STORE_CTX_new();

    if (!sctx) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02208)
                     "SSL proxy client cert initialization failed");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die();
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
}