                                         &include_module, r);

                if (!error_fmt && ap_run_sub_req(rr)) {
                    error_fmt = "unable to include \"%s\" in parsed file %s";
                }
                if (error_fmt) {
                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|loglevel,
                                  0, r, error_fmt, tag_val, r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                }

                /* destroy the sub request */
                if (rr != NULL) {
                    ap_destroy_sub_req(rr);
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" to tag include in %s",
                            tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            }
        }
    }
