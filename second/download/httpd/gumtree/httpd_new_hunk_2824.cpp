             */
            cache->marktime = apr_time_now();
        }
        util_ald_cache_purge(cache);
        tmp_payload = (*cache->copy)(cache, payload);
        if (tmp_payload == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(01327)
                         "Could not allocate memory for LDAP cache value");
            util_ald_free(cache, node);
            return NULL;
        }
    }
    payload = tmp_payload;
