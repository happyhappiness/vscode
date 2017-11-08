static int dbd_sqlite3_prepare(apr_pool_t *pool, apr_dbd_t *sql,
                               const char *query, const char *label,
                               apr_dbd_prepared_t **statement)
{
    sqlite3_stmt *stmt;
    char *p, *slquery = apr_pstrdup(pool, query);
    const char *tail = NULL, *q;
    int ret;

    for (p = slquery, q = query; *q; ++q) {
        if (q[0] == '%') {
            if (isalpha(q[1])) {
                *p++ = '?';
                ++q;
            }
            else if (q[1] == '%') {
                /* reduce %% to % */
                *p++ = *q++;
            }
            else {
                *p++ = *q;
            }
        }
        else {
            *p++ = *q;
        }
    }
    *p = 0;

#if APR_HAS_THREADS
    apr_thread_mutex_lock(sql->mutex);
#endif

    ret = sqlite3_prepare(sql->conn, slquery, strlen(query), &stmt, &tail);
    if (ret == SQLITE_OK) {
        apr_dbd_prepared_t *prep; 

        prep = apr_pcalloc(sql->pool, sizeof(*prep));
        prep->stmt = stmt;
        prep->next = sql->prep;

        /* link new statement to the handle */
        sql->prep = prep;

        *statement = prep;
    } else {
        sqlite3_finalize(stmt);
    }
   
#if APR_HAS_THREADS
    apr_thread_mutex_unlock(sql->mutex);
#endif

    return ret;
}