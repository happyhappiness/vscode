        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "inserting socache entry larger (%d) than subcache data area (%d)",
                     total_len, header->subcache_data_size);
        return -1;
    }

    /* If there are entries to expire, ditch them first. */
    shmcb_subcache_expire(s, header, subcache, apr_time_now());

    /* Loop until there is enough space to insert */
    if (header->subcache_data_size - subcache->data_used < total_len
        || subcache->idx_used == header->index_num) {
        unsigned int loop = 0;

        idx = SHMCB_INDEX(subcache, subcache->idx_pos);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
