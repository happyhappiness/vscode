        if (status != APR_SUCCESS) {
            return HTTP_BAD_REQUEST;
        }
    }

    if (bytes_streamed != cl_val) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: client %s given Content-Length did not match"
                     " number of body bytes read", r->connection->remote_ip);
        return HTTP_BAD_REQUEST;
    }

    if (header_brigade) {
        /* we never sent the header brigade since there was no request
         * body; send it now with the flush flag
