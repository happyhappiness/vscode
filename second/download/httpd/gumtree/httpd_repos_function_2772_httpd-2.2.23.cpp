static int dbd_freetds_prepare(apr_pool_t *pool, apr_dbd_t *sql,
                             const char *query, const char *label,
                             int nargs, int nvals, apr_dbd_type_e *types,
                             apr_dbd_prepared_t **statement)
{
    apr_dbd_prepared_t *stmt;

    if (label == NULL) {
        label = apr_psprintf(pool, "%d", labelnum++);
    }

    if (!*statement) {
        *statement = apr_palloc(pool, sizeof(apr_dbd_prepared_t));
    }
    stmt = *statement;

#if 0
    /* count args */
    stmt->fmt = apr_pstrdup(pool, query);
    stmt->fmt = recurse_args(pool, 0, query, stmt, stmt->fmt);

    /* overestimate by a byte or two to simplify */
    len = strlen("CREATE PROC apr.")
            + strlen(label)
            + stmt->nargs * strlen(" @arg1 varchar(len1),")
            + strlen(" AS begin ")
            + strlen(stmt->fmt)
            + strlen(" end "); /* extra byte for terminator */

    pquery = apr_pcalloc(pool, len);
    sprintf(pquery, "CREATE PROC apr.%s", label);
    for (i=0; i<stmt->nargs; ++i) {
        sprintf(pquery+strlen(pquery), " @arg%d varchar(%d)", i, stmt->sz[i]);
        if (i < stmt->nargs-1) {
            pquery[strlen(pquery)] = ',';
        }
    }
    strcat(pquery, " AS BEGIN ");
    strcat(pquery, stmt->fmt);
    strcat(pquery, " END");

    return (freetds_exec(sql->proc, pquery, 0, &i) == SUCCEED) ? 0 : 1;
#else
    stmt->fmt = apr_pstrdup(pool, query);
    return recurse_args(pool, 0, query, stmt, 0);
#endif

}