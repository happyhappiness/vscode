static int dbd_freetds_select(apr_pool_t *pool, apr_dbd_t *sql,
                              apr_dbd_results_t **results,
                              const char *query, int seek)
{
    apr_dbd_results_t *res;
    if (sql->trans && (sql->trans->errnum != SUCCEED)) {
        return 1;
    }
    /* the core of this is
     * dbcmd(proc, query);
     * dbsqlexec(proc);
     * while (dbnextrow(dbproc) != NO_MORE_ROWS) {
     *     do things
     * }
     *
     * Ignore seek
     */

    sql->err = freetds_exec(sql->proc, query, 1, NULL);
    if (!dbd_freetds_is_success(sql->err)) {
        if (sql->trans) {
            sql->trans->errnum = sql->err;
        }
        return 1;
    }

    sql->err = dbresults(sql->proc);
    if (sql->err != SUCCEED) {
        if (sql->trans) {
            sql->trans->errnum = sql->err;
        }
        return 1;
    }

    if (!*results) {
        *results = apr_pcalloc(pool, sizeof(apr_dbd_results_t));
    }
    res = *results;
    res->proc = sql->proc;
    res->random = seek;
    res->pool = pool;
    res->ntuples = dblastrow(sql->proc);
    res->sz = dbnumcols(sql->proc);
    apr_pool_cleanup_register(pool, sql->proc, clear_result,
                              apr_pool_cleanup_null);

#if 0
    /* Now we have a result set.  We need to bind to its vars */
    res->vars = apr_palloc(pool, res->sz * sizeof(freetds_cell_t*));
    for (i=1; i <= res->sz; ++i) {
        freetds_cell_t *cell = &res->vars[i-1];
        cell->type = dbcoltype(sql->proc, i);
        cell->len = dbcollen(sql->proc, i);
        cell->data = apr_palloc(pool, cell->len);
        sql->err = dbbind(sql->proc, i, /*cell->type */ STRINGBIND, cell->len, cell->data);
        if (sql->err != SUCCEED) {
            fprintf(stderr, "dbbind error: %d, %d, %d", i, cell->type, cell->len);
        }
        if ((sql->err != SUCCEED) && (sql->trans != NULL)) {
            sql->trans->errnum = sql->err;
        }
    }
#endif
    return (sql->err == SUCCEED) ? 0 : 1;
}