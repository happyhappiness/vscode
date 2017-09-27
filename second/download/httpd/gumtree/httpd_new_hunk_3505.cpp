                thisinfo.filetype == APR_NOFILE) {
                /* That was fun, nothing left for us here
                 */
                break;
            }
            else if (thisinfo.filetype != APR_DIR) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00038)
                              "Forbidden: %s doesn't point to "
                              "a file or directory",
                              r->filename);
                return r->status = HTTP_FORBIDDEN;
            }

