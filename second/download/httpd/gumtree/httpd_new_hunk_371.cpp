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
