            apr_bucket_delete(e);
        }

        apr_brigade_length(input_brigade, 1, &bytes);

        if (bytes_spooled + bytes > MAX_MEM_SPOOL) {
            /*
             * LimitRequestBody does not affect Proxy requests (Should it?).
             * Let it take effect if we decide to store the body in a
             * temporary file on disk.
             */
            if (bytes_spooled + bytes > limit) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01088)
                              "Request body is larger than the configured "
                              "limit of %" APR_OFF_T_FMT, limit);
                return HTTP_REQUEST_ENTITY_TOO_LARGE;
            }
            /* can't spool any more in memory; write latest brigade to disk */
            if (tmpfile == NULL) {
                const char *temp_dir;
                char *template;

                status = apr_temp_dir_get(&temp_dir, p);
                if (status != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01089)
                                  "search for temporary directory failed");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                apr_filepath_merge(&template, temp_dir,
                                   "modproxy.tmp.XXXXXX",
                                   APR_FILEPATH_NATIVE, p);
                status = apr_file_mktemp(&tmpfile, template, 0, p);
                if (status != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01090)
                                  "creation of temporary file in directory "
                                  "%s failed", temp_dir);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
            }
            for (e = APR_BRIGADE_FIRST(input_brigade);
                 e != APR_BRIGADE_SENTINEL(input_brigade);
                 e = APR_BUCKET_NEXT(e)) {
