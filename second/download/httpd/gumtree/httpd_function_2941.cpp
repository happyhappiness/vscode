SSL_SESSION *ssl_scache_shmcb_retrieve(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSL_SESSION *pSession = NULL;
    SHMCBHeader *header = mc->tSessionCacheDataTable;
    SHMCBSubcache *subcache = SHMCB_MASK(header, id);

    ssl_mutex_on(s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "ssl_scache_shmcb_retrieve (0x%02x -> subcache %d)",
                 SHMCB_MASK_DBG(header, id));
    if (idlen < 4) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short session_id provided "
                "(%u bytes)", idlen);
        goto done;
    }
    /* Get the session corresponding to the session_id or NULL if it doesn't
     * exist (or is flagged as "removed"). */
    pSession = shmcb_subcache_retrieve(s, header, subcache, id, idlen);
    if (pSession)
        header->stat_retrieves_hit++;
    else
        header->stat_retrieves_miss++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving ssl_scache_shmcb_retrieve successfully");
done:
    ssl_mutex_off(s);
    return pSession;
}