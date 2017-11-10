int util_ldap_cache_checkuserid(request_rec *r, util_ldap_connection_t *ldc,
                              const char *url, const char *basedn, int scope, char **attrs,
                              const char *filter, const char *bindpw, const char **binddn,
                              const char ***retvals)
{
    const char **vals = NULL;
    int result = 0;
    LDAPMessage *res, *entry;
    char *dn;
    int count;
    int failures = 0;
    util_url_node_t *curl;		/* Cached URL node */
    util_url_node_t curnode;
    util_search_node_t *search_nodep;	/* Cached search node */
    util_search_node_t the_search_node;
    apr_time_t curtime;

    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(r->server->module_config,
        &ldap_module);

    /* read lock this function */
    LDAP_CACHE_LOCK_CREATE(st->pool);

    /* Get the cache node for this url */
    LDAP_CACHE_WRLOCK();
    curnode.url = url;
    curl = (util_url_node_t *)util_ald_cache_fetch(util_ldap_cache, &curnode);
    if (curl == NULL) {
        curl = util_ald_create_caches(st, url);
    }
    LDAP_CACHE_UNLOCK();

    LDAP_CACHE_RDLOCK();
    the_search_node.username = filter;
    search_nodep = util_ald_cache_fetch(curl->search_cache, &the_search_node);
    if (search_nodep != NULL && search_nodep->bindpw) {

        /* found entry in search cache... */
        curtime = apr_time_now();

        /*
         * Remove this item from the cache if its expired, or if the 
         * sent password doesn't match the storepassword.
         */
        if ((curtime - search_nodep->lastbind) > st->search_cache_ttl) {
            /* ...but entry is too old */
            util_ald_cache_remove(curl->search_cache, search_nodep);
        }
        else if (strcmp(search_nodep->bindpw, bindpw) != 0) {
	    /* ...but cached password doesn't match sent password */
            util_ald_cache_remove(curl->search_cache, search_nodep);
        }
        else {
            /* ...and entry is valid */
            *binddn = search_nodep->dn;
            *retvals = search_nodep->vals;
            LDAP_CACHE_UNLOCK();
            ldc->reason = "Authentication successful (cached)";
            return LDAP_SUCCESS;
        }
    }
    /* unlock this read lock */
    LDAP_CACHE_UNLOCK();

    /*	
     * At this point, there is no valid cached search, so lets do the search.
     */

    /*
     * If any LDAP operation fails due to LDAP_SERVER_DOWN, control returns here.
     */
start_over:
    if (failures++ > 10) {
        return result;
    }
    if (LDAP_SUCCESS != (result = util_ldap_connection_open(ldc))) {
        return result;
    }

    /* try do the search */
    if ((result = ldap_search_ext_s(ldc->ldap,
				    basedn, scope, 
				    filter, attrs, 0, 
				    NULL, NULL, NULL, -1, &res)) == LDAP_SERVER_DOWN) {
        ldc->reason = "ldap_search_ext_s() for user failed with server down";
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
    count = ldap_count_entries(ldc->ldap, res);
    if (count != 1) {
        ldap_msgfree(res);
        ldc->reason = "User is not unique (search found two or more matches)";
        return LDAP_NO_SUCH_OBJECT;
    }

    entry = ldap_first_entry(ldc->ldap, res);

    /* Grab the dn, copy it into the pool, and free it again */
    dn = ldap_get_dn(ldc->ldap, entry);
    *binddn = apr_pstrdup(st->pool, dn);
    ldap_memfree(dn);

    /* 
     * A bind to the server with an empty password always succeeds, so
     * we check to ensure that the password is not empty. This implies
     * that users who actually do have empty passwords will never be
     * able to authenticate with this module. I don't see this as a big
     * problem.
     */
    if (strlen(bindpw) <= 0) {
        ldap_msgfree(res);
        ldc->reason = "Empty password not allowed";
        return LDAP_INVALID_CREDENTIALS;
    }

    /* 
     * Attempt to bind with the retrieved dn and the password. If the bind
     * fails, it means that the password is wrong (the dn obviously
     * exists, since we just retrieved it)
     */
    if ((result = 
         ldap_simple_bind_s(ldc->ldap, *binddn, bindpw)) == 
         LDAP_SERVER_DOWN) {
        ldc->reason = "ldap_simple_bind_s() to check user credentials failed with server down";
        goto start_over;
    }

    /* failure? if so - return */
    if (result != LDAP_SUCCESS) {
        ldc->reason = "ldap_simple_bind_s() to check user credentials failed";
        return result;
    }

    /*
     * Get values for the provided attributes.
     */
    if (attrs) {
        int k = 0;
        int i = 0;
        while (attrs[k++]);
        vals = apr_pcalloc(r->pool, sizeof(char *) * (k+1));
        while (attrs[i]) {
            char **values;
            int j = 0;
            char *str = NULL;
            /* get values */
            values = ldap_get_values(ldc->ldap, entry, attrs[i]);
            while (values && values[j]) {
                str = str ? apr_pstrcat(r->pool, str, "; ", values[j], NULL) : apr_pstrdup(r->pool, values[j]);
                j++;
            }
            vals[i] = str;
            i++;
        }
        *retvals = vals;
    }

    /* 		
     * Add the new username to the search cache.
     */
    LDAP_CACHE_WRLOCK();
    the_search_node.username = filter;
    the_search_node.dn = *binddn;
    the_search_node.bindpw = bindpw;
    the_search_node.lastbind = apr_time_now();
    the_search_node.vals = vals;
    util_ald_cache_insert(curl->search_cache, &the_search_node);
    ldap_msgfree(res);
    LDAP_CACHE_UNLOCK();

    ldc->reason = "Authentication successful";
    return LDAP_SUCCESS;
}