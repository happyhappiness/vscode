
    /* do syntatic check.
     * We break the URL into host, port, path, search
     */
    port = def_port;
    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err)
        return HTTP_BAD_REQUEST;

    /* now parse path/search args, according to rfc1738 */
    /* N.B. if this isn't a true proxy request, then the URL _path_
     * has already been decoded.  True proxy requests have r->uri
     * == r->unparsed_uri, and no others have that property.
     */
