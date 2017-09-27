
            ap_fcgi_header_fields_from_array(&version, &type, &rid,
                                             &clen, &plen, farray);

            if (version != AP_FCGI_VERSION_1) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01068)
                              "Got bogus version %d", (int) header.version);
                rv = APR_EINVAL;
                break;
            }

            if (rid != request_id) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01069)
