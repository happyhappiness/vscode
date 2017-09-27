         * level, allowing content/resource filters to run later, if
         * necessary. */

        rv = ap_get_brigade(r->proto_input_filters, tempb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, 8192);
        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02015)
                          "could not read request body for SSL buffer");
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        /* Iterate through the returned brigade: setaside each bucket
         * into the context's pool and move it into the brigade. */
