SSL_SESSION *ssl_scache_retrieve(server_rec *s, UCHAR *id, int idlen,
                                 apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    unsigned char dest[MODSSL_SESSION_MAX_DER];
    unsigned int destlen = MODSSL_SESSION_MAX_DER;
    const unsigned char *ptr;
    apr_status_t rv;

    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
        ssl_mutex_on(s);
    }

    rv = mc->sesscache->retrieve(mc->sesscache_context, s, id, idlen,
                                 dest, &destlen, p);

    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
        ssl_mutex_off(s);
    }

    if (rv != APR_SUCCESS) {
        return NULL;
    }

    ptr = dest;

    return d2i_SSL_SESSION(NULL, &ptr, destlen);
}