static int dbd_oracle_prepare(apr_pool_t *pool, apr_dbd_t *sql,
                              const char *query, const char *label,
                              int nargs, int nvals, apr_dbd_type_e *types,
                              apr_dbd_prepared_t **statement)
{
    int ret = 0;
    int i;
    apr_dbd_prepared_t *stmt ;

    if (*statement == NULL) {
        *statement = apr_pcalloc(pool, sizeof(apr_dbd_prepared_t));
    }
    stmt = *statement;
    stmt->handle = sql;
    stmt->pool = pool;
    stmt->nargs = nargs;
    stmt->nvals = nvals;

    /* populate our own args, if any */
    if (nargs > 0) {
        stmt->args = apr_pcalloc(pool, nargs*sizeof(bind_arg));
        for (i = 0; i < nargs; i++) {
            stmt->args[i].type = types[i];
        }
    }

    sql->status = OCIHandleAlloc(dbd_oracle_env, (dvoid**) &stmt->stmt,
                                 OCI_HTYPE_STMT, 0, NULL);
    if (sql->status != OCI_SUCCESS) {
        return 1;
    }

    sql->status = OCIStmtPrepare(stmt->stmt, sql->err, (text*) query,
                                 strlen(query), OCI_NTV_SYNTAX, OCI_DEFAULT);
    if (sql->status != OCI_SUCCESS) {
        OCIHandleFree(stmt->stmt, OCI_HTYPE_STMT);
        return 1;
    }

    apr_pool_cleanup_register(pool, stmt, freeStatement,
                              apr_pool_cleanup_null);

    /* Perl gets statement type here */
    sql->status = OCIAttrGet(stmt->stmt, OCI_HTYPE_STMT, &stmt->type, 0,
                             OCI_ATTR_STMT_TYPE, sql->err);
    if (sql->status != OCI_SUCCESS) {
        return 1;
    }

/* Perl sets PREFETCH_MEMORY here, but the docs say there's a working default */
#if 0
    sql->status = OCIAttrSet(stmt->stmt, OCI_HTYPE_STMT, &prefetch_size,
                             sizeof(prefetch_size), OCI_ATTR_PREFETCH_MEMORY,
                             sql->err);
    if (sql->status != OCI_SUCCESS) {
        return 1;
    }
#endif

    if (stmt->type == OCI_STMT_SELECT) {
        ret = outputParams(sql, stmt);
    }
    return ret;
}