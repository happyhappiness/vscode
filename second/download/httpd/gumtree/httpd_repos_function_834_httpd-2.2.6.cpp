void ssl_scache_dc_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    DC_CTX *ctx = mc->tSessionCacheDataTable;

    /* Remove any corresponding session from the distributed cache context */
    if (!DC_CTX_remove_session(ctx, id, idlen)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'remove_session' MISS");
    } else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'remove_session' HIT");
    }
}