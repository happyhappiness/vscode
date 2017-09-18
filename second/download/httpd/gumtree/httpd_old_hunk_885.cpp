    int access_status;

    /* Ignore embedded %2F's in path for proxy requests */
    if (!r->proxyreq && r->parsed_uri.path) {
        access_status = ap_unescape_url(r->parsed_uri.path);
        if (access_status) {
            return access_status;
        }
    }

    ap_getparents(r->uri);     /* OK --- shrinking transformations... */

