void ssl_scache_remove(server_rec *s, UCHAR *id, int idlen,
                       apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
        ssl_mutex_on(s);
    }

    mc->sesscache->remove(mc->sesscache_context, s, id, idlen, p);

    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
        ssl_mutex_off(s);
    }
}