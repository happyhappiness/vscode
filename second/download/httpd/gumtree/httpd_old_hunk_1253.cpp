         */
        rv = cache->provider->store_body(cache->handle, r, in);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                         "cache: Cache provider's store_body failed!");
            ap_remove_output_filter(f);
        }
        return ap_pass_brigade(f->next, in);
    }

    /*
     * Setup Data in Cache
     * -------------------
