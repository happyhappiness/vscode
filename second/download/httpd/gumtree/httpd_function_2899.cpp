static BOOL shmcb_store_session(
    server_rec *s, void *shm_segment, UCHAR *id,
    int idlen, SSL_SESSION * pSession,
    time_t timeout)
{
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned char masked_index;
    unsigned char encoded[SSL_SESSION_MAX_DER];
    unsigned char *ptr_encoded;
    unsigned int len_encoded;
    time_t expiry_time;
    unsigned char *session_id = SSL_SESSION_get_session_id(pSession);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "inside shmcb_store_session");

    /* Get the header structure, which division this session will fall into etc. */
    shmcb_get_header(shm_segment, &header);
    masked_index = session_id[0] & header->division_mask;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "session_id[0]=%u, masked index=%u",
                 session_id[0], masked_index);
    if (!shmcb_get_division(header, &queue, &cache, (unsigned int)masked_index)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_store_session internal error");
        return FALSE;
    }

    /* Serialise the session, work out how much we're dealing
     * with. NB: This check could be removed if we're not paranoid
     * or we find some assurance that it will never be necessary. */
    len_encoded = i2d_SSL_SESSION(pSession, NULL);
    if (len_encoded > SSL_SESSION_MAX_DER) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "session is too big (%u bytes)", len_encoded);
        return FALSE;
    }
    ptr_encoded = encoded;
    len_encoded = i2d_SSL_SESSION(pSession, &ptr_encoded);
    expiry_time = timeout;
    if (!shmcb_insert_encoded_session(s, &queue, &cache, encoded,
                                     len_encoded, session_id,
                                     expiry_time)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "can't store a session!");
        return FALSE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_store successfully");
    header->num_stores++;
    return TRUE;
}