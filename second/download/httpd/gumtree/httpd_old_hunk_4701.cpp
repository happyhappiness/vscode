                & AP_SOCACHE_FLAG_NOTMPSAFE) {

            rv = ap_global_mutex_create(&socache_mutex, NULL, cache_socache_id,
                    NULL, s, pconf, 0);
            if (rv != APR_SUCCESS) {
                ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(02391)
                "failed to create %s mutex", cache_socache_id);
                return 500; /* An HTTP status would be a misnomer! */
            }
            apr_pool_cleanup_register(pconf, NULL, remove_lock,
                    apr_pool_cleanup_null);
        }

