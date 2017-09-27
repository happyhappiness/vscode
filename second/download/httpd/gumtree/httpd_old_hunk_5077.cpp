                    }

                    /* XXX Why don't we cleanup here?  (logic from AJP) */
                }
                break;

            case FCGI_STDERR:
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

            case FCGI_END_REQUEST:
                done = 1;
                break;

            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01072)
                              "Got bogus record %d", type);
                break;
            }

            if (plen) {
                readbuflen = plen;

                rv = get_data(conn, readbuf, &readbuflen);
                if (rv != APR_SUCCESS) {
                    break;
                }
            }
        }
    }

