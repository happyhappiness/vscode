static SSL_SESSION *shmcb_retrieve_session(
    server_rec *s, void *shm_segment,
    UCHAR *id, int idlen)
{
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned char masked_index;
    SSL_SESSION *pSession;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "inside shmcb_retrieve_session");
    if (idlen < 2) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short session_id provided "
                "(%u bytes)", idlen);
        return FALSE;
    }

    /* Get the header structure, which division this session lookup
     * will come from etc. */
    shmcb_get_header(shm_segment, &header);
    masked_index = id[0] & header->division_mask;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "id[0]=%u, masked index=%u", id[0], masked_index);
    if (!shmcb_get_division(header, &queue, &cache, (unsigned int) masked_index)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "shmcb_retrieve_session internal error");
        header->num_retrieves_miss++;
        return FALSE;
    }

    /* Get the session corresponding to the session_id or NULL if it
     * doesn't exist (or is flagged as "removed"). */
    pSession = shmcb_lookup_session_id(s, &queue, &cache, id, idlen);
    if (pSession)
        header->num_retrieves_hit++;
    else
        header->num_retrieves_miss++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_retrieve_session");
    return pSession;
}