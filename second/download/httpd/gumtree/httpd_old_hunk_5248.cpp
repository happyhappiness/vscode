
                return 0;
            }
            else {
                /* Already stale, quietly remove and treat as not-found */
                idx->removed = 1;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00850)
                             "shmcb_subcache_retrieve discarding expired entry");
                return -1;
            }
        }
        /* Increment */
