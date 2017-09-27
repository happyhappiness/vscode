        default:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          APLOGNO(02508) "%s: Got bogus FastCGI record type "
                          "%d", fn, type);
            break;
        }
        /* Leave on above switch's inner error. */
        if (rv != APR_SUCCESS) {
            break;
        }

        /*
         * Read/discard any trailing padding.
         */
        if (plen) {
            rv = recv_data_full(conf, r, s, readbuf, plen);
