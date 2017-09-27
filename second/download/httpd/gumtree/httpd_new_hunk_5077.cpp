                    }

                    /* XXX Why don't we cleanup here?  (logic from AJP) */
                }
                break;

            case AP_FCGI_STDERR:
                /* TODO: Should probably clean up this logging a bit... */
                if (clen) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01071)
                                  "Got error '%s'", readbuf);
                }

                if (clen > readbuflen) {
                    clen -= readbuflen;
                    goto recv_again;
                }
                break;

            case AP_FCGI_END_REQUEST:
                done = 1;
                break;

            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01072)
                              "Got bogus record %d", type);
                break;
            }

            if (plen) {
                rv = get_data_full(conn, readbuf, plen);
                if (rv != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  APLOGNO(02537) "Error occurred reading padding");
                    break;
                }
            }
        }
    }

