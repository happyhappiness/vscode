static apr_status_t vt_sdbm_nextkey(apr_dbm_t *dbm, apr_datum_t *pkey)
{
    apr_sdbm_datum_t rd;

    (void)apr_sdbm_nextkey(dbm->file, &rd);

    pkey->dptr = rd.dptr;
    pkey->dsize = rd.dsize;

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, APR_SUCCESS);
}