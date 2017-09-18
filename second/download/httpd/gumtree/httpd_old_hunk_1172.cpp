        if (d_uri.path) {
            ap_unescape_url(d_uri.path);
        }
        if (d_uri.query) {
            ap_unescape_url(d_uri.query);
        }

        if (r->method_number == M_CONNECT) {
            if (strcmp(resp->uri, r_uri.hostinfo)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Digest: uri mismatch - <%s> does not match "
                              "request-uri <%s>", resp->uri, r_uri.hostinfo);
