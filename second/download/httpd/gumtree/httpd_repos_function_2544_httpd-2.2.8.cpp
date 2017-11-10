static apr_status_t vt_db_nextkey(apr_dbm_t *dbm, apr_datum_t * pkey)
{
    real_file_t *f = dbm->file;
    DBT ckey = { 0 };
    DBT data = { 0 };
    int dberr;

    ckey.data = pkey->dptr;
    ckey.size = pkey->dsize;

#if DB_VER == 1
    dberr = (*f->bdb->seq)(f->bdb, &ckey, &data, R_NEXT);
    if (dberr == RET_SPECIAL) {
        dberr = 0;
        ckey.data = NULL;
        ckey.size = 0;
    }
#else
    if (f->curs == NULL)
        return APR_EINVAL;

    dberr = (*f->curs->c_get)(f->curs, &ckey, &data, DB_NEXT);
    if (dberr == DB_NOTFOUND) {
        (*f->curs->c_close)(f->curs);
        f->curs = NULL;
        dberr = 0;
        ckey.data = NULL;
        ckey.size = 0;
    }
#endif

    pkey->dptr = ckey.data;
    pkey->dsize = ckey.size;

    /* store any error info into DBM, and return a status code. */
    /* ### or use db2s(dberr) instead of APR_SUCCESS? */
    return set_error(dbm, APR_SUCCESS);
}