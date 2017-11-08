static int dbd_oracle_get_row(apr_pool_t *pool, apr_dbd_results_t *res,
                              apr_dbd_row_t **rowp, int rownum)
{
    apr_dbd_row_t *row = *rowp;
    apr_dbd_t *sql = res->handle;
    int_errorcode;

    if (row == NULL) {
        row = apr_palloc(pool, sizeof(apr_dbd_row_t));
        *rowp = row;
        row->res = res;
        /* Oracle starts counting at 1 according to the docs */
        row->n = res->seek ? rownum : 1;
        row->pool = pool;
    }
    else {
        if (res->seek) {
            row->n = rownum;
        }
        else {
            ++row->n;
        }
    }

    if (res->seek) {
        sql->status = OCIStmtFetch2(res->statement->stmt, res->handle->err, 1,
                                    OCI_FETCH_ABSOLUTE, row->n, OCI_DEFAULT);
    }
    else {
        sql->status = OCIStmtFetch2(res->statement->stmt, res->handle->err, 1,
                                    OCI_FETCH_NEXT, 0, OCI_DEFAULT);
    }
    switch (sql->status) {
    case OCI_SUCCESS:
        (*rowp)->res = res;
        return 0;
    case OCI_NO_DATA:
        return -1;
    case OCI_ERROR:
#ifdef DEBUG
        OCIErrorGet(sql->err, 1, NULL, &errorcode,
                    sql->buf, sizeof(sql->buf), OCI_HTYPE_ERROR);
        printf("Execute error %d: %s\n", sql->status, sql->buf);
#endif
        /* fallthrough */
    default:
        return 1;
    }
    return 0;
}