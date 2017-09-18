{
    SHMCBIndex *idx;
    time_t now;
    unsigned int loop, index_num, pos_count, new_pos;
    SHMCBHeader *header;

    ssl_log(s, SSL_LOG_TRACE, "entering shmcb_expire_division");

    /* We must calculate num and space ourselves based on expiry times. */
    now = time(NULL);
    loop = 0;
    new_pos = shmcb_get_safe_uint(queue->first_pos);

