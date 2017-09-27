                break;

            case AP_FCGI_STDERR:
                /* TODO: Should probably clean up this logging a bit... */
                if (clen) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01071)
                                  "Got error '%s'", iobuf);
                }

                if (clen > readbuflen) {
                    clen -= readbuflen;
                    goto recv_again;
                }
