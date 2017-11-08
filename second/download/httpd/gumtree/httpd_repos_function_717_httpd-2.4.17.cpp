static int stapling_cache_mutex_on(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    return stapling_mutex_on(s, mc->stapling_cache_mutex,
                             SSL_STAPLING_CACHE_MUTEX_TYPE);
}