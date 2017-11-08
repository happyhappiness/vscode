static apr_status_t vt_ndbm_nextkey(apr_dbm_t *dbm, apr_datum_t * pkey)
{
    datum *ckey;
    datum rd;

    ckey = (datum*)pkey;
    rd = dbm_nextkey(dbm->file);
    *pkey = *(apr_datum_t*)&rd;

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, APR_SUCCESS);
}