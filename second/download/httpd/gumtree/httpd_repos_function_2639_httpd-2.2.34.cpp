static apr_status_t vt_gdbm_fetch(apr_dbm_t *dbm, apr_datum_t key,
                                  apr_datum_t *pvalue)
{
    datum kd, rd;

    kd.dptr = key.dptr;
    kd.dsize = key.dsize;

    rd = gdbm_fetch(dbm->file, kd);

    pvalue->dptr = rd.dptr;
    pvalue->dsize = rd.dsize;

    if (pvalue->dptr)
        apr_pool_cleanup_register(dbm->pool, pvalue->dptr, datum_cleanup,
                                  apr_pool_cleanup_null);

    /* store the error info into DBM, and return a status code. Also, note
       that *pvalue should have been cleared on error. */
    return set_error(dbm, APR_SUCCESS);
}