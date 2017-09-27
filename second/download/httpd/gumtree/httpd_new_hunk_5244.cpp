        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00782)
                "Cache lock obtained for stale cached URL, "
                "revalidating entry: %s",
                r->unparsed_uri);
        return 0;
    }
    else if (APR_STATUS_IS_EEXIST(status)) {
        /* lock already exists, return stale data anyway, with a warning */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00783)
                "Cache already locked for stale cached URL, "
                "pretend it is fresh: %s",
                r->unparsed_uri);

        /* make sure we don't stomp on a previous warning */
        warn_head = apr_table_get(h->resp_hdrs, "Warning");
