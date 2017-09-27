    if (r->main) {
        cache_out_handle = cache_out_subreq_filter_handle;
    }
    else {
        cache_out_handle = cache_out_filter_handle;
    }
    ap_add_output_filter_handle(cache_out_handle, cache, r, r->connection);

    /*
     * Did the user indicate the precise location of the CACHE_OUT filter by
     * inserting the CACHE filter as a marker?
     *
     * If so, we get cunning and replace CACHE with the CACHE_OUT filters.
     * This has the effect of inserting the CACHE_OUT filter at the precise
     * location where the admin wants to cache the content. All filters that
     * lie *after* the original location of the CACHE filter will remain in
     * place.
     */
    if (cache_replace_filter(r->output_filters, cache_filter_handle,
            cache_out_handle, ap_get_input_filter_handle("SUBREQ_CORE"))) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS,
                r, APLOGNO(00761) "Replacing CACHE with CACHE_OUT filter for %s",
                r->uri);
    }

    /*
     * Remove all filters that are before the cache_out filter. This ensures
     * that we kick off the filter stack with our cache_out filter being the
