
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
        loop++;
        pos = SHMCB_CYCLIC_INCREMENT(pos, 1, header->index_num);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00851)
                 "shmcb_subcache_retrieve found no match");
    return -1;
}

static int shmcb_subcache_remove(server_rec *s, SHMCBHeader *header,
                                 SHMCBSubcache *subcache,
