            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01067)
                              "Failed to read FastCGI header");
                break;
            }

#ifdef FCGI_DUMP_HEADERS
            ap_log_rdata(APLOG_MARK, APLOG_DEBUG, r, "FastCGI header",
                         farray, AP_FCGI_HEADER_LEN, 0);
#endif

            ap_fcgi_header_fields_from_array(&version, &type, &rid,
                                             &clen, &plen, farray);

            if (version != AP_FCGI_VERSION_1) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01068)
