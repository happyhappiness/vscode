    /*
     * Process CA certificate path files
     */
    if (ca_path) {
        apr_dir_t *dir;
        apr_finfo_t direntry;
        apr_int32_t finfo_flags = APR_FINFO_MIN|APR_FINFO_NAME;
        apr_status_t rv;

        if ((rv = apr_dir_open(&dir, ca_path, ptemp)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                    "Failed to open SSLCACertificatePath `%s'",
                    ca_path);
