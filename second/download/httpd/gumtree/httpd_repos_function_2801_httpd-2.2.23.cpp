static SQLRETURN odbc_bind_param(apr_pool_t *pool,
                                 apr_dbd_prepared_t *statement, const int narg,
                                 const SQLSMALLINT type, int *argp,
                                 const void **args, const int textmode)
{
    SQLRETURN rc;
    SQLSMALLINT baseType, cType;
    void *ptr;
    SQLULEN len;
    SQLLEN *indicator;
    static SQLLEN nullValue = SQL_NULL_DATA;
    static SQLSMALLINT inOut = SQL_PARAM_INPUT;     /* only input params */

    /* bind a NULL data value */
    if (args[*argp] == NULL || type == APR_DBD_TYPE_NULL) {
        baseType = SQL_CHAR;
        cType = SQL_C_CHAR;
        ptr = &nullValue;
        len = sizeof(SQLINTEGER);
        indicator = &nullValue;
        (*argp)++;
    }
    /* bind a non-NULL data value */
    else {
        if (type < 0 || type >= NUM_APR_DBD_TYPES) {
            return APR_EGENERAL;
        }

        baseType = sqlBaseType[type];
        cType = sqlCtype[type];
        indicator = NULL;
        /* LOBs */
        if (IS_LOB(cType)) {
            ptr = (void *)args[*argp];
            len = (SQLULEN) * (apr_size_t *)args[*argp + 1];
            cType = (IS_CLOB(cType)) ? SQL_C_CHAR : SQL_C_DEFAULT;
            (*argp) += 4;  /* LOBs consume 4 args (last two are unused) */
        }
        /* non-LOBs */
        else {
            switch (baseType) {
            case SQL_CHAR:
            case SQL_DATE:
            case SQL_TIME:
            case SQL_TIMESTAMP:
                ptr = (void *)args[*argp];
                len = (SQLULEN)strlen(ptr);
                break;
            case SQL_TINYINT:
                ptr = apr_palloc(pool, sizeof(unsigned char));
                len = sizeof(unsigned char);
                *(unsigned char *)ptr =
                    (textmode ?
                     atoi(args[*argp]) : *(unsigned char *)args[*argp]);
                break;
            case SQL_SMALLINT:
                ptr = apr_palloc(pool, sizeof(short));
                len = sizeof(short);
                *(short *)ptr =
                    (textmode ? atoi(args[*argp]) : *(short *)args[*argp]);
                break;
            case SQL_INTEGER:
                ptr = apr_palloc(pool, sizeof(int));
                len = sizeof(int);
                *(long *)ptr =
                    (textmode ? atol(args[*argp]) : *(long *)args[*argp]);
                break;
            case SQL_FLOAT:
                ptr = apr_palloc(pool, sizeof(float));
                len = sizeof(float);
                *(float *)ptr =
                    (textmode ?
                     (float)atof(args[*argp]) : *(float *)args[*argp]);
                break;
            case SQL_DOUBLE:
                ptr = apr_palloc(pool, sizeof(double));
                len = sizeof(double);
                *(double *)ptr =
                    (textmode ? atof(args[*argp]) : *(double *)
                     args[*argp]);
                break;
            case SQL_BIGINT:
                ptr = apr_palloc(pool, sizeof(apr_int64_t));
                len = sizeof(apr_int64_t);
                *(apr_int64_t *)ptr =
                    (textmode ?
                     apr_atoi64(args[*argp]) : *(apr_int64_t *)args[*argp]);
                break;
            default:
                return APR_EGENERAL;
            }
            (*argp)++;          /* non LOBs consume one argument */
        }
    }
    rc = SQLBindParameter(statement->stmt, narg, inOut, cType, 
                          baseType, len, 0, ptr, len, indicator);
    CHECK_ERROR(statement->apr_dbd, "SQLBindParameter", rc, SQL_HANDLE_STMT,
                statement->stmt);
    return rc;
}