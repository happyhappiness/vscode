static int uldap_cache_check_subgroups(request_rec *r,
                                       util_ldap_connection_t *ldc,
                                       const char *url, const char *dn,
                                       const char *attrib, const char *value,
                                       char **subgroupAttrs,
                                       apr_array_header_t *subgroupclasses,
                                       int cur_subgroup_depth,
                                       int max_subgroup_depth)
{
    int result = LDAP_COMPARE_FALSE;
    util_url_node_t *curl;
    util_url_node_t curnode;
    util_compare_node_t *compare_nodep;
    util_compare_node_t the_compare_node;
    util_compare_subgroup_t *tmp_local_sgl = NULL;
    int sgl_cached_empty = 0, sgindex = 0, base_sgcIndex = 0;
    struct mod_auth_ldap_groupattr_entry_t *sgc_ents =
            (struct mod_auth_ldap_groupattr_entry_t *) subgroupclasses->elts;
    util_ldap_state_t *st = (util_ldap_state_t *)
                            ap_get_module_config(r->server->module_config,
                                                 &ldap_module);

    /*
     * Stop looking at deeper levels of nested groups if we have reached the
     * max. Since we already checked the top-level group in uldap_cache_compare,
     * we don't need to check it again here - so if max_subgroup_depth is set
     * to 0, we won't check it (i.e. that is why we check < rather than <=).
     * We'll be calling uldap_cache_compare from here to check if the user is
     * in the next level before we recurse into that next level looking for
     * more subgroups.
     */
    if (cur_subgroup_depth >= max_subgroup_depth) {
        return LDAP_COMPARE_FALSE;
    }

    /*
     * 1. Check the "groupiness" of the specified basedn. Stopping at the first
     *    TRUE return.
     */
    while ((base_sgcIndex < subgroupclasses->nelts)
           && (result != LDAP_COMPARE_TRUE)) {
        result = uldap_cache_compare(r, ldc, url, dn, "objectClass",
                                     sgc_ents[base_sgcIndex].name);
        if (result != LDAP_COMPARE_TRUE) {
            base_sgcIndex++;
        }
    }

    if (result != LDAP_COMPARE_TRUE) {
        ldc->reason = "DN failed group verification.";
        return result;
    }

    /*
     * 2. Find previously created cache entry and check if there is already a
     *    subgrouplist.
     */
    LDAP_CACHE_LOCK();
    curnode.url = url;
    curl = util_ald_cache_fetch(st->util_ldap_cache, &curnode);
    LDAP_CACHE_UNLOCK();

    if (curl && curl->compare_cache) {
        /* make a comparison to the cache */
        LDAP_CACHE_LOCK();

        the_compare_node.dn = (char *)dn;
        the_compare_node.attrib = (char *)"objectClass";
        the_compare_node.value = (char *)sgc_ents[base_sgcIndex].name;
        the_compare_node.result = 0;
        the_compare_node.sgl_processed = 0;
        the_compare_node.subgroupList = NULL;

        compare_nodep = util_ald_cache_fetch(curl->compare_cache,
                                             &the_compare_node);

        if (compare_nodep != NULL) {
            /*
             * Found the generic group entry... but the user isn't in this
             * group or we wouldn't be here.
             */
            if (compare_nodep->sgl_processed) {
                if (compare_nodep->subgroupList) {
                    /* Make a local copy of the subgroup list */
                    int i;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] util_ldap:"
                                  " Making local copy of SGL for "
                                  "group (%s)(objectClass=%s) ",
                                  getpid(), dn,
                                  (char *)sgc_ents[base_sgcIndex].name);
                    tmp_local_sgl = apr_pcalloc(r->pool,
                                                sizeof(util_compare_subgroup_t));
                    tmp_local_sgl->len = compare_nodep->subgroupList->len;
                    tmp_local_sgl->subgroupDNs =
                        apr_pcalloc(r->pool,
                                    sizeof(char *) * compare_nodep->subgroupList->len);
                    for (i = 0; i < compare_nodep->subgroupList->len; i++) {
                        tmp_local_sgl->subgroupDNs[i] =
                            apr_pstrdup(r->pool,
                                        compare_nodep->subgroupList->subgroupDNs[i]);
                    }
                }
                else {
                    sgl_cached_empty = 1;
                }
            }
        }
        LDAP_CACHE_UNLOCK();
    }

    if (!tmp_local_sgl && !sgl_cached_empty) {
        /* No Cached SGL, retrieve from LDAP */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] util_ldap: no cached SGL for %s,"
                      " retrieving from LDAP" , getpid(), dn);
        tmp_local_sgl = uldap_get_subgroups(r, ldc, url, dn, subgroupAttrs,
                                            subgroupclasses);
        if (!tmp_local_sgl) {
            /* No SGL aailable via LDAP either */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "[%" APR_PID_T_FMT "]"
                          " util_ldap: no subgroups for %s" , getpid(), dn);
        }

      if (curl && curl->compare_cache) {
        /*
         * Find the generic group cache entry and add the sgl we just retrieved.
         */
        LDAP_CACHE_LOCK();

        the_compare_node.dn = (char *)dn;
        the_compare_node.attrib = (char *)"objectClass";
        the_compare_node.value = (char *)sgc_ents[base_sgcIndex].name;
        the_compare_node.result = 0;
        the_compare_node.sgl_processed = 0;
        the_compare_node.subgroupList = NULL;

        compare_nodep = util_ald_cache_fetch(curl->compare_cache,
                                             &the_compare_node);

        if (compare_nodep == NULL) {
            /*
             * The group entry we want to attach our SGL to doesn't exist.
             * We only got here if we verified this DN was actually a group
             * based on the objectClass, but we can't call the compare function
             * while we already hold the cache lock -- only the insert.
             */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "[%" APR_PID_T_FMT "] util_ldap: Cache entry "
                          "for %s doesn't exist",
                           getpid(), dn);
            the_compare_node.result = LDAP_COMPARE_TRUE;
            util_ald_cache_insert(curl->compare_cache, &the_compare_node);
            compare_nodep = util_ald_cache_fetch(curl->compare_cache,
                                                 &the_compare_node);
            if (compare_nodep == NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "[%" APR_PID_T_FMT "] util_ldap: Couldn't "
                              "retrieve group entry for %s from cache",
                               getpid(), dn);
            }
        }

        /*
         * We have a valid cache entry and a locally generated SGL.
         * Attach the SGL to the cache entry
         */
        if (compare_nodep && !compare_nodep->sgl_processed) {
            if (!tmp_local_sgl) {
                /* We looked up an SGL for a group and found it to be empty */
                if (compare_nodep->subgroupList == NULL) {
                    compare_nodep->sgl_processed = 1;
                }
            }
            else {
                util_compare_subgroup_t *sgl_copy =
                    util_ald_sgl_dup(curl->compare_cache, tmp_local_sgl);
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "Copying local SGL of len %d for group %s into cache",
                             tmp_local_sgl->len, dn);
                if (sgl_copy) {
                    if (compare_nodep->subgroupList) {
                        util_ald_sgl_free(curl->compare_cache,
                                          &(compare_nodep->subgroupList));
                    }
                    compare_nodep->subgroupList = sgl_copy;
                    compare_nodep->sgl_processed = 1;
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                                 "Copy of SGL failed to obtain shared memory, "
                                 "couldn't update cache");
                }
            }
        }
        LDAP_CACHE_UNLOCK();
      }
    }

    /*
     * tmp_local_sgl has either been created, or copied out of the cache
     * If tmp_local_sgl is NULL, there are no subgroups to process and we'll
     * return false
     */
    result = LDAP_COMPARE_FALSE;
    if (!tmp_local_sgl) {
        return result;
    }

    while ((result != LDAP_COMPARE_TRUE) && (sgindex < tmp_local_sgl->len)) {
        const char *group = NULL;
        group = tmp_local_sgl->subgroupDNs[sgindex];
        /*
         * 4. Now loop through the subgroupList and call uldap_cache_compare
         * to check for the user.
         */
        result = uldap_cache_compare(r, ldc, url, group, attrib, value);
        if (result == LDAP_COMPARE_TRUE) {
            /*
             * 4.A. We found the user in the subgroup. Return
             * LDAP_COMPARE_TRUE.
             */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "[%" APR_PID_T_FMT "]"
                          " util_ldap: Found user %s in a subgroup (%s) at"
                          " level %d of %d.", getpid(), r->user, group,
                          cur_subgroup_depth+1, max_subgroup_depth);
        }
        else {
            /*
             * 4.B. We didn't find the user in this subgroup, so recurse into
             * it and keep looking.
             */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "[%" APR_PID_T_FMT "]"
                          " util_ldap: user %s not found in subgroup (%s) at"
                          " level %d of %d.", getpid(), r->user, group,
                          cur_subgroup_depth+1, max_subgroup_depth);
            result = uldap_cache_check_subgroups(r, ldc, url, group, attrib,
                                                 value, subgroupAttrs,
                                                 subgroupclasses,
                                                 cur_subgroup_depth+1,
                                                 max_subgroup_depth);
        }
        sgindex++;
    }

    return result;
}