                if (thisinfo.filetype == APR_REG) {
                    /* That was fun, nothing left for us here
                     */
                    break;
                }
                else if (thisinfo.filetype != APR_DIR) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "symlink doesn't point to a file or "
                                  "directory: %s",
                                  r->filename);
                    return r->status = HTTP_FORBIDDEN;
                }
            }
