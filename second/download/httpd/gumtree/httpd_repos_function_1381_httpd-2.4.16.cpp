static apr_status_t cache_canonicalise_key(request_rec *r, apr_pool_t* p,
        const char *uri, apr_uri_t *parsed_uri, const char **key)
{
    cache_server_conf *conf;
    char *port_str, *hn, *lcs;
    const char *hostname, *scheme;
    int i;
    const char *path;
    char *querystring;

    if (*key) {
        /*
         * We have been here before during the processing of this request.
         */
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
        if (conf->base_uri && conf->base_uri->hostname) {
            hostname = conf->base_uri->hostname;
        }
        else {
            /* Use _default_ as the hostname if none present, as in mod_vhost */
            hostname = ap_get_server_name(r);
            if (!hostname) {
                hostname = "_default_";
            }
        }
    }
    else if (parsed_uri->hostname) {
        /* Copy the parsed uri hostname */
        hn = apr_pstrdup(p, parsed_uri->hostname);
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
    if (r->proxyreq && parsed_uri->scheme) {
        /* Copy the scheme and lower-case it */
        lcs = apr_pstrdup(p, parsed_uri->scheme);
        ap_str_tolower(lcs);
        /* const work-around */
        scheme = lcs;
    }
    else {
        if (conf->base_uri && conf->base_uri->scheme) {
            scheme = conf->base_uri->scheme;
        }
        else {
            scheme = ap_http_scheme(r);
        }
    }

    /*
     * If this is a proxy request, but not a reverse proxy request (see comment
     * above why these cases must be handled in the same manner), copy the
     * URI's port-string (which may be a service name). If the URI contains
     * no port-string, use apr-util's notion of the default port for that
     * scheme - if available. Otherwise use the port-number of the current
     * server.
     */
    if (r->proxyreq && (r->proxyreq != PROXYREQ_REVERSE)) {
        if (parsed_uri->port_str) {
            port_str = apr_pcalloc(p, strlen(parsed_uri->port_str) + 2);
            port_str[0] = ':';
            for (i = 0; parsed_uri->port_str[i]; i++) {
                port_str[i + 1] = apr_tolower(parsed_uri->port_str[i]);
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
        if (conf->base_uri && conf->base_uri->port_str) {
            port_str = conf->base_uri->port_str;
        }
        else if (conf->base_uri && conf->base_uri->hostname) {
            port_str = "";
        }
        else {
            /* Use the server port */
            port_str = apr_psprintf(p, ":%u", ap_get_server_port(r));
        }
    }

    /*
     * Check if we need to ignore session identifiers in the URL and do so
     * if needed.
     */
    path = uri;
    querystring = parsed_uri->query;
    if (conf->ignore_session_id->nelts) {
        int i;
        char **identifier;

        identifier = (char **) conf->ignore_session_id->elts;
        for (i = 0; i < conf->ignore_session_id->nelts; i++, identifier++) {
            int len;
            const char *param;

            len = strlen(*identifier);
            /*
             * Check that we have a parameter separator in the last segment
             * of the path and that the parameter matches our identifier
             */
            if ((param = ap_strrchr_c(path, ';'))
                    && !strncmp(param + 1, *identifier, len)
                    && (*(param + len + 1) == '=')
                    && !ap_strchr_c(param + len + 2, '/')) {
                path = apr_pstrmemdup(p, path, param - path);
                continue;
            }
            /*
             * Check if the identifier is in the querystring and cut it out.
             */
            if (querystring) {
                /*
                 * First check if the identifier is at the beginning of the
                 * querystring and followed by a '='
                 */
                if (!strncmp(querystring, *identifier, len)
                        && (*(querystring + len) == '=')) {
                    param = querystring;
                }
                else {
                    char *complete;

                    /*
                     * In order to avoid subkey matching (PR 48401) prepend
                     * identifier with a '&' and append a '='
                     */
                    complete = apr_pstrcat(p, "&", *identifier, "=", NULL);
                    param = strstr(querystring, complete);
                    /* If we found something we are sitting on the '&' */
                    if (param) {
                        param++;
                    }
                }
                if (param) {
                    const char *amp;

                    if (querystring != param) {
                        querystring = apr_pstrndup(p, querystring,
                                param - querystring);
                    }
                    else {
                        querystring = "";
                    }

                    if ((amp = ap_strchr_c(param + len + 1, '&'))) {
                        querystring = apr_pstrcat(p, querystring, amp + 1,
                                NULL);
                    }
                    else {
                        /*
                         * If querystring is not "", then we have the case
                         * that the identifier parameter we removed was the
                         * last one in the original querystring. Hence we have
                         * a trailing '&' which needs to be removed.
                         */
                        if (*querystring) {
                            querystring[strlen(querystring) - 1] = '\0';
                        }
                    }
                }
            }
        }
    }

    /* Key format is a URI, optionally without the query-string */
    if (conf->ignorequerystring) {
        *key 