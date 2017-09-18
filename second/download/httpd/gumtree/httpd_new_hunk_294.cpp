{
    /*
     * check for important parameters and the
     * possibility that the user forgot to set them.
     */
    if (!mctx->pks->cert_files[0]) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "No SSL Certificate set [hint: SSLCertificateFile]");
        ssl_die();
    }

    /*
     *  Check for problematic re-initializations
     */
    if (mctx->pks->certs[SSL_AIDX_RSA] ||
        mctx->pks->certs[SSL_AIDX_DSA])
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Illegal attempt to re-initialise SSL for server "
                "(theoretically shouldn't happen!)");
        ssl_die();
    }
}

