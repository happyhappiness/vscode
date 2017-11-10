static apr_status_t dbd_oracle_datum_get(const apr_dbd_row_t *row, int n,
                                         apr_dbd_type_e type, void *data)
{
    define_arg *val = &row->res->statement->out[n];
    const char *entry;

    if ((n < 0) || (n >= row->res->statement->nout)) {
        return APR_EGENERAL;
    }

    if(val->ind == -1) {
        return APR_ENOENT;
    }

    switch (type) {
    case APR_DBD_TYPE_TINY:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(char*)data = atoi(entry);
        break;
    case APR_DBD_TYPE_UTINY:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(unsigned char*)data = atoi(entry);
        break;
    case APR_DBD_TYPE_SHORT:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(short*)data = atoi(entry);
        break;
    case APR_DBD_TYPE_USHORT:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(unsigned short*)data = atoi(entry);
        break;
    case APR_DBD_TYPE_INT:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(int*)data = atoi(entry);
        break;
    case APR_DBD_TYPE_UINT:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(unsigned int*)data = atoi(entry);
        break;
    case APR_DBD_TYPE_LONG:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(long*)data = atol(entry);
        break;
    case APR_DBD_TYPE_ULONG:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(unsigned long*)data = atol(entry);
        break;
    case APR_DBD_TYPE_LONGLONG:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(apr_int64_t*)data = apr_atoi64(entry);
        break;
    case APR_DBD_TYPE_ULONGLONG:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(apr_uint64_t*)data = apr_atoi64(entry);
        break;
    case APR_DBD_TYPE_FLOAT:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(float*)data = (float)atof(entry);
        break;
    case APR_DBD_TYPE_DOUBLE:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(double*)data = atof(entry);
        break;
    case APR_DBD_TYPE_STRING:
    case APR_DBD_TYPE_TEXT:
    case APR_DBD_TYPE_TIME:
    case APR_DBD_TYPE_DATE:
    case APR_DBD_TYPE_DATETIME:
    case APR_DBD_TYPE_TIMESTAMP:
    case APR_DBD_TYPE_ZTIMESTAMP:
        entry = dbd_oracle_get_entry(row, n);
        if (entry == NULL) {
            return APR_ENOENT;
        }
        *(char**)data = (char*)entry;
        break;
    case APR_DBD_TYPE_BLOB:
    case APR_DBD_TYPE_CLOB:
        {
        apr_bucket *e;
        apr_bucket_brigade *b = (apr_bucket_brigade*)data;
        apr_dbd_t *sql = row->res->handle;
        ub4 len = 0;

        switch (val->type) {
        case SQLT_BLOB:
        case SQLT_CLOB:
            sql->status = OCILobGetLength(sql->svc, sql->err,
                                          val->buf.lobval, &len);
            switch(sql->status) {
            case OCI_SUCCESS:
            case OCI_SUCCESS_WITH_INFO:
                if (len == 0) {
                    e = apr_bucket_eos_create(b->bucket_alloc);
                }
                else {
                    e = apr_bucket_lob_create(row, n, 0, len,
                                              row->pool, b->bucket_alloc);
                }
                break;
            default:
                return APR_ENOE