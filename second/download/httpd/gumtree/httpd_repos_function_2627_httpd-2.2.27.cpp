static apr_status_t vt_ndbm_nextkey(apr_dbm_t *dbm, apr_datum_t *pkey)
{
    datum kd, rd;

    kd.dptr = pkey->dptr;
    kd.dsize = pkey->dsize;

    rd = dbm_nextkey(dbm->file);

    pkey->dptr = rd.dptr;
    pkey->dsize = rd.dsize;

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, APR_SUCCESS);
}