static util_compare_subgroup_t* uldap_get_subgroups(request_rec *r,
                                                    util_ldap_connection_t *ldc,
                                                    const char *url,
                                                    const char *dn,
                                                    char **subgroupAttrs,
                                                    apr_array_header_t *subgroupclasses)
{
    int failures = 0;
    int result = LDAP_COMPARE_FALSE;
    util_compare_subgroup_t *res = NULL;
    LDAPMessage *sga_res, *entry;
    struct mod_auth_ldap_groupattr_entry_t *sgc_ents;
    apr_array_header_t *subgroups = apr_array_make(r->pool, 20, sizeof(char *));
    util_ldap_state_t *st = (util_ldap_state_t *)
                            ap_get_module_config(r->server->module_config,
                                                 &ldap_module);

    sgc_ents = (struct mod_auth_ldap_groupattr_entry_t *) subgroupclasses->elts;

    if (!subgroupAttrs) {
        return res;
    }

start_over:
    /*
     * 3.B. The cache didn't have any subgrouplist yet. Go check for subgroups.
     */
    if (failures > st->retries) {
        return res;
    }

    if (failures > 0 && st->retry_delay > 0) {
        apr_sleep(st->retry_delay);
    }


    if (LDAP_SUCCESS != (result = uldap_connection_open(r, ldc))) {
        /* connect failed */
        return res;
    }

    /* try to do the search */
    result = ldap_search_ext_s(ldc->ldap, (char *)dn, LDAP_SCOPE_BASE,
                               NULL, subgroupAttrs, 0,
                               NULL, NULL, NULL, APR_LDAP_SIZELIMIT, &sga_res);
    if (AP_LDAP_IS_SERVER_DOWN(result)) {
        ldc->reason = "ldap_search_ext_s() for subgroups failed with server"
                      " down";
        uldap_connection_unbind(ldc);
        failures++;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
        goto start_over;
    }
    if (result == LDAP_TIMEOUT && failures == 0) {
        /*
         * we are reusing a connection that doesn't seem to be active anymore
         * (firewall state drop?), let's try a new connection.
         */
        ldc->reason = "ldap_search_ext_s() for subgroups failed with timeout";
        uldap_connection_unbind(ldc);
        failures++;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "%s (attempt %d)", ldc->reason, failures);
        goto start_over;
    }

    /* if there is an error (including LDAP_NO_SUCH_OBJECT) return now */
    if (result != LDAP_SUCCESS) {
        ldc->reason = "ldap_search_ext_s() for subgroups failed";
        return res;
    }

    entry = ldap_first_entry(ldc->ldap, sga_res);

    /*
     * Get values for the provided sub-group attributes.
     */
    if (subgroupAttrs) {
        int indx = 0, tmp_sgcIndex;

        while (subgroupAttrs[indx]) {
            char **values;
            int val_index = 0;

            /* Get *all* matching "member" values from this group. */
            values = ldap_get_values(ldc->ldap, entry, subgroupAttrs[indx]);

            if (values) {
                val_index = 0;
                /*
                 * Now we are going to pare the subgroup members of this group
                 * to *just* the subgroups, add them to the compare_nodep, and
                 * then proceed to check the new level of subgroups.
                 */
                while (values[val_index]) {
                    /* Check if this entry really is a group. */
                    tmp_sgcIndex = 0;
                    result = LDAP_COMPARE_FALSE;
                    while ((tmp_sgcIndex < subgroupclasses->nelts)
                           && (result != LDAP_COMPARE_TRUE)) {
                        result = uldap_cache_compare(r, ldc, url,
                                                     values[val_index],
                                                     "objectClass",
                                                     sgc_ents[tmp_sgcIndex].name
                                                     );

                        if (result != LDAP_COMPARE_TRUE) {
                            tmp_sgcIndex++;
                        }
                    }
                    /* It's a group, so add it to the array.  */
                    if (result == LDAP_COMPARE_TRUE) {
                        char **newgrp = (char **) apr_array_push(subgroups);
                        *newgrp = apr_pstrdup(r->pool, values[val_index]);
                    }
                    val_index++;
                }
                ldap_value_free(values);
            }
            indx++;
        }
    }

    ldap_msgfree(sga_res);

    if (subgroups->nelts > 0) {
        /* We need to fill in tmp_local_subgroups using the data from LDAP */
        int sgindex;
        char **group;
        res = apr_pcalloc(r->pool, sizeof(util_compare_subgroup_t));
        res->subgroupDNs  = apr_palloc(r->pool,
                                       sizeof(char *) * (subgroups->nelts));
        for (sgindex = 0; (group = apr_array_pop(subgroups)); sgindex++) {
            res->subgroupDNs[sgindex] = apr_pstrdup(r->pool, *group);
        }
        res->len = sgindex;
    }

    return res;
}