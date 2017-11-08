void ssl_scache_shmcb_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);

    ssl_mutex_on(s);
    shmcb_remove_session(s, mc->tSessionCacheDataTable, id, idlen);
    ssl_mutex_off(s);
}