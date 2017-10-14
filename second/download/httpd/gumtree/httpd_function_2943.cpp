void ssl_scache_shmcb_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    SHMCBHeader *header = mc->tSessionCacheDataTable;
    SHMCBSubcache *subcache = SHMCB_MASK(header, id);

    ssl_mutex_on(s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "ssl_scache_shmcb_remove (0x%02x -> subcache %d)",
                 SHMCB_MASK_DBG(header, id));
    if (idlen < 4) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short session_id provided "
                "(%u bytes)", idlen);
        goto done;
    }
    if (shmcb_subcache_remove(s, header, subcache, id, idlen))
        header->stat_removes_hit++;
    else
        header->stat_removes_miss++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving ssl_scache_shmcb_remove successfully");
done:
    ssl_mutex_off(s);
}