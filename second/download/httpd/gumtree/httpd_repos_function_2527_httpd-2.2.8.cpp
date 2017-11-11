static apr_status_t vt_ndbm_fetch(apr_dbm_t *dbm, apr_datum_t key,
                                  apr_datum_t * pvalue)
{
    datum *ckey;
    datum rd;

    ckey = (datum*)&key;
    rd = dbm_fetch(dbm->file, *ckey);
    *pvalue = *(apr_datum_t*)&rd;

    /* store the error info into DBM, and return a status code. Also, note
       that *pvalue should have been cleared on error. */
    return set_error(dbm, APR_SUCCESS);
}