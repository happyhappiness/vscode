        (dhparams = ssl_dh_GetParamFromFile(mctx->pks->cert_files[0]))) {
        SSL_CTX_set_tmp_dh(mctx->ssl_ctx, dhparams);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "Custom DH parameters (%d bits) for %s loaded from %s",
                     BN_num_bits(dhparams->p), vhost_id,
                     mctx->pks->cert_files[0]);
        DH_free(dhparams);
    }

#ifndef OPENSSL_NO_EC
    /*
     * Similarly, try to read the ECDH curve name from SSLCertificateFile...
     */
