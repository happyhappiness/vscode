static char *get_dbm_entry_as_str(apr_pool_t *pool, apr_dbm_t *f, char *key)
{
    apr_datum_t d, q;
    q.dptr = key;

#ifndef NETSCAPE_DBM_COMPAT
    q.dsize = strlen(q.dptr);
#else
    q.dsize = strlen(q.dptr) + 1;
#endif

    if (apr_dbm_fetch(f, q, &d) == APR_SUCCESS && d.dptr) {
        return apr_pstrmemdup(pool, d.dptr, d.dsize);
    }

    return NULL;
}