     * Process CA certificate path files
     */
    if (ca_path) {
        apr_dir_t *dir;
        apr_finfo_t direntry;
        apr_int32_t finfo_flags = APR_FINFO_MIN|APR_FINFO_NAME;

        if (apr_dir_open(&dir, ca_path, ptemp) != APR_SUCCESS) {
            ssl_log(s, SSL_LOG_ERROR|SSL_ADD_ERRNO|SSL_INIT,
                    "Failed to open SSLCACertificatePath `%s'",
                    ca_path);
            ssl_die();
        }

        while ((apr_dir_read(&direntry, finfo_flags, dir)) == APR_SUCCESS) {
