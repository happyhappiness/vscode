    }
    else {
        /* Use the server port */
        port_str = apr_psprintf(p, ":%u", ap_get_server_port(r));
    }

    /*
     * Check if we need to ignore session identifiers in the URL and do so
     * if needed.
     */
    path = r->parsed_uri.path;
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
                 "cache: Key for entity %s?%s is %s", r->parsed_uri.path,
                 r->parsed_uri.query, *key);

    return APR_SUCCESS;
}
