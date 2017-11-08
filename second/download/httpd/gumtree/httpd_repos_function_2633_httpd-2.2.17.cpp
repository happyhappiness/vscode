static apr_status_t vt_sdbm_fetch(apr_dbm_t *dbm, apr_datum_t key,
                                  apr_datum_t *pvalue)
{
    apr_status_t rv;
    apr_sdbm_datum_t kd, rd;

    kd.dptr = key.dptr;
    kd.dsize = (int)key.dsize;

    rv = apr_sdbm_fetch(dbm->file, &rd, kd);

    pvalue->dptr = rd.dptr;
    pvalue->dsize = rd.dsize;

    /* store the error info into DBM, and return a status code. Also, note
       that *pvalue should have been cleared on error. */
    return set_error(dbm, rv);
}