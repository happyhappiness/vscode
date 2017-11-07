int cache_check_freshness(cache_handle_t *h, cache_request_rec *cache,
        request_rec *r)
{
    apr_status_t status;
    apr_int64_t age, maxage_req, maxage_cresp, maxage, smaxage, maxstale;
    apr_int64_t minfresh;
    const char *cc_req;
    const char *pragma;
    const char *agestr = NULL;
    apr_time_t age_c = 0;
    cache_info *info = &(h->cache_obj->info);
    const char *warn_head;
    cache_server_conf *conf =
      (cache_server_conf *)ap_get_module_config(r->server->module_config,
                                                &cache_module);

    /*
     * We now want to check if our cached data is still fresh. This depends
     * on a few things, in this order:
     *
     * - RFC2616 14.9.4 End to end reload, Cache-Control: no-cache. no-cache
     * in either the request or the cached response means that we must
     * perform the request unconditionally, and ignore cached content. We
     * should never reach here, but if we do, mark the content as stale,
     * as this is the best we can do.
     *
     * - RFC2616 14.32 Pragma: no-cache This is treated the same as
     * Cache-Control: no-cache.
     *
     * - RFC2616 14.9.3 Cache-Control: max-stale, must-revalidate,
     * proxy-revalidate if the max-stale request header exists, modify the
     * stale calculations below so that an object can be at most <max-stale>
     * seconds stale before we request a revalidation, _UNLESS_ a
     * must-revalidate or proxy-revalidate cached response header exists to
     * stop us doing this.
     *
     * - RFC2616 14.9.3 Cache-Control: s-maxage the origin server specifies the
     * maximum age an object can be before it is considered stale. This
     * directive has the effect of proxy|must revalidate, which in turn means
     * simple ignore any max-stale setting.
     *
     * - RFC2616 14.9.4 Cache-Control: max-age this header can appear in both
     * requests and responses. If both are specified, the smaller of the two
     * takes priority.
     *
     * - RFC2616 14.21 Expires: if this request header exists in the cached
     * entity, and it's value is in the past, it has expired.
     *
     */

    /* This value comes from the client's initial request. */
    cc_req = apr_table_get(r->headers_in, "Cache-Control");
    pragma = apr_table_get(r->headers_in, "Pragma");

    ap_cache_control(r, &cache->control_in, cc_req, pragma, r->headers_in);

    if (cache->control_in.no_cache) {

        if (!conf->ignorecachecontrol) {
            /* Treat as stale, causing revalidation */
            return 0;
        }

        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00781)
                "Incoming request is asking for a uncached version of "
                "%s, but we have been configured to ignore it and "
                "serve a cached response anyway",
                r->unparsed_uri);
    }

    /* These come from the cached entity. */
    if (h->cache_obj->info.control.no_cache
            || h->cache_obj->info.control.invalidated) {
        /*
         * The cached entity contained Cache-Control: no-cache, or a
         * no-cache with a header present, or a private with a header
         * present, or the cached entity has been invalidated in the
         * past, so treat as stale causing revalidation.
         */
        return 0;
    }

    if ((agestr = apr_table_get(h->resp_hdrs, "Age"))) {
        age_c = apr_atoi64(agestr);
    }

    /* calculate age of object */
    age = ap_cache_current_age(info, age_c, r->request_time);

    /* extract s-maxage */
    smaxage = h->cache_obj->info.control.s_maxage_value;

    /* extract max-age from request */
    maxage_req = -1;
    if (!conf->ignorecachecontrol) {
        maxage_req = cache->control_in.max_age_value;
    }

    /*
     * extract max-age from response, if both s-maxage and max-age, s-maxage
     * takes priority
     */
    if (smaxage != -1) {
        maxage_cresp = smaxage;
    }
    else {
        maxage_cresp = h->cache_obj->info.control.max_age_value;
    }

    /*
     * if both maxage request and response, the smaller one takes priority
     */
    if (maxage_req == -1) {
        maxage = maxage_cresp;
    }
    else if (maxage_cresp == -1) {
        maxage = maxage_req;
    }
    else {
        maxage = MIN(maxage_req, maxage_cresp);
    }

    /* extract max-stale */
    if (cache->control_in.max_stale) {
        if(cache->control_in.max_stale_value != -1) {
            maxstale = cache->control_in.max_stale_value;
        }
        else {
            /*
             * If no value is assigned to max-stale, then the client is willing
             * to accept a stale response of any age (RFC2616 14.9.3). We will
             * set it to one year in this case as this situation is somewhat
             * similar to a "never expires" Expires header (RFC2616 14.21)
             * which is set to a date one year from the time the response is
             * sent in this case.
             */
            maxstale = APR_INT64_C(86400*365);
        }
    }
    else {
        maxstale = 0;
    }

    /* extract min-fresh */
    if (!conf->ignorecachecontrol && cache->control_in.min_fresh) {
        minfresh = cache->control_in.min_fresh_value;
    }
    else {
        minfresh = 0;
    }

    /* override maxstale if must-revalidate, proxy-revalidate or s-maxage */
    if (maxstale && (h->cache_obj->info.control.must_revalidate
            || h->cache_obj->info.control.proxy_revalidate || smaxage != -1)) {
        maxstale = 0;
    }

    /* handle expiration */
    if (((maxage != -1) && (age < (maxage + maxstale - minfresh))) ||
        ((smaxage == -1) && (maxage == -1) &&
         (info->expire != APR_DATE_BAD) &&
         (age < (apr_time_sec(info->expire - info->date) + maxstale - minfresh)))) {

        warn_head = apr_table_get(h->resp_hdrs, "Warning");

        /* it's fresh darlings... */
        /* set age header on response */
        apr_table_set(h->resp_hdrs, "Age",
                      apr_psprintf(r->pool, "%lu", (unsigned long)age));

        /* add warning if maxstale overrode freshness calculation */
        if (!(((maxage != -1) && age < maxage) ||
              (info->expire != APR_DATE_BAD &&
               (apr_time_sec(info->expire - info->date)) > age))) {
            /* make sure we don't stomp on a previous warning */
            if ((warn_head == NULL) ||
                ((warn_head != NULL) && (ap_strstr_c(warn_head, "110") == NULL))) {
                apr_table_mergen(h->resp_hdrs, "Warning",
                                 "110 Response is stale");
            }
        }

        /*
         * If none of Expires, Cache-Control: max-age, or Cache-Control:
         * s-maxage appears in the response, and the response header age
         * calculated is more than 24 hours add the warning 113
         */
        if ((maxage_cresp == -1) && (smaxage == -1) && (apr_table_get(
                h->resp_hdrs, "Expires") == NULL) && (age > 86400)) {

            /* Make sure we don't stomp on a previous warning, and don't dup
             * a 113 marning that is already present. Also, make sure to add
             * the new warning to the correct *headers_out location.
             */
            if ((warn_head == NULL) ||
                ((warn_head != NULL) && (ap_strstr_c(warn_head, "113") == NULL))) {
                apr_table_mergen(h->resp_hdrs, "Warning",
                                 "113 Heuristic expiration");
            }
        }
        return 1;    /* Cache object is fresh (enough) */
    }

    /*
     * At this point we are stale, but: if we are under load, we may let
     * a significant number of stale requests through before the first
     * stale request successfully revalidates itself, causing a sudden
     * unexpected thundering herd which in turn brings angst and drama.
     *
     * So.
     *
     * We want the first stale request to go through as normal. But the
     * second and subsequent request, we must pretend to be fresh until
     * the first request comes back with either new content or confirmation
     * that the stale content is still fresh.
     *
     * To achieve this, we create a very simple file based lock based on
     * the key of the cached object. We attempt to open the lock file with
     * exclusive write access. If we succeed, woohoo! we're first, and we
     * follow the stale path to the backend server. If we fail, oh well,
     * we follow the fresh path, and avoid being a thundering herd.
     *
     * The lock lives only as long as the stale request that went on ahead.
     * If the request succeeds, the lock is deleted. If the request fails,
     * the lock is deleted, and another request gets to make a new lock
     * and try again.
     *
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