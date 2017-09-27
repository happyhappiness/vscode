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
                                unsigned char *data, unsigned int data_len,
                                const unsigned char *id, unsigned int id_len,
                                apr_time_t expiry)
{
    unsigned int data_offset, new_idx, id_offset;
    SHMCBIndex *idx;
    unsigned int total_len = id_len + data_len;

    /* Sanity check the input */
    if (total_len > header->subcache_data_size) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "inserting socache entry larger (%d) than subcache data area (%d)",
                     total_len, header->subcache_data_size);
        return -1;
    }

    /* First reclaim space from removed and expired records. */
