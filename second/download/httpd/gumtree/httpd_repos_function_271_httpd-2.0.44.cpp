dav_lookup_result dav_lookup_uri(const char *uri, request_rec * r,
                                 int must_be_absolute)
{
    dav_lookup_result result = { 0 };
    const char *scheme;
    apr_port_t port;
    apr_uri_t comp;
    char *new_file;
    const char *domain;

    /* first thing to do is parse the URI into various components */
    if (apr_uri_parse(r->pool, uri, &comp) != APR_SUCCESS) {
        result.err.status = HTTP_BAD_REQUEST;
        result.err.desc = "Invalid syntax in Destination URI.";
        return result;
    }

    /* the URI must be an absoluteURI (WEBDAV S9.3) */
    if (comp.scheme == NULL && must_be_absolute) {
        result.err.status = HTTP_BAD_REQUEST;
        result.err.desc = "Destination URI must be an absolute URI.";
        return result;
    }

    /* the URI must not have a query (args) or a fragment */
    if (comp.query != NULL || comp.fragment != NULL) {
        result.err.status = HTTP_BAD_REQUEST;
        result.err.desc =
            "Destination URI contains invalid components "
            "(a query or a fragment).";
        return result;
    }

    /* If the scheme or port was provided, then make sure that it matches
       the scheme/port of this request. If the request must be absolute,
       then require the (explicit/implicit) scheme/port be matching.

       ### hmm. if a port wasn't provided (does the parse return port==0?),
       ### but we're on a non-standard port, then we won't detect that the
       ### URI's port implies the wrong one.
    */
    if (comp.scheme != NULL || comp.port != 0 || must_be_absolute)
    {
        /* ### not sure this works if the current request came in via https: */
        scheme = r->parsed_uri.scheme;
        if (scheme == NULL)
            scheme = ap_http_method(r);

        /* insert a port if the URI did not contain one */
        if (comp.port == 0)
            comp.port = apr_uri_port_of_scheme(comp.scheme);

        /* now, verify that the URI uses the same scheme as the current.
           request. the port must match our port.
        */
        apr_sockaddr_port_get(&port, r->connection->local_addr);
        if (strcasecmp(comp.scheme, scheme) != 0
#ifdef APACHE_PORT_HANDLING_IS_BUSTED
            || comp.port != port
#endif
            ) {
            result.err.status = HTTP_BAD_GATEWAY;
            result.err.desc = apr_psprintf(r->pool,
                                           "Destination URI refers to "
                                           "different scheme or port "
                                           "(%s://hostname:%d)" APR_EOL_STR
                                           "(want: %s://hostname:%d)",
                                           comp.scheme ? comp.scheme : scheme,
                                           comp.port ? comp.port : port,
                                           scheme, port);
            return result;
        }
    }

    /* we have verified the scheme, port, and general structure */

    /*
    ** Hrm.  IE5 will pass unqualified hostnames for both the 
    ** Host: and Destination: headers.  This breaks the
    ** http_vhost.c::matches_aliases function.
    **
    ** For now, qualify unqualified comp.hostnames with
    ** r->server->server_hostname.
    **
    ** ### this is a big hack. Apache should provide a better way.
    ** ### maybe the admin should list the unqualified hosts in a
    ** ### <ServerAlias> block?
    */
    if (comp.hostname != NULL
        && strrchr(comp.hostname, '.') == NULL
        && (domain = strchr(r->server->server_hostname, '.')) != NULL) {
        comp.hostname = apr_pstrcat(r->pool, comp.hostname, domain, NULL);
    }

    /* now, if a hostname was provided, then verify that it represents the
       same server as the current connection. note that we just use our
       port, since we've verified the URI matches ours */
#ifdef APACHE_PORT_HANDLING_IS_BUSTED
    if (comp.hostname != NULL &&
        !ap_matches_request_vhost(r, comp.hostname, port)) {
        result.err.status = HTTP_BAD_GATEWAY;
        result.err.desc = "Destination URI refers to a different server.";
        return result;
    }
#endif

    /* we have verified that the requested URI denotes the same server as
       the current request. Therefore, we can use ap_sub_req_lookup_uri() */

    /* reconstruct a URI as just the path */
    new_file = apr_uri_unparse(r->pool, &comp, APR_URI_UNP_OMITSITEPART);

    /*
     * Lookup the URI and return the sub-request. Note that we use the
     * same HTTP method on the destination. This allows the destination
     * to apply appropriate restrictions (e.g. readonly).
     */
    result.rnew = ap_sub_req_method_uri(r->method, new_file, r, NULL);

    return result;
}