static const char *odbc_get_entry(const apr_dbd_row_t *row, int col)
{
    void *p;

    if (col >= row->res->ncols)
        return NULL;

    p = odbc_get(row, col, SQL_C_CHAR);

    /* NULL or invalid (-1) */
    if (p == NULL || p == (void *)-1)
        return p;     
    else
        return apr_pstrdup(row->pool, p);   
}