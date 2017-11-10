void ssl_scache_shmht_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);

    /* remove value under key in table */
    ssl_mutex_on(s);
    table_delete(mc->tSessionCacheDataTable, id, idlen, NULL, NULL);
    ssl_mutex_off(s);
    return;
}