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
            ssl_die();
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
