    unsigned char encoded[SSL_SESSION_MAX_DER];
    unsigned char *ptr_encoded;
    unsigned int len_encoded;
    time_t expiry_time;
    unsigned char *session_id = SSL_SESSION_get_session_id(pSession);

    ssl_log(s, SSL_LOG_TRACE, "inside shmcb_store_session");

    /* Get the header structure, which division this session will fall into etc. */
    shmcb_get_header(shm_segment, &header);
    masked_index = session_id[0] & header->division_mask;
    ssl_log(s, SSL_LOG_TRACE, "session_id[0]=%u, masked index=%u",
            session_id[0], masked_index);
    if (!shmcb_get_division(header, &queue, &cache, (unsigned int)masked_index)) {
        ssl_log(s, SSL_LOG_ERROR, "shmcb_store_session, " "internal error");
        return FALSE;
    }

    /* Serialise the session, work out how much we're dealing
     * with. NB: This check could be removed if we're not paranoid
     * or we find some assurance that it will never be necessary. */
    len_encoded = i2d_SSL_SESSION(pSession, NULL);
    if (len_encoded > SSL_SESSION_MAX_DER) {
        ssl_log(s, SSL_LOG_ERROR, "session is too big (%u bytes)",
                len_encoded);
        return FALSE;
    }
    ptr_encoded = encoded;
    len_encoded = i2d_SSL_SESSION(pSession, &ptr_encoded);
    expiry_time = timeout;
    if (!shmcb_insert_encoded_session(s, &queue, &cache, encoded,
                                     len_encoded, session_id,
                                     expiry_time)) {
        ssl_log(s, SSL_LOG_ERROR, "can't store a session!");
        return FALSE;
    }
    ssl_log(s, SSL_LOG_TRACE, "leaving shmcb_store successfully");
    header->num_stores++;
    return TRUE;
}

static SSL_SESSION *shmcb_retrieve_session(
    server_rec *s, void *shm_segment,
