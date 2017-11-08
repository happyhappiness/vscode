static SSL_SESSION *shmcb_subcache_retrieve(server_rec *s, SHMCBHeader *header,
                                            SHMCBSubcache *subcache, UCHAR *id,
                                            unsigned int idlen)
{
    unsigned int pos;
    unsigned int loop = 0;

    /* If there are entries to expire, ditch them first. */
    shmcb_subcache_expire(s, header, subcache);
    pos = subcache->idx_pos;

    while (loop < subcache->idx_used) {
        SHMCBIndex *idx = SHMCB_INDEX(subcache, pos);

        /* Only consider 'idx' if;
         * (a) the s_id2 byte matches
         * (b) the "removed" flag isn't set.
         */
        if ((idx->s_id2 == id[1]) && !idx->removed) {
            SSL_SESSION *pSession;
            unsigned char *s_id;
            unsigned int s_idlen;
            unsigned char tempasn[SSL_SESSION_MAX_DER];
            MODSSL_D2I_SSL_SESSION_CONST unsigned char *ptr = tempasn;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "possible match at idx=%d, data=%d", pos, idx->data_pos);
            /* Copy the data */
            shmcb_cyclic_cton_memcpy(header->subcache_data_size,
                                     tempasn, SHMCB_DATA(header, subcache),
                                     idx->data_pos, idx->data_used);
            /* Decode the session */
            pSession = d2i_SSL_SESSION(NULL, &ptr, idx->data_used);
            if (!pSession) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "shmcb_subcache_retrieve internal error");
                return NULL;
            }
            s_id = SSL_SESSION_get_session_id(pSession);
            s_idlen = SSL_SESSION_get_session_id_length(pSession);
            if (s_idlen == idlen && memcmp(s_id, id, idlen) == 0) {
                /* Found the matching session */
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "shmcb_subcache_retrieve returning matching session");
                return pSession;
            }
            SSL_SESSION_free(pSession);
        }
        /* Increment */
        loop++;
        pos = SHMCB_CYCLIC_INCREMENT(pos, 1, header->index_num);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "shmcb_subcache_retrieve found no match");
    return NULL;
}