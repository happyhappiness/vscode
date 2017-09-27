    ca_list = sk_X509_NAME_new(ssl_init_FindCAList_X509NameCmp);

    /*
     * Process CA certificate bundle file
     */
    if (ca_file) {
        ssl_init_PushCAList(ca_list, s, ca_file);
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
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
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
            ssl_init_PushCAList(ca_list, s, file);
        }

        apr_dir_close(dir);
    }

    /*
