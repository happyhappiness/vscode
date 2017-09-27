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
