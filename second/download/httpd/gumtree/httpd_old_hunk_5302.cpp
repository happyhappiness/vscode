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
