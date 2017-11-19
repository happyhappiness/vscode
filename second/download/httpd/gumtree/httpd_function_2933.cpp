static BOOL shmcb_remove_session_id(
    server_rec *s, SHMCBQueue *queue,
    SHMCBCache *cache, UCHAR *id, unsigned int idlen)
{
    unsigned char tempasn[SSL_SESSION_MAX_DER];
    SSL_SESSION *pSession = NULL;
    SHMCBIndex *idx;
    SHMCBHeader *header;
    unsigned int curr_pos, loop, count;
    MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr;
    BOOL to_return = FALSE;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_remove_session_id");

    /* If there's entries to expire, ditch them first thing. */
    /* shmcb_expire_division(s, queue, cache); */

    /* Regarding the above ... hmmm ... I know my expiry code is slightly
     * "faster" than all this remove stuff ... but if the higher level
     * code calls a "remove" operation (and this *only* seems to happen
     * when it has spotted an expired session before we had a chance to)
     * then it should get credit for a remove (stats-wise). Also, in the
     * off-chance that the server *requests* a renegotiate and wants to
     * wipe the session clean we should give that priority over our own
     * routine expiry handling. So I've moved the expiry check to *after*
     * this general remove stuff. */
    curr_pos = shmcb_get_safe_uint(queue->first_pos);
    count = shmcb_get_safe_uint(queue->pos_count);
    header = cache->header;
    for (loop = 0; loop < count; loop++) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "loop=%u, count=%u, curr_pos=%u",
                loop, count, curr_pos);
        idx = shmcb_get_index(queue, curr_pos);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "idx->s_id2=%u, id[1]=%u", idx->s_id2,
                id[1]);
        /* Only look into the session further if the second byte of the
         * session_id matches. */
        if (idx->s_id2 == id[1]) {
            unsigned int session_id_length;
            unsigned char *session_id;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "at index %u, found possible "
                         "session match", curr_pos);
            shmcb_cyclic_cton_memcpy(header->cache_data_size,
                                     tempasn, cache->data,
                                     shmcb_get_safe_uint(&(idx->offset)),
                                     SSL_SESSION_MAX_DER);
            ptr = tempasn;
            pSession = d2i_SSL_SESSION(NULL, &ptr, SSL_SESSION_MAX_DER);
            if (pSession == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "shmcb_remove_session_id, internal error");
                goto end;
            }
            session_id_length = SSL_SESSION_get_session_id_length(pSession);
            session_id = SSL_SESSION_get_session_id(pSession);

            if ((session_id_length == idlen)
                 && (memcmp(id, session_id, idlen) == 0)) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                            "a match!");
                /* Scrub out this session "quietly" */
                idx->removed = (unsigned char) 1;
                SSL_SESSION_free(pSession);
                to_return = TRUE;
                goto end;
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "not a match");
            SSL_SESSION_free(pSession);
            pSession = NULL;
        }
        curr_pos = shmcb_cyclic_increment(header->index_num, curr_pos, 1);
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "no matching sessions were found");

    /* If there's entries to expire, ditch them now. */
    shmcb_expire_division(s, queue, cache);
end:
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving shmcb_remove_session_id");
    return to_return;
}