BOOL ssl_scache_shmcb_store(server_rec *s, UCHAR *id, int idlen,
                           time_t timeout, SSL_SESSION * pSession)
{
    SSLModConfigRec *mc = myModConfig(s);
    BOOL to_return = FALSE;
    unsigned char encoded[SSL_SESSION_MAX_DER];
    unsigned char *ptr_encoded;
    unsigned int len_encoded;
    SHMCBHeader *header = mc->tSessionCacheDataTable;
    SHMCBSubcache *subcache = SHMCB_MASK(header, id);

    ssl_mutex_on(s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "ssl_scache_shmcb_store (0x%02x -> subcache %d)",
                 SHMCB_MASK_DBG(header, id));
    if (idlen < 4) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short session_id provided "
                "(%u bytes)", idlen);
        goto done;
    }
    /* Serialise the session. */
    len_encoded = i2d_SSL_SESSION(pSession, NULL);
    if (len_encoded > SSL_SESSION_MAX_DER) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "session is too big (%u bytes)", len_encoded);
        goto done;
    }
    ptr_encoded = encoded;
    len_encoded = i2d_SSL_SESSION(pSession, &ptr_encoded);
    if (!shmcb_subcache_store(s, header, subcache, encoded,
                              len_encoded, id, timeout)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "can't store a session!");
        goto done;
    }
    header->stat_stores++;
    to_return = TRUE;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving ssl_scache_shmcb_store successfully");
done:
    ssl_mutex_off(s);
    return to_return;
}