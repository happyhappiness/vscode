        subcache->idx_used -= loop;
        subcache->idx_pos = new_idx_pos;
        /* Adjust the data area */
        subcache->data_used -= diff;
        subcache->data_pos = idx->data_pos;
    }
    header->stat_expiries += expired;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "we now have %u socache entries", subcache->idx_used);
}

static int shmcb_subcache_store(server_rec *s, SHMCBHeader *header,
                                SHMCBSubcache *subcache, 
