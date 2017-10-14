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
    shmcb_subcache_expire(s, header, subcache, apr_time_now());

    /* Loop until there is enough space to insert
     * XXX: This should first compress out-of-order expiries and
     * removed records, and then force-remove oldest-first
     */
    if (header->subcache_data_size - subcache->data_used < total_len
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
        } while (header->subcache_data_size - subcache->data_used < total_len);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "finished force-expire, subcache: idx_used=%d, "
                     "data_used=%d", subcache->idx_used, subcache->data_used);
    }

    /* HERE WE ASSUME THAT THE NEW ENTRY SHOULD GO ON THE END! I'M NOT
     * CHECKING WHETHER IT SHOULD BE GENUINELY "INSERTED" SOMEWHERE.
     *
     * We aught to fix that.  httpd (never mind third party modules)
     * does not promise to perform any processing in date order
     * (c.f. FAQ "My log entries are not in date order!")
     */
    /* Insert the id */
    id_offset = SHMCB_CYCLIC_INCREMENT(subcache->data_pos, subcache->data_used,
                                       header->subcache_data_size);
    shmcb_cyclic_ntoc_memcpy(header->subcache_data_size,
                             SHMCB_DATA(header, subcache), id_offset,
                             id, id_len);
    subcache->data_used += id_len;
    /* Insert the data */
    data_offset = SHMCB_CYCLIC_INCREMENT(subcache->data_pos, subcache->data_used,
                                         header->subcache_data_size);
    shmcb_cyclic_ntoc_memcpy(header->subcache_data_size,
                             SHMCB_DATA(header, subcache), data_offset,
                             data, data_len);
    subcache->data_used += data_len;
    /* Insert the index */
    new_idx = SHMCB_CYCLIC_INCREMENT(subcache->idx_pos, subcache->idx_used,
                                     header->index_num);
    idx = SHMCB_INDEX(subcache, new_idx);
    idx->expires = expiry;
    idx->data_pos = id_offset;
    idx->data_used = total_len;
    idx->id_len = id_len;
    idx->removed = 0;
    subcache->idx_used++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "insert happened at idx=%d, data=(%u:%u)", new_idx, 
                 id_offset, data_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "finished insert, subcache: idx_pos/idx_used=%d/%d, "
                 "data_pos/data_used=%d/%d",
                 subcache->idx_pos, subcache->idx_used,
                 subcache->data_pos, subcache->data_used);
    return 0;
}