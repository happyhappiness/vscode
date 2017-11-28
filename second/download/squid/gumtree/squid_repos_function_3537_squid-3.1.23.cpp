static int
refreshCheck(const StoreEntry * entry, HttpRequest * request, time_t delta)
{
    const refresh_t *R;
    const char *uri = NULL;
    time_t age = 0;
    time_t check_time = squid_curtime + delta;
    int staleness;
    stale_flags sf;

    if (entry->mem_obj)
        uri = entry->mem_obj->url;
    else if (request)
        uri = urlCanonical(request);

    debugs(22, 3, "refreshCheck: '" << (uri ? uri : "<none>") << "'");

    if (check_time > entry->timestamp)
        age = check_time - entry->timestamp;

    // FIXME: what to do when age < 0 or counter overflow?
    assert(age >= 0);

    R = uri ? refreshLimits(uri) : refreshUncompiledPattern(".");

    if (NULL == R)
        R = &DefaultRefresh;

    debugs(22, 3, "refreshCheck: Matched '" << R->pattern << " " <<
           (int) R->min << " " << (int) (100.0 * R->pct) << "%% " <<
           (int) R->max << "'");

    debugs(22, 3, "\tage:\t" << age);

    debugs(22, 3, "\tcheck_time:\t" << mkrfc1123(check_time));

    debugs(22, 3, "\tentry->timestamp:\t" << mkrfc1123(entry->timestamp));

    if (request && !request->flags.ignore_cc) {
        const HttpHdrCc *const cc = request->cache_control;
        if (cc && cc->min_fresh > 0) {
            debugs(22, 3, "\tage + min-fresh:\t" << age << " + " <<
                   cc->min_fresh << " = " << age + cc->min_fresh);
            debugs(22, 3, "\tcheck_time + min-fresh:\t" << check_time << " + "
                   << cc->min_fresh << " = " <<
                   mkrfc1123(check_time + cc->min_fresh));
            age += cc->min_fresh;
            check_time += cc->min_fresh;
        }
    }

    memset(&sf, '\0', sizeof(sf));

    staleness = refreshStaleness(entry, check_time, age, R, &sf);

    debugs(22, 3, "Staleness = " << staleness);

    // stale-if-error requires any failure be passed thru when its period is over.
    if (request && entry->mem_obj && entry->mem_obj->getReply() && entry->mem_obj->getReply()->cache_control &&
            EBIT_TEST(entry->mem_obj->getReply()->cache_control->mask, CC_STALE_IF_ERROR) &&
            entry->mem_obj->getReply()->cache_control->stale_if_error < staleness) {

        debugs(22, 3, "refreshCheck: stale-if-error period expired.");
        request->flags.fail_on_validation_err = 1;
    }

    if (EBIT_TEST(entry->flags, ENTRY_REVALIDATE) && staleness > -1
#if HTTP_VIOLATIONS
            && !R->flags.ignore_must_revalidate
#endif
       ) {
        debugs(22, 3, "refreshCheck: YES: Must revalidate stale response");
        if (request)
            request->flags.fail_on_validation_err = 1;
        return STALE_MUST_REVALIDATE;
    }

    /* request-specific checks */
    if (request && !request->flags.ignore_cc) {
        HttpHdrCc *cc = request->cache_control;

        if (request->flags.ims && (R->flags.refresh_ims || Config.onoff.refresh_all_ims)) {
            /* The clients no-cache header is changed into a IMS query */
            debugs(22, 3, "refreshCheck: YES: refresh-ims");
            return STALE_FORCED_RELOAD;
        }

#if HTTP_VIOLATIONS

        if (!request->flags.nocache_hack) {
            (void) 0;
        } else if (R->flags.ignore_reload) {
            /* The clients no-cache header is ignored */
            debugs(22, 3, "refreshCheck: MAYBE: ignore-reload");
        } else if (R->flags.reload_into_ims || Config.onoff.reload_into_ims) {
            /* The clients no-cache header is changed into a IMS query */
            debugs(22, 3, "refreshCheck: YES: reload-into-ims");
            return STALE_RELOAD_INTO_IMS;
        } else {
            /* The clients no-cache header is not overridden on this request */
            debugs(22, 3, "refreshCheck: YES: client reload");
            request->flags.nocache = 1;
            return STALE_FORCED_RELOAD;
        }

#endif
        if (NULL != cc) {
            if (cc->max_age > -1) {
#if HTTP_VIOLATIONS
                if (R->flags.ignore_reload && cc->max_age == 0) {
                    debugs(22, 3, "refreshCheck: MAYBE: client-max-age = 0 and ignore-reload");
                } else
#endif
                {
                    if (cc->max_age == 0) {
                        debugs(22, 3, "refreshCheck: YES: client-max-age = 0");
                        return STALE_EXCEEDS_REQUEST_MAX_AGE_VALUE;
                    }

                    if (age > cc->max_age) {
                        debugs(22, 3, "refreshCheck: YES: age > client-max-age");
                        return STALE_EXCEEDS_REQUEST_MAX_AGE_VALUE;
                    }
                }
            }

            if (EBIT_TEST(cc->mask, CC_MAX_STALE) && staleness > -1) {
                if (cc->max_stale < 0) {
                    /* max-stale directive without a value */
                    debugs(22, 3, "refreshCheck: NO: max-stale wildcard");
                    return FRESH_REQUEST_MAX_STALE_ALL;
                } else if (staleness < cc->max_stale) {
                    debugs(22, 3, "refreshCheck: NO: staleness < max-stale");
                    return FRESH_REQUEST_MAX_STALE_VALUE;
                }
            }
        }
    }

    if (-1 == staleness) {
        debugs(22, 3, "refreshCheck: object isn't stale..");
        if (sf.expires) {
            debugs(22, 3, "refreshCheck: returning FRESH_EXPIRES");
            return FRESH_EXPIRES;
        }

        assert(!sf.max);

        if (sf.lmfactor) {
            debugs(22, 3, "refreshCheck: returning FRESH_LMFACTOR_RULE");
            return FRESH_LMFACTOR_RULE;
        }

        assert(sf.min);

        debugs(22, 3, "refreshCheck: returning FRESH_MIN_RULE");
        return FRESH_MIN_RULE;
    }

    /*
     * At this point the response is stale, unless one of
     * the override options kicks in.
     */
    if (sf.expires) {
#if HTTP_VIOLATIONS

        if (R->flags.override_expire && age < R->min) {
            debugs(22, 3, "refreshCheck: NO: age < min && override-expire");
            return FRESH_OVERRIDE_EXPIRES;
        }

#endif
        return STALE_EXPIRES;
    }

    if (sf.max)
        return STALE_MAX_RULE;

    if (sf.lmfactor) {
#if HTTP_VIOLATIONS

        if (R->flags.override_lastmod && age < R->min) {
            debugs(22, 3, "refreshCheck: NO: age < min && override-lastmod");
            return FRESH_OVERRIDE_LASTMOD;
        }

#endif
        return STALE_LMFACTOR_RULE;
    }

    debugs(22, 3, "refreshCheck: returning STALE_DEFAULT");
    return STALE_DEFAULT;
}