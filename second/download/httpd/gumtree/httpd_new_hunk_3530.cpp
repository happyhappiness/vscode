                r->err_headers_out = apr_table_overlay(r->pool,
                    r->err_headers_out, cookie_table);
            }
            return cond_status;
        }

        if (trace_log) {
            if (first_header)
                ap_log_rerror(SCRIPT_LOG_MARK, APLOG_TRACE4, 0, r,
                              "Headers from script '%s':",
                              apr_filepath_name_get(r->filename));
            ap_log_rerror(SCRIPT_LOG_MARK, APLOG_TRACE4, 0, r, "  %s", w);
        }

        /* if we see a bogus header don't ignore it. Shout and scream */

#if APR_CHARSET_EBCDIC
            /* Chances are that we received an ASCII header text instead of
             * the expected EBCDIC header lines. Try to auto-detect:
             */
