static int vt_db_exists(apr_dbm_t *dbm, apr_datum_t key)
{
    DBT ckey = { 0 };   /* converted key */
    DBT data = { 0 };
    int dberr;

    ckey.data = key.dptr;
    ckey.size = key.dsize;

    dberr = do_fetch(GET_BDB(dbm->file), ckey, data);

    /* note: the result data is "loaned" to us; we don't need to free it */

    /* DB returns DB_NOTFOUND if it doesn't exist. but we want to say
       that *any* error means it doesn't exist. */
    return dberr == 0;
}