                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01072)
                              "Got bogus record %d", type);
                break;
            }

            if (plen) {
                rv = get_data_full(conn, iobuf, plen);
                if (rv != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  APLOGNO(02537) "Error occurred reading padding");
                    break;
                }
            }
