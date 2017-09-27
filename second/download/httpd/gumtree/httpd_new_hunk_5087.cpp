     */
    if ((mctx->pkp == FALSE) && (mctx->stapling_enabled == TRUE)) {
        modssl_init_stapling(s, p, ptemp, mctx);
    }
#endif

#ifdef HAVE_SRP
    /*
     * TLS-SRP support
     */
    if (mctx->srp_vfile != NULL) {
        int err;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02308)
