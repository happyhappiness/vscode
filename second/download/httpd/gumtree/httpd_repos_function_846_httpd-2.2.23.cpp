static BOOL shmcb_subcache_remove(server_rec *s, SHMCBHeader *header,
                                  SHMCBSubcache *subcache,
                                  UCHAR *id, unsigned int idlen)
{
    unsigned int pos;
    unsigned int loop = 0;
    BOOL to_return = FALSE;

    /* Unlike the others, we don't do an expire-run first. This is to keep
     * consistent statistics where a "remove" operation may actually be the
     * higher layer spotting an expiry issue prior to us. Our caller is
     * handling stats, so a failure return would be inconsistent if the
     * intended session was in fact removed by an expiry run. */

    pos = subcache->idx_pos;
    while (!to_return && (loop < subcache->idx_used)) {
        SHMCBIndex *idx = SHMCB_INDEX(subcache, pos);
        /* Only consider 'idx' if the s_id2 byte matches and it's not already
         * removed - easiest way to avoid costly ASN decodings. */
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
                             "shmcb_subcache_remove internal error");
                return FALSE;
            }
            s_id = SSL_SESSION_get_session_id(pSession);
            s_idlen = SSL_SESSION_get_session_id_length(pSession);
            if (s_idlen == idlen && memcmp(s_id, id, idlen) == 0) {
                /* Found the matching session, remove it quietly. */
                idx->removed = 1;
                to_return = TRUE;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "shmcb_subcache_remove removing matching session");
            }
            SSL_SESSION_free(pSession);
        }
        /* Increment */
        loop++;
        pos = SHMCB_CYCLIC_INCREMENT(pos, 1, header->index_num);
    }

    return to_return;
}