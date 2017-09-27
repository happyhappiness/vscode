
        if (!error_fmt && ((status = ap_run_sub_req(rr)))) {
            error_fmt = "unable to include \"%s\" in parsed file %s, subrequest returned %d";
        }

        if (error_fmt) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, error_fmt, tag_val,
                    r->filename, status ? status : rr ? rr->status : 0);
            if (last_error) {
                /* onerror threw an error, give up completely */
                break;
            }
