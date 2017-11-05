static void shmcb_subcache_expire(server_rec *s, SHMCBHeader *header,
                                  SHMCBSubcache *subcache, apr_time_t now)
{
    unsigned int loop = 0;
    unsigned int new_idx_pos = subcache->idx_pos;
    SHMCBIndex *idx = NULL;

    while (loop < subcache->idx_used) {
        idx = SHMCB_INDEX(subcache, new_idx_pos);
        if (idx->expires > now)
            /* it hasn't expired yet, we're done iterating */
            break;
        loop++;
        new_idx_pos = SHMCB_CYCLIC_INCREMENT(new_idx_pos, 1, header->index_num);
    }
    if (!loop)
        /* Nothing to do */
        return;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "will be expiring %u socache entries", loop);
    if (loop == subcache->idx_used) {
        /* We're expiring everything, piece of cake */
        subcache->idx_used = 0;
        subcache->data_used = 0;
    } else {
        /* There remain other indexes, so we can use idx to adjust 'data' */
        unsigned int diff = SHMCB_CYCLIC_SPACE(subcache->data_pos,
                                               idx->data_pos,
                                               header->subcache_data_size);
        /* Adjust the indexes */
        subcache->idx_used -= loop;
        subcache->idx_pos = new_idx_pos;
        /* Adjust the data area */
        subcache->data_used -= diff;
        subcache->data_pos = idx->data_pos;
    }
    header->stat_expiries += loop;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "we now have %u socache entries", subcache->idx_used);
}