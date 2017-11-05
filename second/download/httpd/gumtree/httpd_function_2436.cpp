static BOOL shmcb_init_memory(
    server_rec *s, void *shm_mem,
    unsigned int shm_mem_size)
{
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned int temp, loop, granularity;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entered shmcb_init_memory()");

    /* Calculate some sizes... */
    temp = sizeof(SHMCBHeader);

    /* If the segment is ridiculously too small, bail out */
    if (shm_mem_size < (2*temp)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shared memory segment too small");
        return FALSE;
    }

    /* Make temp the amount of memory without the header */
    temp = shm_mem_size - temp;

    /* Work on the basis that you need 10 bytes index for each session
     * (approx 150 bytes), which is to divide temp by 160 - and then
     * make sure we err on having too index space to burn even when
     * the cache is full, which is a lot less stupid than having
     * having not enough index space to utilise the whole cache!. */
    temp /= 120;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "for %u bytes, recommending %u indexes",
                 shm_mem_size, temp);

    /* We should divide these indexes evenly amongst the queues. Try
     * to get it so that there are roughly half the number of divisions
     * as there are indexes in each division. */
    granularity = 256;
    while ((temp / granularity) < (2 * granularity))
        granularity /= 2;

    /* So we have 'granularity' divisions, set 'temp' equal to the
     * number of indexes in each division. */
    temp /= granularity;

    /* Too small? Bail ... */
    if (temp < 5) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shared memory segment too small");
        return FALSE;
    }

    /* OK, we're sorted - from here on in, the return should be TRUE */
    header = (SHMCBHeader *)shm_mem;
    header->division_mask = (unsigned char)(granularity - 1);
    header->division_offset = sizeof(SHMCBHeader);
    header->index_num = temp;
    header->index_offset = (2 * sizeof(unsigned int));
    header->index_size = sizeof(SHMCBIndex);
    header->queue_size = header->index_offset +
                         (header->index_num * header->index_size);

    /* Now calculate the space for each division */
    temp = shm_mem_size - header->division_offset;
    header->division_size = temp / granularity;

    /* Calculate the space left in each division for the cache */
    temp -= header->queue_size;
    header->cache_data_offset = (2 * sizeof(unsigned int));
    header->cache_data_size = header->division_size -
                              header->queue_size - header->cache_data_offset;

    /* Output trace info */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_init_memory choices follow");
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "division_mask = 0x%02X", header->division_mask);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "division_offset = %u", header->division_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "division_size = %u", header->division_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "queue_size = %u", header->queue_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "index_num = %u", header->index_num);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "index_offset = %u", header->index_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "index_size = %u", header->index_size);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "cache_data_offset = %u", header->cache_data_offset);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "cache_data_size = %u", header->cache_data_size);

    /* The header is done, make the caches empty */
    for (loop = 0; loop < granularity; loop++) {
        if (!shmcb_get_division(header, &queue, &cache, loop))
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "shmcb_init_memory, " "internal error");
        shmcb_set_safe_uint(cache.first_pos, 0);
        shmcb_set_safe_uint(cache.pos_count, 0);
        shmcb_set_safe_uint(queue.first_pos, 0);
        shmcb_set_safe_uint(queue.pos_count, 0);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_init_memory()");
    return TRUE;
}