    SHMCBHeader *header;
    SSL_SESSION *pSession = NULL;
    unsigned int curr_pos, loop, count;
    unsigned char *ptr;
    time_t now;

    ssl_log(s, SSL_LOG_TRACE, "entering shmcb_lookup_session_id");

    /* If there are entries to expire, ditch them first thing. */
    shmcb_expire_division(s, queue, cache);
    now = time(NULL);
    curr_pos = shmcb_get_safe_uint(queue->first_pos);
    count = shmcb_get_safe_uint(queue->pos_count);
    header = queue->header;
    for (loop = 0; loop < count; loop++) {
        ssl_log(s, SSL_LOG_TRACE, "loop=%u, count=%u, curr_pos=%u",
                loop, count, curr_pos);
        idx = shmcb_get_index(queue, curr_pos);
        ssl_log(s, SSL_LOG_TRACE, "idx->s_id2=%u, id[1]=%u, offset=%u",
                idx->s_id2, id[1], shmcb_get_safe_uint(&(idx->offset)));
        /* Only look into the session further if;
         * (a) the second byte of the session_id matches,
         * (b) the "removed" flag isn't set,
         * (c) the session hasn't expired yet.
         * We do (c) like this so that it saves us having to
