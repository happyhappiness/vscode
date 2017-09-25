    if (conf->ignorecachecontrol == 1 && auth == NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "incoming request is asking for a uncached version of "
                     "%s, but we know better and are ignoring it", url);
    }
    else {
        if (ap_cache_liststr(NULL, cc_in, "no-store", NULL) ||
            ap_cache_liststr(NULL, pragma, "no-cache", NULL) || (auth != NULL)) {
            /* delete the previously cached file */
            cache_remove_url(r, cache->types, url);

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: no-store forbids caching of %s", url);
            return DECLINED;
