static apr_status_t odbc_lob_bucket_read(apr_bucket *e, const char **str,
                                         apr_size_t *len, apr_read_type_e block)
{
    SQLRETURN rc;
    SQLLEN len_indicator;
    SQLSMALLINT type;
    odbc_bucket *bd = (odbc_bucket *)e->data;
    apr_bucket *nxt;
    void *buf;
    int bufsize = bd->row->res->apr_dbd->defaultBufferSize;
    int eos;
    
    /* C type is CHAR for CLOBs, DEFAULT for BLOBs */
    type = bd->row->res->coltypes[bd->col];
    type = (type == SQL_LONGVARCHAR) ? SQL_C_CHAR : SQL_C_DEFAULT;

    /* LOB buffers are always at least APR_BUCKET_BUFF_SIZE, 
     *   but they may be much bigger per the BUFSIZE parameter.
     */
    if (bufsize < APR_BUCKET_BUFF_SIZE)
        bufsize = APR_BUCKET_BUFF_SIZE;

    buf = apr_bucket_alloc(bufsize, e->list);
    *str = NULL;
    *len = 0;

    rc = SQLGetData(bd->row->res->stmt, bd->col + 1, 
                    type, buf, bufsize, 
                    &len_indicator);

    CHECK_ERROR(bd->row->res->apr_dbd, "SQLGetData", rc, 
                SQL_HANDLE_STMT, bd->row->res->stmt);
    
    if (rc == SQL_NO_DATA || len_indicator == SQL_NULL_DATA || len_indicator < 0)
        len_indicator = 0;

    if (SQL_SUCCEEDED(rc) || rc == SQL_NO_DATA) {

        if (rc == SQL_SUCCESS_WITH_INFO
            && (len_indicator == SQL_NO_TOTAL || len_indicator >= bufsize)) {
            /* not the last read = a full buffer. CLOBs have a null terminator */
            *len = bufsize - (IS_CLOB(bd->type) ? 1 : 0 );

             eos = 0;
        }
        else {
            /* the last read - len_indicator is supposed to be the length, 
             * but some driver get this wrong and return the total length.
             * We try to handle both interpretations.
             */
            *len =  (len_indicator > bufsize 
                     && len_indicator >= (SQLLEN)e->start)
                ? (len_indicator - (SQLLEN)e->start) : len_indicator;

            eos = 1;
        }

        if (!eos) {
            /* Create a new LOB bucket to append and append it */
            nxt = apr_bucket_alloc(sizeof(apr_bucket *), e->list);
            APR_BUCKET_INIT(nxt);
            nxt->length = -1;
            nxt->data   = e->data;
            nxt->type   = &odbc_bucket_type;
            nxt->free   = apr_bucket_free;
            nxt->list   = e->list;
            nxt->start  = e->start + *len;
            APR_BUCKET_INSERT_AFTER(e, nxt);
        }
        else {
            odbc_lob_bucket_destroy(e->data);
        }
        /* make current bucket into a heap bucket */
        apr_bucket_heap_make(e, buf, *len, apr_bucket_free);
        *str = buf;

        /* No data is success in this context */
        rc = SQL_SUCCESS;
    }
    return APR_FROM_SQL_RESULT(rc);
}