void ssl_scache_shmcb_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    void *shm_segment;

    /* We've kludged our pointer into the other cache's member variable. */
    shm_segment = (void *) mc->tSessionCacheDataTable;
    ssl_mutex_on(s);
    shmcb_remove_session(s, shm_segment, id, idlen);
    ssl_mutex_off(s);
}