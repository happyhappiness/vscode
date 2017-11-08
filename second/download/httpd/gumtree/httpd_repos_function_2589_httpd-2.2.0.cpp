static const char *dbd_sqlite3_escape(apr_pool_t *pool, const char *arg,
                                      apr_dbd_t *sql)
{
    char *ret = sqlite3_mprintf(arg);
    apr_pool_cleanup_register(pool, ret, (void *) sqlite3_free,
                              apr_pool_cleanup_null);
    return ret;
}