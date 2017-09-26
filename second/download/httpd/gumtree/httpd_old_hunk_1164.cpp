                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "proxy: error processing end");
                    output_failed = 1;
                }
                /* XXX: what about flush here? See mod_jk */
                data_sent = 1;
                break;
            default:
                backend_failed = 1;
                break;
        }

