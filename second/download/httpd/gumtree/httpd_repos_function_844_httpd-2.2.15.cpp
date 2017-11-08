void ssl_scache_dc_kill(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->tSessionCacheDataTable)
        DC_CTX_free(mc->tSessionCacheDataTable);
    mc->tSessionCacheDataTable = NULL;
}