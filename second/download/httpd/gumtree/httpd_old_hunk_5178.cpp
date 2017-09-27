    if (APR_SUCCESS != apr_uri_parse(p, *url, uri)) {
        return ap_proxyerror(r, HTTP_BAD_REQUEST,
                             apr_pstrcat(p,"URI cannot be parsed: ", *url,
                                         NULL));
    }
    if (!uri->port) {
        uri->port = apr_uri_port_of_scheme(uri->scheme);
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00944)
                 "connecting %s to %s:%d", *url, uri->hostname, uri->port);

    /*
