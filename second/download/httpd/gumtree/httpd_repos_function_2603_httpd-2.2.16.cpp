static apr_status_t vt_ndbm_fetch(apr_dbm_t *dbm, apr_datum_t key,
                                  apr_datum_t *pvalue)
{
    datum kd, rd;

    kd.dptr = key.dptr;
    kd.dsize = key.dsize;

    rd = dbm_fetch(dbm->file, kd);

    pvalue->dptr = rd.dptr;
    pvalue->dsize = rd.dsize;

    /* store the error info into DBM, and return a status code. Also, note
       that *pvalue should have been cleared on error. */
    return set_error(dbm, APR_SUCCESS);
}