static int stapling_refresh_mutex_off(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    return stapling_mutex_off(s, mc->stapling_refresh_mutex,
                              SSL_STAPLING_REFRESH_MUTEX_TYPE);
}