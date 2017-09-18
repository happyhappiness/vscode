           ap_cache_liststr(cc_out, "public", NULL))
        ) ||

    /* or we've been asked not to cache it above */
        r->no_cache) {

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "cache: response is not cachable");

        /* remove this object from the cache 
         * BillS Asks.. Why do we need to make this call to remove_url?
         * leave it in for now..
         */
