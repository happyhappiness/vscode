static int dbd_oracle_num_tuples(apr_dbd_results_t* res)
{
    if (!res->seek) {
        return -1;
    }
    if (res->nrows >= 0) {
        return res->nrows;
    }
    res->handle->status = OCIAttrGet(res->statement->stmt, OCI_HTYPE_STMT,
                                     &res->nrows, 0, OCI_ATTR_ROW_COUNT,
                                     res->handle->err);
    return res->nrows;
}