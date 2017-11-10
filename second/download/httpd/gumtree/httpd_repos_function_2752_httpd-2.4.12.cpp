static int uldap_cache_getuserdn(request_rec *r, util_ldap_connection_t *ldc,
                                 const char *url, const char *basedn,
                                 int scope, char **attrs, const char *filter,
                                 const char **binddn, const char ***retvals)
{
    const char **vals = NULL;
    int numvals = 0;
    int result = 0;
    LDAPMessage *res, *entry;
    char *dn;
    int count;
    int failures = 0;
    util_url_node_t *curl;              /* Cached URL node */
    util_url_node_t curnode;
    util_search_node_t *search_nodep;   /* Cached search node */
    util_search_node_t the_search_node;
    apr_time_t curtime;

    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(r->server->module_config,
        &ldap_module);

    /* Get the cache node for this url */
    LDAP_CACHE_LOCK();
    curnode.url = url;
    curl = (util_url_node_t *)util_ald_cache_fetch(st->util_ldap_cache,
                                                   &curnode);
    if (curl == NULL) {
        curl = util_ald_create_caches(st, url);
    }
    LDAP_CACHE_UNLOCK();

    if (curl) {
        LDAP_CACHE_LOCK();
        the_search_node.username = filter;
        search_nodep = util_ald_cache_fetch(curl->search_cache,
                                            &the_search_node);
        if (search_nodep != NULL) {

            /* found entry in search cache... */
            curtime = apr_time_now();

            /*
             * Remove this item from the cache if its expired.
             */
            if ((curtime - search_nodep->lastbind) > st->search_cache_ttl) {
                /* ...but entry is too old */
                util_ald_cache_remove(curl->search_cache, search_nodep);
            }
            else {
                /* ...and entry is valid */
                *binddn = apr_pstrdup(r->pool, search_nodep->dn);
                if (attrs) {
                    int i;
                    *retvals = apr_palloc(r->pool, sizeof(char *) * search_nodep->numvals);
                    for (i = 0; i < search_nodep->numvals; i++) {
                        (*retvals)[i] = apr_pstrdup(r->pool, search_nodep->vals[i]);
                    }
                }
                LDAP_CACHE_UNLOCK();
                ldc->reason = "Search successful (cached)";
                return LDAP_SUCCESS;
            }
        }
        /* unlock this read lock */
        LDAP_CACHE_UNLOCK();
    }

    /*
     * At this point, there is no valid cached search, so lets do the search.
     */

    /*
     * If LDAP operation fails due to LDAP_SERVER_DOWN, control returns here.
     */
start_over:
    if (failures > st->retries) {
        return result;
    }

    if (failures > 0 && st->retry_delay > 0) {
        apr_sleep(st->retry_delay);
    }

    if (LDAP_SUCCESS != (result = uldap_connection_open(r, ldc))) {
        return result;
    }

    /* try do the search */
    result = ldap_search_ext_s(ldc->ldap,
                               (char *)basedn, scope,
                               (char *)filter, attrs, 0,
                               NULL, NULL, st->opTimeout, APR_LDAP_SIZELIMIT, &res);
    if (AP_LDAP_IS_SERVER_DOWN(result))
    {
        ldc->reason = "ldap_search_ext_s() for user failed with server down";
        uldap_connection_unbind(ldc);
        failures++;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
        goto start_over;
    }

    /* if there is an error (including LDAP_NO_SUCH_OBJECT) return now */
    if (result != LDAP_SUCCESS) {
        ldc->reason = "ldap_search_ext_s() for user failed";
        return result;
    }

    /*
     * We should have found exactly one entry; to find a different
     * number is an error.
     */
    ldc->last_backend_conn = r->request_time;
    count = ldap_count_entries(ldc->ldap, res);
    if (count != 1)
    {
        if (count == 0 )
            ldc->reason = "User not found";
        else
            ldc->reason = "User is not unique (search found two "
                    