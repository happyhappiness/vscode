                if (ap_pass_brigade(r->output_filters,
                                    output_brigade) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "proxy: error processing body");
                    isok = 0;
                }
                break;
            default:
                isok = 0;
                break;
        }

