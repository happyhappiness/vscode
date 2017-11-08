apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
                                        char**key)
{
    char *port_str, *scheme, *hn;
    const char * hostname;
    int i;

    /*
     * Use the canonical name to improve cache hit rate, but only if this is
     * not a proxy request or if this is a reverse proxy request.
     * We need to handle both cases in the same manner as for the reverse proxy
     * case we have the following situation:
     *
     * If a cached entry is looked up by mod_cache's quick handler r->proxyreq
     * is still unset in the reverse proxy case as it only gets set in the
     * translate name hook (either by ProxyPass or mod_rewrite) which is run
     * after the quick handler hook. This is different to the forward proxy
     * case where it gets set before the quick handler is run (in the
     * post_read_request hook).
     * If a cache entry is created by the CACHE_SAVE filter we always have
     * r->proxyreq set correctly.
     * So we must ensure that in the reverse proxy case we use the same code
     * path and using the canonical name seems to be the right thing to do
     * in the reverse proxy case.
     */
    if (!r->proxyreq || (r->proxyreq == PROXYREQ_REVERSE)) {
        /* Use _default_ as the hostname if none present, as in mod_vhost */
        hostname =  ap_get_server_name(r);
        if (!hostname) {
            hostname = "_default_";
        }
    }
    else if(r->parsed_uri.hostname) {
        /* Copy the parsed uri hostname */
        hn = apr_pcalloc(p, strlen(r->parsed_uri.hostname) + 1);
        for (i = 0; r->parsed_uri.hostname[i]; i++) {
            hn[i] = apr_tolower(r->parsed_uri.hostname[i]);
        }
        /* const work-around */
        hostname = hn;
    }
    else {
        /* We are a proxied request, with no hostname. Unlikely
         * to get very far - but just in case */
        hostname = "_default_";
    }

    /* Copy the scheme, ensuring that it is lower case. If the parsed uri
     * contains no string or if this is not a proxy request.
     */
    if (r->proxyreq && r->parsed_uri.scheme) {
        /* Copy the scheme */
        scheme = apr_pcalloc(p, strlen(r->parsed_uri.scheme) + 1);
        for (i = 0; r->parsed_uri.scheme[i]; i++) {
            scheme[i] = apr_tolower(r->parsed_uri.scheme[i]);
        }
    }
    else {
        scheme = "http";
    }

    /* If the content is locally generated, use the port-number of the
     * current server. Otherwise. copy the URI's port-string (which may be a
     * service name). If the URI contains no port-string, use apr-util's
     * notion of the default port for that scheme - if available.
     */
    if(r->proxyreq) {
        if (r->parsed_uri.port_str) {
            port_str = apr_pcalloc(p, strlen(r->parsed_uri.port_str) + 2);
            port_str[0] = ':';
            for (i = 0; r->parsed_uri.port_str[i]; i++) {
                port_str[i + 1] = apr_tolower(r->parsed_uri.port_str[i]);
            }
        }
        else if (apr_uri_port_of_scheme(scheme)) {
            port_str = apr_psprintf(p, ":%u", apr_uri_port_of_scheme(scheme));
        }
        else {
            /* No port string given in the AbsoluteUri, and we have no
             * idea what the default port for the scheme is. Leave it
             * blank and live with the inefficiency of some extra cached
             * entities.
             */
            port_str = "";
        }
    }
    else {
        /* Use the server port */
        port_str = apr_psprintf(p, ":%u", ap_get_server_port(r));
    }

    /* Key format is a URI */
    *key = apr_pstrcat(p, scheme, "://", hostname, port_str,
                       r->parsed_uri.path, "?", r->args, NULL);

    return APR_SUCCESS;
}