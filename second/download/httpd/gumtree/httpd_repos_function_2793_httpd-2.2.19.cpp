static SQLRETURN odbc_set_result_column(int icol, apr_dbd_results_t *res, 
                                        SQLHANDLE stmt)
{
    SQLRETURN rc;
    int maxsize, textsize, realsize, type, isunsigned = 1;

    /* discover the sql type */
    rc = SQLColAttribute(stmt, icol + 1, SQL_DESC_UNSIGNED, NULL, 0, NULL,
                         (SQLPOINTER)&isunsigned);
    isunsigned = (isunsigned == SQL_TRUE);

    rc = SQLColAttribute(stmt, icol + 1, SQL_DESC_TYPE, NULL, 0, NULL,
                         (SQLPOINTER)&type);
    if (!SQL_SUCCEEDED(rc) || type == SQL_UNKNOWN_TYPE) {
        /* MANY ODBC v2 datasources only supply CONCISE_TYPE */
        rc = SQLColAttribute(stmt, icol + 1, SQL_DESC_CONCISE_TYPE, NULL,
                             0, NULL, (SQLPOINTER)&type);
    }

    if (!SQL_SUCCEEDED(rc)) {
        /* if still unknown make it CHAR */
        type = SQL_C_CHAR;
    }

    switch (type) {
    case SQL_INTEGER:
    case SQL_SMALLINT:
    case SQL_TINYINT:
    case SQL_BIGINT:
      /* fix these numeric binary types up as signed/unsigned for C types */
      type += (isunsigned) ? SQL_UNSIGNED_OFFSET : SQL_SIGNED_OFFSET;
      break;
    /* LOB types are not changed to C types */
    case SQL_LONGVARCHAR: 
        type = SQL_LONGVARCHAR; 
        break;
    case SQL_LONGVARBINARY: 
        type = SQL_LONGVARBINARY; 
        break;
    case SQL_FLOAT : 
        type = SQL_C_FLOAT; 
        break;
    case SQL_DOUBLE : 
        type = SQL_C_DOUBLE; 
        break;

    /* DBD wants times as strings */
    case SQL_TIMESTAMP:      
    case SQL_DATE:
    case SQL_TIME:
    default:
      type = SQL_C_CHAR;
    }

    res->coltypes[icol] = type;

    /* size if retrieved as text */
    rc = SQLColAttribute(stmt, icol + 1, SQL_DESC_DISPLAY_SIZE, NULL, 0,
                         NULL, (SQLPOINTER)&textsize);
    if (!SQL_SUCCEEDED(rc) || textsize < 0) {
        textsize = res->apr_dbd->defaultBufferSize;
    }
    /* for null-term, which sometimes isn't included */
    textsize++;

    /* real size */
    rc = SQLColAttribute(stmt, icol + 1, SQL_DESC_OCTET_LENGTH, NULL, 0,
                         NULL, (SQLPOINTER)&realsize);
    if (!SQL_SUCCEEDED(rc)) {
        realsize = textsize;
    }

    maxsize = (textsize > realsize) ? textsize : realsize;
    if (IS_LOB(type) || maxsize <= 0) {
        /* LOB types are never bound and have a NULL colptr for binary.
         * Ingore their real (1-2gb) length & use a default - the larger
         * of defaultBufferSize or APR_BUCKET_BUFF_SIZE.
         * If not a LOB, but simply unknown length - always use defaultBufferSize.
         */
        maxsize = res->apr_dbd->defaultBufferSize;
        if (IS_LOB(type) && maxsize < APR_BUCKET_BUFF_SIZE) {
            maxsize = APR_BUCKET_BUFF_SIZE;
        }

        res->colptrs[icol] =  NULL;
        res->colstate[icol] = COL_AVAIL;
        res->colsizes[icol] = maxsize;
        rc = SQL_SUCCESS;
    }
    else {
        res->colptrs[icol] = apr_pcalloc(res->pool, maxsize);
        res->colsizes[icol] = maxsize;
        if (res->apr_dbd->dboptions & SQL_GD_BOUND) {
            /* we are allowed to call SQLGetData if we need to */
            rc = SQLBindCol(stmt, icol + 1, res->coltypes[icol], 
                            res->colptrs[icol], maxsize, 
                            &(res->colinds[icol]));
            CHECK_ERROR(res->apr_dbd, "SQLBindCol", rc, SQL_HANDLE_STMT,
                        stmt);
            res->colstate[icol] = SQL_SUCCEEDED(rc) ? COL_BOUND : COL_AVAIL;
        }
        else {
            /* this driver won't allow us to call SQLGetData on bound 
             * columns - so don't bind any
             */
            res->colstate[icol] = COL_AVAIL;
            rc = SQL_SUCCESS;
        }
    }
    return rc;
}