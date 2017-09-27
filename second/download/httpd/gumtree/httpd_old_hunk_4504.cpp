
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
            if (querystring && *querystring) {
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
                    param = ap_strstr_c(querystring, complete);
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
        *key = apr_pstrcat(p, scheme, "://", hostname, port_str, path, "?",
                NULL);
    }
    else {
        *key = apr_pstrcat(p, scheme, "://", hostname, port_str, path, "?",
                querystring, NULL);
    }

    /*
     * Store the key in the request_config for the cache as r->parsed_uri
     * might have changed in the time from our first visit here triggered by the
     * quick handler and our possible second visit triggered by the CACHE_SAVE
     * filter (e.g. r->parsed_uri got unescaped). In this case we would save the
     * resource in the cache under a key where it is never found by the quick
     * handler during following requests.
     */
    ap_log_rerror(
            APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00698) "cache: Key for entity %s?%s is %s", uri, parsed_uri->query, *key);

    return APR_SUCCESS;
}

apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
        const char **key)
{
    /* We want the actual query-string, which may differ from
     * r->parsed_uri.query (immutable), so use "" (not NULL).
     */
    const char *args = r->args ? r->args : "";
    return cache_canonicalise_key(r, p, r->uri, args, &r->parsed_uri, key);
}

/*
 * Invalidate a specific URL entity in all caches
 *
 * All cached entities for this URL are removed, usually in
