static apr_status_t vt_db_fetch(apr_dbm_t *dbm, apr_datum_t key,
                                apr_datum_t * pvalue)
{
    DBT ckey = { 0 };
    DBT rd = { 0 };
    int dberr;

    ckey.data = key.dptr;
    ckey.size = key.dsize;

    dberr = do_fetch(GET_BDB(dbm->file), ckey, rd);

    /* "not found" is not an error. return zero'd value. */
    if (dberr ==
#if DB_VER == 1
        RET_SPECIAL
#else
        DB_NOTFOUND
#endif
        ) {
        memset(&rd, 0, sizeof(rd));
        dberr = 0;
    }

    pvalue->dptr = rd.data;
    pvalue->dsize = rd.size;

    /* store the error info into DBM, and return a status code. Also, note
       that *pvalue should have been cleared on error. */
    return set_error(dbm, db2s(dberr));
}