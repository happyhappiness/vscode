    int access_status;

    /* Ignore embedded %2F's in path for proxy requests */
    if (!r->proxyreq && r->parsed_uri.path) {
        access_status = ap_unescape_url(r->parsed_uri.path);
        if (access_status) {
            if (access_status == HTTP_NOT_FOUND) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "found %%2f (encoded '/') in URI "
                              "(decoded='%s'), returning 404",
                              r->parsed_uri.path);
            }
            return access_status;
        }
    }

    ap_getparents(r->uri);     /* OK --- shrinking transformations... */

