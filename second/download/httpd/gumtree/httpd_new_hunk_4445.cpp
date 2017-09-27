            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(01325)
                         "Could not allocate memory for LDAP cache entry");
            return NULL;
        }
    }

    /* Take a copy of the payload before proceeding. */
    tmp_payload = (*cache->copy)(cache, payload);
    if (tmp_payload == NULL) {
        /*
         * XXX: The cache management should be rewritten to work
         * properly when LDAPSharedCacheSize is too small.
         */
