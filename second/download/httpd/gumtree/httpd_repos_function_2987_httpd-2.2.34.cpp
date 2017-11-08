static int dbd_pgsql_prepare(apr_pool_t *pool, apr_dbd_t *sql,
                             const char *query, const char *label,
                             int nargs, int nvals, apr_dbd_type_e *types,
                             apr_dbd_prepared_t **statement)
{
    char *sqlcmd;
    char *sqlptr;
    size_t length, qlen;
    int i = 0;
    const char **args;
    size_t alen;
    int ret;
    PGresult *res;

    if (!*statement) {
        *statement = apr_palloc(pool, sizeof(apr_dbd_prepared_t));
    }
    (*statement)->nargs = nargs;
    (*statement)->nvals = nvals;
    (*statement)->types = types;

    args = apr_palloc(pool, nargs * sizeof(*args));

    qlen = strlen(query);
    length = qlen + 1;

    for (i = 0; i < nargs; i++) {
        switch (types[i]) {
        case APR_DBD_TYPE_TINY: 
        case APR_DBD_TYPE_UTINY: 
        case APR_DBD_TYPE_SHORT: 
        case APR_DBD_TYPE_USHORT:
            args[i] = "smallint";
            break;
        case APR_DBD_TYPE_INT: 
        case APR_DBD_TYPE_UINT:
            args[i] = "integer";
            break;
        case APR_DBD_TYPE_LONG: 
        case APR_DBD_TYPE_ULONG:   
        case APR_DBD_TYPE_LONGLONG: 
        case APR_DBD_TYPE_ULONGLONG:
            args[i] = "bigint";
            break;
        case APR_DBD_TYPE_FLOAT:
            args[i] = "real";
            break;
        case APR_DBD_TYPE_DOUBLE:
            args[i] = "double precision";
            break;
        case APR_DBD_TYPE_TEXT:
            args[i] = "text";
            break;
        case APR_DBD_TYPE_TIME:
            args[i] = "time";
            break;
        case APR_DBD_TYPE_DATE:
            args[i] = "date";
            break;
        case APR_DBD_TYPE_DATETIME:
        case APR_DBD_TYPE_TIMESTAMP:
            args[i] = "timestamp";
            break;
        case APR_DBD_TYPE_ZTIMESTAMP:
            args[i] = "timestamp with time zone";
            break;
        case APR_DBD_TYPE_BLOB:
        case APR_DBD_TYPE_CLOB:
            args[i] = "bytea";
            break;
        case APR_DBD_TYPE_NULL:
            args[i] = "varchar"; /* XXX Eh? */
            break;
        default:
            args[i] = "varchar";
            break;
        }
        length += 1 + strlen(args[i]);
    }

    if (!label) {
        /* don't really prepare; use in execParams instead */
        (*statement)->prepared = 0;
        (*statement)->name = apr_pstrdup(pool, query);
        return 0;
    }
    (*statement)->name = apr_pstrdup(pool, label);

    /* length of SQL query that prepares this statement */
    length = 8 + strlen(label) + 2 + 4 + length + 1;
    sqlcmd = apr_palloc(pool, length);
    sqlptr = sqlcmd;
    memcpy(sqlptr, "PREPARE ", 8);
    sqlptr += 8;
    length = strlen(label);
    memcpy(sqlptr, label, length);
    sqlptr += length;
    if (nargs > 0) {
        memcpy(sqlptr, " (",2);
        sqlptr += 2;
        for (i=0; i < nargs; ++i) {
            alen = strlen(args[i]);
            memcpy(sqlptr, args[i], alen);
            sqlptr += alen;
            *sqlptr++ = ',';
        }
        sqlptr[-1] =  ')';
    }
    memcpy(sqlptr, " AS ", 4);
    sqlptr += 4;
    memcpy(sqlptr, query, qlen);
    sqlptr += qlen;
    *sqlptr = 0;

    res = PQexec(sql->conn, sqlcmd);
    if ( res ) {
        ret = PQresultStatus(res);
        if (dbd_pgsql_is_success(ret)) {
            ret = 0;
        }
        /* Hmmm, do we do this here or register it on the pool? */
        PQclear(res);
    }
    else {
        ret = PGRES_FATAL_ERROR;
    }
    (*statement)->prepared = 1;

    return ret;
}