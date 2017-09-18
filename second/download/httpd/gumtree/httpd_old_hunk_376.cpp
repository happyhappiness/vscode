    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned char masked_index;
    BOOL res;

    ssl_log(s, SSL_LOG_TRACE, "inside shmcb_remove_session");
    if (id == NULL) {
        ssl_log(s, SSL_LOG_ERROR, "remove called with NULL session_id!");
        return FALSE;
    }

    /* Get the header structure, which division this session remove
     * will happen in etc. */
    shmcb_get_header(shm_segment, &header);
    masked_index = id[0] & header->division_mask;
    ssl_log(s, SSL_LOG_TRACE, "id[0]=%u, masked index=%u",
            id[0], masked_index);
    if (!shmcb_get_division(header, &queue, &cache, (unsigned int)masked_index)) {
        ssl_log(s, SSL_LOG_ERROR, "shmcb_remove_session, internal error");
        header->num_removes_miss++;
        return FALSE;
    }
    res = shmcb_remove_session_id(s, &queue, &cache, id, idlen);
    if (res)
        header->num_removes_hit++;
    else
        header->num_removes_miss++;
    ssl_log(s, SSL_LOG_TRACE, "leaving shmcb_remove_session");
    return res;
}


/* 
**
