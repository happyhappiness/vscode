static int stapling_cache_mutex_off(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    return stapling_mutex_off(s, mc->stapling_cache_mutex,
                              SSL_STAPLING_CACHE_MUTEX_TYPE);
}