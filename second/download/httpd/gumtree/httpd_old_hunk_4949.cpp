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
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00698)
            "cache: Key for entity %s?%s is %s", r->uri,
            r->parsed_uri.query, *key);

    return APR_SUCCESS;
}
