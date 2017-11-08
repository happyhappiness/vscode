static apr_status_t vt_db_del(apr_dbm_t *dbm, apr_datum_t key)
{
    apr_status_t rv;
    DBT ckey = { 0 };

    ckey.data = key.dptr;
    ckey.size = key.dsize;

    rv = db2s((*GET_BDB(dbm->file)->del)(GET_BDB(dbm->file),
                                         TXN_ARG
                                         &ckey,
                                         0));

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, rv);
}