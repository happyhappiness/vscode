static apr_status_t vt_sdbm_firstkey(apr_dbm_t *dbm, apr_datum_t *pkey)
{
    apr_status_t rv;
    apr_sdbm_datum_t rd;

    rv = apr_sdbm_firstkey(dbm->file, &rd);

    pkey->dptr = rd.dptr;
    pkey->dsize = rd.dsize;

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, rv);
}