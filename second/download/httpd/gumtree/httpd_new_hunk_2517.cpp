     * At any time, a request marked "no-cache" will force a refresh,
     * ignoring the lock, ensuring an extended lockout is impossible.
     *
     * A lock that exceeds a maximum age will be deleted, and another
     * request gets to make a new lock and try again.
     */
    status = cache_try_lock(conf, cache, r);
    if (APR_SUCCESS == status) {
        /* we obtained a lock, follow the stale path */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00782)
                "Cache lock obtained for stale cached URL, "
                "revalidating entry: %s",
                r->unparsed_uri);
        return 0;
    }
    else if (APR_EEXIST == status) {
        /* lock already exists, return stale data anyway, with a warning */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00783)
                "Cache already locked for stale cached URL, "
                "pretend it is fresh: %s",
                r->unparsed_uri);

        /* make sure we don't stomp on a previous warning */
        warn_head = apr_table_get(h->resp_hdrs, "Warning");
        if ((warn_head == NULL) ||
            ((warn_head != NULL) && (ap_strstr_c(warn_head, "110") == NULL))) {
            apr_table_mergen(h->resp_hdrs, "Warning",
                             "110 Response is stale");
        }

        return 1;
    }
    else {
        /* some other error occurred, just treat the object as stale */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00784)
                "Attempt to obtain a cache lock for stale "
                "cached URL failed, revalidating entry anyway: %s",
                r->unparsed_uri);
        return 0;
    }

}

/* return each comma separated token, one at a time */
CACHE_DECLARE(const char *)ap_cache_tokstr(apr_pool_t *p, const char *list,
                                           const char **str)
{
    apr_size_t i;
    const char *s;
