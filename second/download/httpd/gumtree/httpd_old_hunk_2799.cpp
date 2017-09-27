        }
        LDAP_CACHE_UNLOCK();
    }

    if (!tmp_local_sgl && !sgl_cached_empty) {
        /* No Cached SGL, retrieve from LDAP */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "no cached SGL for %s, retrieving from LDAP", dn);
        tmp_local_sgl = uldap_get_subgroups(r, ldc, url, dn, subgroupAttrs,
                                            subgroupclasses);
        if (!tmp_local_sgl) {
            /* No SGL aailable via LDAP either */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "no subgroups for %s",
                          dn);
        }

      if (curl && curl->compare_cache) {
        /*
         * Find the generic group cache entry and add the sgl we just retrieved.
