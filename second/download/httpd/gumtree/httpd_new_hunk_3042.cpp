        if (status != APR_SUCCESS) {
            return HTTP_BAD_REQUEST;
        }
    }

    if (bytes_streamed != cl_val) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01087)
                      "client %s given Content-Length did not match"
                      " number of body bytes read", r->connection->client_ip);
        return HTTP_BAD_REQUEST;
    }

    if (header_brigade) {
        /* we never sent the header brigade since there was no request
         * body; send it now with the flush flag
