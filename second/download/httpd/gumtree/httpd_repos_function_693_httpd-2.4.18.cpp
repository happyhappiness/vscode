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
        load_x509_info(ptemp, sk, pkp->cert_file);
    }

    if (pkp->cert_path) {
        apr_dir_t *dir;
        apr_finfo_t dirent;
        apr_int32_t finfo_flags = APR_FINFO_TYPE|APR_FINFO_NAME;
    
        if (apr_dir_open(&dir, pkp->cert_path, ptemp) == APR_SUCCESS) {
            while ((apr_dir_read(&dirent, finfo_flags, dir)) == APR_SUCCESS) {
                const char *fullname;

                if (dirent.filetype == APR_DIR) {
                    continue; /* don't try to load directories */
                }
        
                fullname = apr_pstrcat(ptemp,
                                       pkp->cert_path, "/", dirent.name,
                                       NULL);
                load_x509_info(ptemp, sk, fullname);
            }

            apr_dir_close(dir);
        }
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