        apr_status_t rv;

        if ((rv = apr_dir_open(&dir, ca_path, ptemp)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02211)
                    "Failed to open Certificate Path `%s'",
                    ca_path);
            ssl_die(s);
        }

        while ((apr_dir_read(&direntry, finfo_flags, dir)) == APR_SUCCESS) {
            const char *file;
            if (direntry.filetype == APR_DIR) {
                continue; /* don't try to load directories */
