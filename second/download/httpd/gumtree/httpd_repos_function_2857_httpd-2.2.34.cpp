static apr_status_t odbc_datum_get(const apr_dbd_row_t *row, int col,
                                   apr_dbd_type_e dbdtype, void *data)
{
    SQLSMALLINT sqltype;
    void *p;
    int len;

    if (col >= row->res->ncols)
        return APR_EGENERAL;

    if (dbdtype < 0 || dbdtype >= NUM_APR_DBD_TYPES) {
        data = NULL;            /* invalid type */
        return APR_EGENERAL;
    }

    len = sqlSizes[dbdtype];
    sqltype = sqlCtype[dbdtype];

    /* must not memcpy a brigade, sentinals are relative to orig loc */
    if (IS_LOB(sqltype)) 
        return odbc_create_bucket(row, col, sqltype, data);

    p = odbc_get(row, col, sqltype);
    if (p == (void *)-1)
        return APR_EGENERAL;

    if (p == NULL)
        return APR_ENOENT;          /* SQL NULL value */
    
    if (len < 0)
       *(char**)data = (char *)p;
    else
        memcpy(data, p, len);
    
    return APR_SUCCESS;

}