        type_e = CACHE_TYPE_FILE;
    }
    else {
        return DECLINED;
    }

    /* In principle, we should be able to dispense with the cache_size checks
     * when caching open file descriptors.  However, code in cache_insert() and 
     * other places does not make the distinction whether a file's content or
     * descriptor is being cached. For now, just do all the same size checks
     * regardless of what we are caching.
     */
    if (len < sconf->min_cache_object_size || 
        len > sconf->max_cache_object_size) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache_mem: URL %s failed the size check, "
                     "or is incomplete", 
                     key);
        return DECLINED;
    }
    if (type_e == CACHE_TYPE_FILE) {
        /* CACHE_TYPE_FILE is only valid for local content handled by the 
         * default handler. Need a better way to check if the file is
         * local or not.
         */
        if (!r->filename) {
