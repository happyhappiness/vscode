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


static util_compare_subgroup_t* uldap_get_subgroups(request_rec *r,
                                                    util_ldap_connection_t *ldc,
