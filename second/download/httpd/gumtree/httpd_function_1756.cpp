apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
                                        char**key)
{
    cache_server_conf *conf;
    cache_request_rec *cache;
    char *port_str, *hn, *lcs;
    const char *hostname, *scheme;
    int i;
    char *path, *querystring;

    cache = (cache_request_rec *) ap_get_module_config(r->request_config,
                                                       &cache_module);
    if (!cache) {
        /* This should never happen */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "cache: No cache request information available for key"
                     " generation");
        *key = "";
        return APR_EGENERAL;
    }
    if (cache->key) {
        /*
         * We have been here before during the processing of this request.
         * So return the key we already have.
         */
        *key = apr_pstrdup(p, cache->key);
        return APR_SUCCESS;
    }

    /*
     * Get the module configuration. We need this for the CacheIgnoreQueryString
     * option below.
     */
    conf = (cache_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &cache_module);

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
        hn = apr_pstrdup(p, r->parsed_uri.hostname);
        ap_str_tolower(hn);
        /* const work-around */
        hostname = hn;
    }
    else {
        /* We are a proxied request, with no hostname. Unlikely
         * to get very far - but just in case */
        hostname = "_default_";
    }

    /*
     * Copy the scheme, ensuring that it is lower case. If the parsed uri
     * contains no string or if this is not a proxy request get the http
     * scheme for this request. As r->parsed_uri.scheme is not set if this
     * is a reverse proxy request, it is ensured that the cases
     * "no proxy request" and "reverse proxy request" are handled in the same
     * manner (see above why this is needed).
     */
    if (r->proxyreq && r->parsed_uri.scheme) {
        /* Copy the scheme and lower-case it */
        lcs = apr_pstrdup(p, r->parsed_uri.scheme);
        ap_str_tolower(lcs);
        /* const work-around */
        scheme = lcs;
    }
    else {
        scheme = ap_http_scheme(r);
    }

    /*
     * If this is a proxy request, but not a reverse proxy request (see comment
     * above why these cases must be handled in the same manner), copy the
     * URI's port-string (which may be a service name). If the URI contains
     * no port-string, use apr-util's notion of the default port for that
     * scheme - if available. Otherwise use the port-number of the current
     * server.
     */
    if(r->proxyreq && (r->proxyreq != PROXYREQ_REVERSE)) {
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

    /*
     * Check if we need to ignore session identifiers in the URL and do so
     * if needed.
     */
    path = r->uri;
    querystring = r->parsed_uri.query;
    if (conf->ignore_session_id->nelts) {
        int i;
        char **identifier;

        identifier = (char **)conf->ignore_session_id->elts;
        for (i = 0; i < conf->ignore_session_id->nelts; i++, identifier++) {
            int len;
            char *param;

            len = strlen(*identifier);
            /*
             * Check that we have a parameter separator in the last segment
             * of the path and that the parameter matches our identifier
             */
            if ((param = strrchr(path, ';'))
                && !strncmp(param + 1, *identifier, len)
                && (*(param + len + 1) == '=')
                && !strchr(param + len + 2, '/')) {
                path = apr_pstrndup(p, path, param - path);
                break;
            }
            /*
             * Check if the identifier is in the querystring and cut it out.
             */
            if (querystring
                && (param = strstr(querystring, *identifier))
                && (*(param + len) == '=')
                ) {
                char *amp;

                if (querystring != param) {
                    querystring = apr_pstrndup(p, querystring,
                                               param - querystring);
                }
                else {
                    querystring = "";
                }
                if ((amp = strchr(param + len + 1, '&'))) {
                    querystring = apr_pstrcat(p, querystring, amp + 1, NULL);
                }
                break;
            }
        }
    }

    /* Key format is a URI, optionally without the query-string */
    if (conf->ignorequerystring) {
        *key = apr_pstrcat(p, scheme, "://", hostname, port_str,
                           path, "?", NULL);
    }
    else {
        *key = apr_pstrcat(p, scheme, "://", hostname, port_str,
                           path, "?", querystring, NULL);
    }

    /*
     * Store the key in the request_config for the cache as r->parsed_uri
     * might have changed in the time from our first visit here triggered by the
     * quick handler and our possible second visit triggered by the CACHE_SAVE
     * filter (e.g. r->parsed_uri got unescaped). In this case we would save the
     * resource in the cache under a key where it is never found by the quick
     * handler during following requests.
     */
    cache->key = apr_pstrdup(r->pool, *key);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                 "cache: Key for entity %s?%s is %s", r->uri,
                 r->parsed_uri.query, *key);

    return APR_SUCCESS;
}