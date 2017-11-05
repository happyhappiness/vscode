static BOOL shmcb_remove_session(
    server_rec *s, void *shm_segment,
    UCHAR *id, int idlen)
{
    SHMCBHeader *header;
    SHMCBQueue queue;
    SHMCBCache cache;
    unsigned char masked_index;
    BOOL res;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "inside shmcb_remove_session");
    if (id == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "remove called with NULL session_id!");
        return FALSE;
    }

    /* Get the header structure, which division this session remove
     * will happen in etc. */
    shmcb_get_header(shm_segment, &header);
    masked_index = id[0] & header->division_mask;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "id[0]=%u, masked index=%u", id[0], masked_index);
    if (!shmcb_get_division(header, &queue, &cache, (unsigned int)masked_index)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "shmcb_remove_session, internal error");
        header->num_removes_miss++;
        return FALSE;
    }
    res = shmcb_remove_session_id(s, &queue, &cache, id, idlen);
    if (res)
        header->num_removes_hit++;
    else
        header->num_removes_miss++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_remove_session");
    return res;
}