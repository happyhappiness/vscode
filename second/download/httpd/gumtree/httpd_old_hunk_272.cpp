                    /* if we are done, leave */
                    if (TRUE == finish) {
                        break;
                    }
                }
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
                         "proxy: end body send");
        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
                         "proxy: header only");
        }
    }

    if ( conf->error_override ) {
        /* the code above this checks for 'OK' which is what the hook expects */
