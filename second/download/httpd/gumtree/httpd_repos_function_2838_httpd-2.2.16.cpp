static int dbd_sqlite3_prepare(apr_pool_t *pool, apr_dbd_t *sql,
                               const char *query, const char *label,
                               int nargs, int nvals, apr_dbd_type_e *types,
                               apr_dbd_prepared_t **statement)
{
    sqlite3_stmt *stmt;
    const char *tail = NULL;
    int ret;

    apr_dbd_mutex_lock();

    ret = sqlite3_prepare(sql->conn, query, strlen(query), &stmt, &tail);
    if (ret == SQLITE_OK) {
        apr_dbd_prepared_t *prep; 

        prep = apr_pcalloc(sql->pool, sizeof(*prep));
        prep->stmt = stmt;
        prep->next = sql->prep;
        prep->nargs = nargs;
        prep->nvals = nvals;
        prep->types = types;

        /* link new statement to the handle */
        sql->prep = prep;

        *statement = prep;
    } else {
        sqlite3_finalize(stmt);
    }
   
    apr_dbd_mutex_unlock();

    return ret;
}