static SSL_SESSION *shmcb_lookup_session_id(
    server_rec *s, SHMCBQueue *queue,
    SHMCBCache *cache, UCHAR *id,
    unsigned int idlen)
{
    unsigned char tempasn[SSL_SESSION_MAX_DER];
    SHMCBIndex *idx;
    SHMCBHeader *header;
    SSL_SESSION *pSession = NULL;
    unsigned int curr_pos, loop, count;
    MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr;
    time_t now;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_lookup_session_id");

    /* If there are entries to expire, ditch them first thing. */
    shmcb_expire_division(s, queue, cache);
    now = time(NULL);
    curr_pos = shmcb_get_safe_uint(queue->first_pos);
    count = shmcb_get_safe_uint(queue->pos_count);
    header = queue->header;
    for (loop = 0; loop < count; loop++) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "loop=%u, count=%u, curr_pos=%u",
                     loop, count, curr_pos);
        idx = shmcb_get_index(queue, curr_pos);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "idx->s_id2=%u, id[1]=%u, offset=%u",
                idx->s_id2, id[1], shmcb_get_safe_uint(&(idx->offset)));
        /* Only look into the session further if;
         * (a) the second byte of the session_id matches,
         * (b) the "removed" flag isn't set,
         * (c) the session hasn't expired yet.
         * We do (c) like this so that it saves us having to
         * do natural expiries ... naturally expired sessions
         * scroll off the front anyway when the cache is full and
         * "rotating", the only real issue that remains is the
         * removal or disabling of forcibly killed sessions. */
        if ((idx->s_id2 == id[1]) && !idx->removed &&
            (shmcb_get_safe_time(&(idx->expires)) > now)) {
            unsigned int session_id_length;
            unsigned char *session_id;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "at index %u, found possible session match",
                         curr_pos);
            shmcb_cyclic_cton_memcpy(header->cache_data_size,
                                     tempasn, cache->data,
                                     shmcb_get_safe_uint(&(idx->offset)),
                                     SSL_SESSION_MAX_DER);
            ptr = tempasn;
            pSession = d2i_SSL_SESSION(NULL, &ptr, SSL_SESSION_MAX_DER);
            session_id_length = SSL_SESSION_get_session_id_length(pSession);
            session_id = SSL_SESSION_get_session_id(pSession);

            if (pSession == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "scach2_lookup_session_id internal error");
                return NULL;
            }
            if ((session_id_length == idlen) &&
                (memcmp(session_id, id, idlen) == 0)) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "a match!");
                return pSession;
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
    return NULL;
}