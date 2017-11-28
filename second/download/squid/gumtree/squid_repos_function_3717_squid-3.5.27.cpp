static int
refreshCheck(const StoreEntry * entry, HttpRequest * request, time_t delta)
{
    const char *uri = NULL;
    time_t age = 0;
    time_t check_time = squid_curtime + delta;
    int staleness;
    stale_flags sf;

    // get the URL of this entry, if there is one
    if (entry->mem_obj)
        uri = entry->mem_obj->storeId();
    else if (request)
        uri = urlCanonical(request);

    debugs(22, 3, "checking freshness of '" << (uri ? uri : "<none>") << "'");

    // age is not necessarily the age now, but the age at the given check_time
    if (check_time > entry->timestamp)
        age = check_time - entry->timestamp;

    // FIXME: what to do when age < 0 or counter overflow?
    assert(age >= 0);

    /* We need a refresh rule. In order of preference:
     *
     *   1. the rule that matches this URI by regex
     *   2. the "." rule from the config file
     *   3. the default "." rule
     */
    const RefreshPattern *R = uri ? refreshLimits(uri) : refreshUncompiledPattern(".");
    if (NULL == R)
        R = &DefaultRefresh;

    debugs(22, 3, "Matched '" << R->pattern << " " <<
           (int) R->min << " " << (int) (100.0 * R->pct) << "%% " <<
           (int) R->max << "'");

    debugs(22, 3, "\tage:\t" << age);

    debugs(22, 3, "\tcheck_time:\t" << mkrfc1123(check_time));

    debugs(22, 3, "\tentry->timestamp:\t" << mkrfc1123(entry->timestamp));

    if (request && !request->flags.ignoreCc) {
        const HttpHdrCc *const cc = request->cache_control;
        if (cc && cc->hasMinFresh()) {
            const int32_t minFresh=cc->minFresh();
            debugs(22, 3, "\tage + min-fresh:\t" << age << " + " <<
                   minFresh << " = " << age + minFresh);
            debugs(22, 3, "\tcheck_time + min-fresh:\t" << check_time << " + "
                   << minFresh << " = " <<
                   mkrfc1123(check_time + minFresh));
            age += minFresh;
            check_time += minFresh;
        }
    }

    memset(&sf, '\0', sizeof(sf));

    staleness = refreshStaleness(entry, check_time, age, R, &sf);

    debugs(22, 3, "Staleness = " << staleness);

    // stale-if-error requires any failure be passed thru when its period is over.
    if (request && entry->mem_obj && entry->mem_obj->getReply() && entry->mem_obj->getReply()->cache_control &&
            entry->mem_obj->getReply()->cache_control->hasStaleIfError() &&
            entry->mem_obj->getReply()->cache_control->staleIfError() < staleness) {

        debugs(22, 3, "stale-if-error period expired. Will produce error if validation fails.");
        request->flags.failOnValidationError = true;
    }

    /* If the origin server specified either of:
     *   Cache-Control: must-revalidate
     *   Cache-Control: proxy-revalidate
     * the spec says the response must always be revalidated if stale.
     */
    const bool revalidateAlways = EBIT_TEST(entry->flags, ENTRY_REVALIDATE_ALWAYS);
    bool revalidateStale = staleness > -1 && EBIT_TEST(entry->flags, ENTRY_REVALIDATE_STALE);
#if USE_HTTP_VIOLATIONS
    revalidateStale = revalidateStale && !R->flags.ignore_must_revalidate;
#endif
    if (revalidateAlways || revalidateStale) {
        debugs(22, 3, "YES: Must revalidate stale object (origin set " <<
               (revalidateAlways ? "no-cache or private" :
                "must-revalidate, proxy-revalidate or s-maxage") << ")");
        if (request)
            request->flags.failOnValidationError = true;
        return STALE_MUST_REVALIDATE;
    }

    /* request-specific checks */
    if (request && !request->flags.ignoreCc) {
        HttpHdrCc *cc = request->cache_control;

        /* If the request is an IMS request, and squid is configured NOT to service this from cache
         * (either by 'refresh-ims' in the refresh pattern or 'refresh_all_ims on' globally)
         * then force a reload from the origin.
         */
        if (request->flags.ims && (R->flags.refresh_ims || Config.onoff.refresh_all_ims)) {
            // The client's no-cache header is changed into a IMS query
            debugs(22, 3, "YES: Client IMS request forcing revalidation of object (refresh-ims option)");
            return STALE_FORCED_RELOAD;
        }

#if USE_HTTP_VIOLATIONS
        /* Normally a client reload request ("Cache-Control: no-cache" or "Pragma: no-cache")
         * means we must treat this reponse as STALE and fetch a new one.
         *
         * However, some options exist to override this behaviour. For example, we might just
         * revalidate our existing response, or even just serve it up without revalidating it.
         *
         *     ---- Note on the meaning of nocache_hack -----
         *
         * The nocache_hack flag has a very specific and complex meaning:
         *
         * (a) this is a reload request ("Cache-Control: no-cache" or "Pragma: no-cache" header)
         * and (b) the configuration file either has at least one refresh_pattern with
         * ignore-reload or reload-into-ims (not necessarily the rule matching this request) or
         * the global reload_into_ims is set to on
         *
         * In other words: this is a client reload, and we might need to override
         * the default behaviour (but we might not).
         *
         * "nocache_hack" is a pretty deceptive name for such a complicated meaning.
         */
        if (request->flags.noCacheHack()) {

            if (R->flags.ignore_reload) {
                /* The client's no-cache header is ignored completely - we'll try to serve
                 * what we have (assuming it's still fresh, etc.)
                 */
                debugs(22, 3, "MAYBE: Ignoring client reload request - trying to serve from cache (ignore-reload option)");
            } else if (R->flags.reload_into_ims || Config.onoff.reload_into_ims) {
                /* The client's no-cache header is not honoured completely - we'll just try
                 * to revalidate our cached copy (IMS to origin) instead of fetching a new
                 * copy with an unconditional GET.
                 */
                debugs(22, 3, "YES: Client reload request - cheating, only revalidating with origin (reload-into-ims option)");
                return STALE_RELOAD_INTO_IMS;
            } else {
                /* The client's no-cache header is honoured - we fetch a new copy from origin */
                debugs(22, 3, "YES: Client reload request - fetching new copy from origin");
                request->flags.noCache = true;
                return STALE_FORCED_RELOAD;
            }
        }
#endif

        // Check the Cache-Control client request header
        if (NULL != cc) {

            // max-age directive
            if (cc->hasMaxAge()) {
#if USE_HTTP_VIOLATIONS
                // Ignore client "Cache-Control: max-age=0" header
                if (R->flags.ignore_reload && cc->maxAge() == 0) {
                    debugs(22, 3, "MAYBE: Ignoring client reload request - trying to serve from cache (ignore-reload option)");
                } else
#endif
                {
                    // Honour client "Cache-Control: max-age=x" header
                    if (age > cc->maxAge() || cc->maxAge() == 0) {
                        debugs(22, 3, "YES: Revalidating object - client 'Cache-Control: max-age=" << cc->maxAge() << "'");
                        return STALE_EXCEEDS_REQUEST_MAX_AGE_VALUE;
                    }
                }
            }

            // max-stale directive
            if (cc->hasMaxStale() && staleness > -1) {
                if (cc->maxStale()==HttpHdrCc::MAX_STALE_ANY) {
                    debugs(22, 3, "NO: Client accepts a stale response of any age - 'Cache-Control: max-stale'");
                    return FRESH_REQUEST_MAX_STALE_ALL;
                } else if (staleness < cc->maxStale()) {
                    debugs(22, 3, "NO: Client accepts a stale response - 'Cache-Control: max-stale=" << cc->maxStale() << "'");
                    return FRESH_REQUEST_MAX_STALE_VALUE;
                }
            }
        }
    }

    // If the object is fresh, return the right FRESH_ code
    if (-1 == staleness) {
        debugs(22, 3, "Object isn't stale..");
        if (sf.expires) {
            debugs(22, 3, "returning FRESH_EXPIRES");
            return FRESH_EXPIRES;
        }

        assert(!sf.max);

        if (sf.lmfactor) {
            debugs(22, 3, "returning FRESH_LMFACTOR_RULE");
            return FRESH_LMFACTOR_RULE;
        }

        assert(sf.min);

        debugs(22, 3, "returning FRESH_MIN_RULE");
        return FRESH_MIN_RULE;
    }

    /*
     * At this point the response is stale, unless one of
     * the override options kicks in.
     * NOTE: max-stale config blocks the overrides.
     */
    int max_stale = (R->max_stale >= 0 ? R->max_stale : Config.maxStale);
    if ( max_stale >= 0 && staleness > max_stale) {
        debugs(22, 3, "YES: refresh_pattern max-stale=N limit from squid.conf");
        if (request)
            request->flags.failOnValidationError = true;
        return STALE_MAX_STALE;
    }

    if (sf.expires) {
#if USE_HTTP_VIOLATIONS

        if (R->flags.override_expire && age < R->min) {
            debugs(22, 3, "NO: Serving from cache - even though explicit expiry has passed, we enforce Min value (override-expire option)");
            return FRESH_OVERRIDE_EXPIRES;
        }

#endif
        return STALE_EXPIRES;
    }

    if (sf.max)
        return STALE_MAX_RULE;

    if (sf.lmfactor) {
#if USE_HTTP_VIOLATIONS
        if (R->flags.override_lastmod && age < R->min) {
            debugs(22, 3, "NO: Serving from cache - even though L-M factor says the object is stale, we enforce Min value (override-lastmod option)");
            return FRESH_OVERRIDE_LASTMOD;
        }
#endif
        debugs(22, 3, "YES: L-M factor says the object is stale'");
        return STALE_LMFACTOR_RULE;
    }

    debugs(22, 3, "returning STALE_DEFAULT");
    return STALE_DEFAULT;
}