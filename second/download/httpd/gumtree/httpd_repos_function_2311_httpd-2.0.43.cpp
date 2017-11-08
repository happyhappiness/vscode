static apr_status_t vt_db_firstkey(apr_dbm_t *dbm, apr_datum_t * pkey)
{
    real_file_t *f = dbm->file;
    DBT first = { 0 };
    DBT data = { 0 };
    int dberr;

#if DB_VER == 1
    dberr = (*f->bdb->seq)(f->bdb, &first, &data, R_FIRST);
#else
    if ((dberr = (*f->bdb->cursor)(f->bdb, NULL, &f->curs
#if DB_VER == 3
                                , 0
#elif (DB_VERSION_MAJOR == 2) && (DB_VERSION_MINOR > 5) 
                                , 0

#endif
             )) == 0) {
        dberr = (*f->curs->c_get)(f->curs, &first, &data, DB_FIRST);
        if (dberr == DB_NOTFOUND) {
            memset(&first, 0, sizeof(first));
            (*f->curs->c_close)(f->curs);
            f->curs = NULL;
            dberr = 0;
        }
    }
#endif

    pkey->dptr = first.data;
    pkey->dsize = first.size;

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, db2s(dberr));
}