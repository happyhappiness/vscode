    /* So we have 'granularity' divisions, set 'temp' equal to the
     * number of indexes in each division. */
    temp /= granularity;

    /* Too small? Bail ... */
    if (temp < 5) {
        ssl_log(s, SSL_LOG_ERROR, "shared memory segment too small");
        return FALSE;
    }

    /* OK, we're sorted - from here on in, the return should be TRUE */
    header = (SHMCBHeader *)shm_mem;
    header->division_mask = (unsigned char)(granularity - 1);
