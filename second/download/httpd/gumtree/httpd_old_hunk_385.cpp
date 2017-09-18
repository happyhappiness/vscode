    SHMCBIndex *idx;
    SHMCBHeader *header;
    unsigned int curr_pos, loop, count;
    unsigned char *ptr;
    BOOL to_return = FALSE;

    ssl_log(s, SSL_LOG_TRACE, "entering shmcb_remove_session_id");

    /* If there's entries to expire, ditch them first thing. */
    /* shmcb_expire_division(s, queue, cache); */

    /* Regarding the above ... hmmm ... I know my expiry code is slightly
     * "faster" than all this remove stuff ... but if the higher level
