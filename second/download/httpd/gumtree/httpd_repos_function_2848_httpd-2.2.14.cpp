static int dbd_oracle_query(apr_dbd_t *sql, int *nrows, const char *query)
{
    int ret = 0;
    apr_pool_t *pool;
    apr_dbd_prepared_t *statement = NULL;

    if (sql->trans && sql->trans->status == TRANS_ERROR) {
        return 1;
    }

    /* make our own pool so that APR allocations don't linger and so that
     * both Stmt and LOB handles are cleaned up (LOB handles may be
     * allocated when preparing APR_DBD_TYPE_CLOB/BLOBs)
     */
    apr_pool_create(&pool, sql->pool);

    ret = dbd_oracle_prepare(pool, sql, query, NULL, 0, 0, NULL, &statement);
    if (ret == 0) {
        ret = dbd_oracle_pquery(pool, sql, nrows, statement, NULL);
        if (ret == 0) {
            sql->status = OCIAttrGet(statement->stmt, OCI_HTYPE_STMT,
                                     nrows, 0, OCI_ATTR_ROW_COUNT,
                                     sql->err);
        }
    }

    apr_pool_destroy(pool);

    return ret;
}