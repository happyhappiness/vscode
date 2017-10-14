static int uldap_cache_compare(request_rec *r, util_ldap_connection_t *ldc,
                               const char *url, const char *dn,
                               const char *attrib, const char *value)
{
    int result = 0;
    util_url_node_t *curl;
    util_url_node_t curnode;
    util_compare_node_t *compare_nodep;
    util_compare_node_t the_compare_node;
    apr_time_t curtime = 0; /* silence gcc -Wall */
    int failures = 0;

    util_ldap_state_t *st = (util_ldap_state_t *)
                            ap_get_module_config(r->server->module_config,
                                                 &ldap_module);

    /* get cache entry (or create one) */
    LDAP_CACHE_LOCK();
    curnode.url = url;
    curl = util_ald_cache_fetch(st->util_ldap_cache, &curnode);
    if (curl == NULL) {
        curl = util_ald_create_caches(st, url);
    }
    LDAP_CACHE_UNLOCK();

    if (curl) {
        /* make a comparison to the cache */
        LDAP_CACHE_LOCK();
        curtime = apr_time_now();

        the_compare_node.dn = (char *)dn;
        the_compare_node.attrib = (char *)attrib;
        the_compare_node.value = (char *)value;
        the_compare_node.result = 0;
        the_compare_node.sgl_processed = 0;
        the_compare_node.subgroupList = NULL;

        compare_nodep = util_ald_cache_fetch(curl->compare_cache,
                                             &the_compare_node);

        if (compare_nodep != NULL) {
            /* found it... */
            if (curtime - compare_nodep->lastcompare > st->compare_cache_ttl) {
                /* ...but it is too old */
                util_ald_cache_remove(curl->compare_cache, compare_nodep);
            }
            else {
                /* ...and it is good */
                if (LDAP_COMPARE_TRUE == compare_nodep->result) {
                    ldc->reason = "Comparison true (cached)";
                }
                else if (LDAP_COMPARE_FALSE == compare_nodep->result) {
                    ldc->reason = "Comparison false (cached)";
                }
                else if (LDAP_NO_SUCH_ATTRIBUTE == compare_nodep->result) {
                    ldc->reason = "Comparison no such attribute (cached)";
                }
                else {
                    ldc->reason = "Comparison undefined (cached)";
                }

                /* record the result code to return with the reason... */
                result = compare_nodep->result;
                /* and unlock this read lock */
                LDAP_CACHE_UNLOCK();
                return result;
            }
        }
        /* unlock this read lock */
        LDAP_CACHE_UNLOCK();
    }

start_over:
    if (failures++ > 10) {
        /* too many failures */
        return result;
    }

    if (LDAP_SUCCESS != (result = uldap_connection_open(r, ldc))) {
        /* connect failed */
        return result;
    }

    result = ldap_compare_s(ldc->ldap,
                            (char *)dn,
                            (char *)attrib,
                            (char *)value);
    if (AP_LDAP_IS_SERVER_DOWN(result)) { 
        /* connection failed - try again */
        ldc->reason = "ldap_compare_s() failed with server down";
        uldap_connection_unbind(ldc);
        goto start_over;
    }
    if (result == LDAP_TIMEOUT && failures == 0) {
        /*
         * we are reusing a connection that doesn't seem to be active anymore
         * (firewall state drop?), let's try a new connection.
         */
        ldc->reason = "ldap_compare_s() failed with timeout";
        uldap_connection_unbind(ldc);
        goto start_over;
    }

    ldc->reason = "Comparison complete";
    if ((LDAP_COMPARE_TRUE == result) ||
        (LDAP_COMPARE_FALSE == result) ||
        (LDAP_NO_SUCH_ATTRIBUTE == result)) {
        if (curl) {
            /* compare completed; caching result */
            LDAP_CACHE_LOCK();
            the_compare_node.lastcompare = curtime;
            the_compare_node.result = result;
            the_compare_node.sgl_processed = 0;
            the_compare_node.subgroupList = NULL;

            /* If the node doesn't exist then insert it, otherwise just update
             * it with the last results
             */
            compare_nodep = util_ald_cache_fetch(curl->compare_cache,
                                                 &the_compare_node);
            if (   (compare_nodep == NULL)
                || (strcmp(the_compare_node.dn, compare_nodep->dn) != 0)
                || (strcmp(the_compare_node.attrib,compare_nodep->attrib) != 0)
                || (strcmp(the_compare_node.value, compare_nodep->value) != 0))
            {
                void *junk;

                junk = util_ald_cache_insert(curl->compare_cache,
                                             &the_compare_node);
                if(junk == NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] cache_compare: Cache"
                                  " insertion failure.", getpid());
                }
            }
            else {
                compare_nodep->lastcompare = curtime;
                compare_nodep->result = result;
            }
            LDAP_CACHE_UNLOCK();
        }
        if (LDAP_COMPARE_TRUE == result) {
            ldc->reason = "Comparison true (adding to cache)";
            return LDAP_COMPARE_TRUE;
        }
        else if (LDAP_COMPARE_FALSE == result) {
            ldc->reason = "Comparison false (adding to cache)";
            return LDAP_COMPARE_FALSE;
        }
        else {
            ldc->reason = "Comparison no such attribute (adding to cache)";
            return LDAP_NO_SUCH_ATTRIBUTE;
        }
    }
    return result;
}