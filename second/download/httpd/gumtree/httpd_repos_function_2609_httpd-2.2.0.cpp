static const char *dbd_sqlite_escape(apr_pool_t * pool, const char *arg,
                                     apr_dbd_t * sql)
{
    char *ret = sqlite_mprintf(arg);
    apr_pool_cleanup_register(pool, ret, (void *) sqlite_freemem,
                              apr_pool_cleanup_null);
    return ret;
}