static BOOL shmcb_subcache_store(server_rec *s, SHMCBHeader *header,
                                 SHMCBSubcache *subcache, 
                                 UCHAR *data, unsigned int data_len,
                                 UCHAR *id, time_t expiry)
{
    unsigned int new_offset, new_idx;
    SHMCBIndex *idx;

    /* Sanity check the input */
    if ((data_len > header->subcache_data_size) || (data_len > SSL_SESSION_MAX_DER)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "inserting session larger (%d) than subcache data area (%d)",
                     data_len, header->subcache_data_size);
        return FALSE;
    }

    /* If there are entries to expire, ditch them first. */
    shmcb_subcache_expire(s, header, subcache);

    /* Loop until there is enough space to insert */
    if (header->subcache_data_size - subcache->data_used < data_len
        || subcache->idx_used == header->index_num) {
        unsigned int loop = 0;

        idx = SHMCB_INDEX(subcache, subcache->idx_pos);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "about to force-expire, subcache: idx_used=%d, "
                     "data_used=%d", subcache->idx_used, subcache->data_used);
        do {
            SHMCBIndex *idx2;

            /* Adjust the indexes by one */
            subcache->idx_pos = SHMCB_CYCLIC_INCREMENT(subcache->idx_pos, 1,
                                                       header->index_num);
            subcache->idx_used--;
            if (!subcache->idx_used) {
                /* There's nothing left */
                subcache->data_used = 0;
                break;
            }
            /* Adjust the data */
            idx2 = SHMCB_INDEX(subcache, subcache->idx_pos);
            subcache->data_used -= SHMCB_CYCLIC_SPACE(idx->data_pos, idx2->data_pos,
                                                      header->subcache_data_size);
            subcache->data_pos = idx2->data_pos;
            /* Stats */
            header->stat_scrolled++;
            /* Loop admin */
            idx = idx2;
            loop++;
        } while (header->subcache_data_size - subcache->data_used < data_len);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "finished force-expire, subcache: idx_used=%d, "
                     "data_used=%d", subcache->idx_used, subcache->data_used);
    }

    /* HERE WE ASSUME THAT THE NEW SESSION SHOULD GO ON THE END! I'M NOT
     * CHECKING WHETHER IT SHOULD BE GENUINELY "INSERTED" SOMEWHERE.
     *
     * We either fix that, or find out at a "higher" (read "mod_ssl")
     * level whether it is possible to have distinct session caches for
     * any attempted tomfoolery to do with different session timeouts.
     * Knowing in advance that we can have a cache-wide constant timeout
     * would make this stuff *MUCH* more efficient. Mind you, it's very
     * efficient right now because I'm ignoring this problem!!!
     */
    /* Insert the data */
    new_offset = SHMCB_CYCLIC_INCREMENT(subcache->data_pos, subcache->data_used,
                                        header->subcache_data_size);
    shmcb_cyclic_ntoc_memcpy(header->subcache_data_size,
                             SHMCB_DATA(header, subcache), new_offset,
                             data, data_len);
    subcache->data_used += data_len;
    /* Insert the index */
    new_idx = SHMCB_CYCLIC_INCREMENT(subcache->idx_pos, subcache->idx_used,
                                     header->index_num);
    idx = SHMCB_INDEX(subcache, new_idx);
    idx->expires = expiry;
    idx->data_pos = new_offset;
    idx->data_used = data_len;
    idx->s_id2 = id[1];
    idx->removed = 0;
    subcache->idx_used++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "insert happened at idx=%d, data=%d", new_idx, new_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "finished insert, subcache: idx_pos/idx_used=%d/%d, "
                 "data_pos/data_used=%d/%d",
                 subcache->idx_pos, subcache->idx_used,
                 subcache->data_pos, subcache->data_used);
    return TRUE;
}