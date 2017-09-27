        /* be safe; only files in this directory or below allowed */
        rv = apr_filepath_merge(&newpath, NULL, tag_val,
                                APR_FILEPATH_SECUREROOTTEST |
                                APR_FILEPATH_NOTABSOLUTE, r->pool);

        if (rv != APR_SUCCESS) {
            error_fmt = APLOGNO(02668) "unable to access file \"%s\" "
                        "in parsed file %s";
        }
        else {
            /* note: it is okay to pass NULL for the "next filter" since
               we never attempt to "run" this sub request. */
            rr = ap_sub_req_lookup_file(newpath, r, NULL);

            if (rr->status == HTTP_OK && rr->finfo.filetype != APR_NOFILE) {
                to_send = rr->filename;
                if ((rv = apr_stat(finfo, to_send,
                    APR_FINFO_GPROT | APR_FINFO_MIN, rr->pool)) != APR_SUCCESS
                    && rv != APR_INCOMPLETE) {
                    error_fmt = APLOGNO(02669) "unable to get information "
                                "about \"%s\" in parsed file %s";
                }
            }
            else {
                error_fmt = APLOGNO(02670) "unable to lookup information "
                            "about \"%s\" in parsed file %s";
            }
        }

        if (error_fmt) {
            ret = -1;
            ap_log_rerror(APLOG_MARK, APLOG_ERR,
