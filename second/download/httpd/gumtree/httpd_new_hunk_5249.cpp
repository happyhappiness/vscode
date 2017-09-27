                if (rv != APR_SUCCESS)
                    return rv;
            }
            else {
                /* Already stale, quietly remove and treat as not-found */
                idx->removed = 1;
                header->stat_expiries++;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00856)
                             "shmcb_subcache_iterate discarding expired entry");
            }
        }
        /* Increment */
        loop++;
