static apr_status_t vt_ndbm_firstkey(apr_dbm_t *dbm, apr_datum_t *pkey)
{
    datum rd;

    rd = dbm_firstkey(dbm->file);

    pkey->dptr = rd.dptr;
    pkey->dsize = rd.dsize;

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, APR_SUCCESS);
}