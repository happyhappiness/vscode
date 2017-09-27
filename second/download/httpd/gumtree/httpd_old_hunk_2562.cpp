        loop++;
        new_idx_pos = SHMCB_CYCLIC_INCREMENT(new_idx_pos, 1, header->index_num);
    }
    if (!loop)
        /* Nothing to do */
        return;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "expiring %u and reclaiming %u removed socache entries",
                 expired, freed);
    if (loop == subcache->idx_used) {
        /* We're expiring everything, piece of cake */
        subcache->idx_used = 0;
        subcache->data_used = 0;
