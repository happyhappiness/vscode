static const char *dbd_oracle_escape(apr_pool_t *pool, const char *arg,
                                     apr_dbd_t *sql)
{
    return arg;        /* OCI has no concept of string escape */
}