static const char *dbd_pgsql_escape(apr_pool_t *pool, const char *arg,
                                    apr_dbd_t *sql)
{
    size_t len = strlen(arg);
    char *ret = apr_palloc(pool, 2*len + 2);
    PQescapeString(ret, arg, len);
    return ret;
}