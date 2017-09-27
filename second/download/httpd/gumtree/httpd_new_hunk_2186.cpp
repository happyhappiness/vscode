                char *template;

                status = apr_temp_dir_get(&temp_dir, p);
                if (status != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                                 "proxy: search for temporary directory failed");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                apr_filepath_merge(&template, temp_dir,
                                   "modproxy.tmp.XXXXXX",
                                   APR_FILEPATH_NATIVE, p);
                status = apr_file_mktemp(&tmpfile, template, 0, p);
                if (status != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                                 "proxy: creation of temporary file in directory %s failed",
                                 temp_dir);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
            }
            for (e = APR_BRIGADE_FIRST(input_brigade);
                 e != APR_BRIGADE_SENTINEL(input_brigade);
                 e = APR_BUCKET_NEXT(e)) {
                const char *data;
