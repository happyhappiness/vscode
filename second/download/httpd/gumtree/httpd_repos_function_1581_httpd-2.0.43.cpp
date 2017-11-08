int util_ldap_cache_compare(request_rec *r, util_ldap_connection_t *ldc,
                          const char *url, const char *dn,
                          const char *attrib, const char *value)
{
    int result = 0;
    util_url_node_t *curl; 
    util_url_node_t curnode;
    util_compare_node_t *compare_nodep;
    util_compare_node_t the_compare_node;
    apr_time_t curtime;
    int failures = 0;

    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(r->server->module_config,
        &ldap_module);

    /* read lock this function */
    LDAP_CACHE_LOCK_CREATE(st->pool);

    /* get cache entry (or create one) */
    LDAP_CACHE_WRLOCK();
    curnode.url = url;
    curl = util_ald_cache_fetch(util_ldap_cache, &curnode);
    if (curl == NULL) {
        curl = util_ald_create_caches(st, url);
    }
    LDAP_CACHE_UNLOCK();

    /* make a comparison to the cache */
    LDAP_CACHE_RDLOCK();
    curtime = apr_time_now();

    the_compare_node.dn = (char *)dn;
    the_compare_node.attrib = (char *)attrib;
    the_compare_node.value = (char *)value;
    the_compare_node.result = 0;

    compare_nodep = util_ald_cache_fetch(curl->compare_cache, &the_compare_node);

    if (compare_nodep != NULL) {
        /* found it... */
        if (curtime - compare_nodep->lastcompare > st->compare_cache_ttl) {
            /* ...but it is too old */
            util_ald_cache_remove(curl->compare_cache, compare_nodep);
        }
        else {
            /* ...and it is good */
            /* unlock this read lock */
            LDAP_CACHE_UNLOCK();
            if (LDAP_COMPARE_TRUE == compare_nodep->result) {
                ldc->reason = "Comparison true (cached)";
                return compare_nodep->result;
            }
            else if (LDAP_COMPARE_FALSE == compare_nodep->result) {
                ldc->reason = "Comparison false (cached)";
                return compare_nodep->result;
            }
            else if (LDAP_NO_SUCH_ATTRIBUTE == compare_nodep->result) {
                ldc->reason = "Comparison no such attribute (cached)";
                return compare_nodep->result;
            }
            else {
                ldc->reason = "Comparison undefined (cached)";
                return compare_nodep->result;
            }
        }
    }
    /* unlock this read lock */
    LDAP_CACHE_UNLOCK();

start_over:
    if (failures++ > 10) {
        /* too many failures */
        return result;
    }
    if (LDAP_SUCCESS != (result = util_ldap_connection_open(ldc))) {
        /* connect failed */
        return result;
    }

    if ((result = ldap_compare_s(ldc->ldap, const_cast(dn), 
			         const_cast(attrib), const_cast(value)))
        == LDAP_SERVER_DOWN) { 
        /* connection failed - try again */
        util_ldap_connection_close(ldc);
        ldc->reason = "ldap_compare_s() failed with server down";
        goto start_over;
    }

    ldc->reason = "Comparison complete";
    if ((LDAP_COMPARE_TRUE == result) || 
        (LDAP_COMPARE_FALSE == result) ||
        (LDAP_NO_SUCH_ATTRIBUTE == result)) {
        /* compare completed; caching result */
        LDAP_CACHE_WRLOCK();
        the_compare_node.lastcompare = curtime;
        the_compare_node.result = result;
        util_ald_cache_insert(curl->compare_cache, &the_compare_node);
        LDAP_CACHE_UNLOCK();
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