static int shmcb_subcache_remove(server_rec *s, SHMCBHeader *header,
                                 SHMCBSubcache *subcache,
                                 const unsigned char *id,
                                 unsigned int idlen)
{
    unsigned int pos;
    unsigned int loop = 0;

    pos = subcache->idx_pos;
    while (loop < subcache->idx_used) {
        SHMCBIndex *idx = SHMCB_INDEX(subcache, pos);

        /* Only consider 'idx' if the id matches, and the "removed"
         * flag isn't set. */
        if (!idx->removed && idx->id_len == idlen
            && shmcb_cyclic_memcmp(header->subcache_data_size,
                                   SHMCB_DATA(header, subcache),
                                   idx->data_pos, id, idx->id_len) == 0) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "possible match at idx=%d, data=%d", pos, idx->data_pos);

            /* Found the matching entry, remove it quietly. */
            idx->removed = 1;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "shmcb_subcache_remove removing matching entry");
            return 0;
        }
        /* Increment */
        loop++;
        pos = SHMCB_CYCLIC_INCREMENT(pos, 1, header->index_num);
    }

    return -1; /* failure */
}