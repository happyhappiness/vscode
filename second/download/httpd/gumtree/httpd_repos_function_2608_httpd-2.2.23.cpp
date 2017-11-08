static apr_status_t vt_gdbm_firstkey(apr_dbm_t *dbm, apr_datum_t *pkey)
{
    datum rd;

    rd = gdbm_firstkey(dbm->file);

    pkey->dptr = rd.dptr;
    pkey->dsize = rd.dsize;

    if (pkey->dptr)
        apr_pool_cleanup_register(dbm->pool, pkey->dptr, datum_cleanup,
                                  apr_pool_cleanup_null);

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, APR_SUCCESS);
}