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

static BOOL shmcb_remove_session_id(
    server_rec *s, SHMCBQueue *queue,
    SHMCBCache *cache, UCHAR *id, unsigned int idlen)
