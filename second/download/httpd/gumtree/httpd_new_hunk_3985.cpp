                            "about \"%s\" in parsed file %s";
            }
        }

        if (error_fmt) {
            ret = -1;
            /* Intentional no APLOGNO */
            /* error_fmt provides APLOGNO */
            ap_log_rerror(APLOG_MARK, APLOG_ERR,
                          rv, r, error_fmt, to_send, r->filename);
        }

        if (rr) ap_destroy_sub_req(rr);

