         * request-uri), so lets do a more sophisticated match
         */
        apr_uri_t r_uri, d_uri;

        copy_uri_components(&r_uri, resp->psd_request_uri, r);
        if (apr_uri_parse(r->pool, resp->uri, &d_uri) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: invalid uri <%s> in Authorization header",
                          resp->uri);
            return HTTP_BAD_REQUEST;
        }

        if (d_uri.hostname) {
            ap_unescape_url(d_uri.hostname);
