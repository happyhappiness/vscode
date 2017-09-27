        ap_remove_output_filter(f);
        cache_remove_lock(conf, cache, r, NULL);
        return ap_pass_brigade(f->next, in);
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00769)
            "cache: Caching url: %s", r->unparsed_uri);

    /* We are actually caching this response. So it does not
     * make sense to remove this entity any more.
     */
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00770)
            "cache: Removing CACHE_REMOVE_URL filter.");
