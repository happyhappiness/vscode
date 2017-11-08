static int outputParams(apr_dbd_t *sql, apr_dbd_prepared_t *stmt)
{
    OCIParam *parms;
    int i;
    ub2 paramtype[DBD_ORACLE_MAX_COLUMNS];
    ub2 paramsize[DBD_ORACLE_MAX_COLUMNS];
    char *paramname[DBD_ORACLE_MAX_COLUMNS];
    ub4 paramnamelen[DBD_ORACLE_MAX_COLUMNS];
    int_errorcode;

    /* Perl uses 0 where we used 1 */
    sql->status = OCIStmtExecute(sql->svc, stmt->stmt, sql->err, 0, 0,
                                 NULL, NULL, OCI_DESCRIBE_ONLY);
    switch (sql->status) {
    case OCI_SUCCESS:
    case OCI_SUCCESS_WITH_INFO:
        break;
    case OCI_ERROR:
#ifdef DEBUG
        OCIErrorGet(sql->err, 1, NULL, &errorcode,
                    sql->buf, sizeof(sql->buf), OCI_HTYPE_ERROR);
        printf("Describing prepared statement: %s\n", sql->buf);
#endif
    default:
        return 1;
    }
    while (sql->status == OCI_SUCCESS) {
        sql->status = OCIParamGet(stmt->stmt, OCI_HTYPE_STMT,
                                  sql->err, (dvoid**)&parms, stmt->nout+1);
        switch (sql->status) {
        case OCI_SUCCESS:
            sql->status = OCIAttrGet(parms, OCI_DTYPE_PARAM,
                                     &paramtype[stmt->nout],
                                     0, OCI_ATTR_DATA_TYPE, sql->err);
            sql->status = OCIAttrGet(parms, OCI_DTYPE_PARAM,
                                     &paramsize[stmt->nout],
                                     0, OCI_ATTR_DATA_SIZE, sql->err);
            sql->status = OCIAttrGet(parms, OCI_DTYPE_PARAM,
                                     &paramname[stmt->nout],
                                     &paramnamelen[stmt->nout],
                                     OCI_ATTR_NAME, sql->err);
            ++stmt->nout;
        }
    }
    switch (sql->status) {
    case OCI_SUCCESS:
        break;
    case OCI_ERROR:
        break;        /* this is what we expect at end-of-loop */
    default:
        return 1;
    }

    /* OK, the above works.  We have the params; now OCIDefine them */
    stmt->out = apr_palloc(stmt->pool, stmt->nout*sizeof(define_arg));
    for (i=0; i<stmt->nout; ++i) {
        stmt->out[i].type = paramtype[i];
        stmt->out[i].len = stmt->out[i].sz = paramsize[i];
        stmt->out[i].name = apr_pstrmemdup(stmt->pool,
                                           paramname[i], paramnamelen[i]);
        switch (stmt->out[i].type) {
        default:
            switch (stmt->out[i].type) {
            case SQLT_NUM:           /* 2: numeric, Perl worst case=130+38+3 */
                stmt->out[i].sz = 171;
                break;
            case SQLT_CHR:           /* 1: char */
            case SQLT_AFC:           /* 96: ANSI fixed char */
                stmt->out[i].sz *= 4; /* ugh, wasteful UCS-4 handling */
                break;
            case SQLT_DAT:           /* 12: date, depends on NLS date format */
                stmt->out[i].sz = 75;
                break;
            case SQLT_BIN:           /* 23: raw binary, perhaps UTF-16? */
                stmt->out[i].sz *= 2;
                break;
            case SQLT_RID:           /* 11: rowid */
            case SQLT_RDD:           /* 104: rowid descriptor */
                stmt->out[i].sz = 20;
                break;
            case SQLT_TIMESTAMP:     /* 187: timestamp */
            case SQLT_TIMESTAMP_TZ:  /* 188: timestamp with time zone */
            case SQLT_INTERVAL_YM:   /* 189: interval year-to-month */
            case SQLT_INTERVAL_DS:   /* 190: interval day-to-second */
            case SQLT_TIMESTAMP_LTZ: /* 232: timestamp with local time zone */
                stmt->out[i].sz = 75;
                break;
            default:
#ifdef DEBUG
                printf("Unsupported data type: %d\n", stmt->out[i].type);
#endif
                break;
            }
            ++stmt->out[i].sz;
            stmt->out[i].buf.raw = apr_palloc(stmt->pool, stmt->out[i].sz);
            sql->status = OCIDefineByPos(stmt->stmt, &stmt->out[i].defn,
                                         sql->err, i+1,
                                         stmt->out[i].buf.sval,
                                         stmt->out[i].sz, SQLT_STR,
                                         &stmt->out[i].ind, &stmt->out[i].len,
                                         0, OCI_DEFAULT);
            break;
        case SQLT_LNG: /* 8: long */
            stmt->out[i].sz = sql->long_size * 4 + 4; /* ugh, UCS-4 handling */
            stmt->out[i].buf.raw = apr_palloc(stmt->pool, stmt->out[i].sz);
            sql->status = OCIDefineByPos(stmt->stmt, &stmt->out[i].defn,
                                         sql->err, i+1,
                                         stmt->out[i].buf.raw,
                                         stmt->out[i].sz, SQLT_LVC,
                                         &stmt->out[i].ind, NULL,
                                         0, OCI_DEFAULT);
            break;
        case SQLT_LBI: /* 24: long binary, perhaps UTF-16? */
            stmt->out[i].sz = sql->long_size * 2 + 4; /* room for int prefix */
            stmt->out[i].buf.raw = apr_palloc(stmt->pool, stmt->out[i].sz);
            sql->status = OCIDefineByPos(stmt->stmt, &stmt->out[i].defn,
                                         sql->err, i+1,
                                         stmt->out[i].buf.raw,
                                         stmt->out[i].sz, SQLT_LVB,
                                         &stmt->out[i].ind, NULL,
                                         0, OCI_DEFAULT);
            break;
        case SQLT_BLOB: /* 113 */
        case SQLT_CLOB: /* 112 */
/*http://download-west.oracle.com/docs/cd/B10501_01/appdev.920/a96584/oci05bnd.htm#434937*/
            sql->status = OCIDescriptorAlloc(dbd_oracle_env,
                                             (dvoid**)&stmt->out[i].buf.lobval,
                                             OCI_DTYPE_LOB, 0, NULL);
            apr_pool_cleanup_register(stmt->pool, stmt->out[i].buf.lobval,
                                      dbd_free_lobdesc,
                                      apr_pool_cleanup_null);
            sql->status = OCIDefineByPos(stmt->stmt, &stmt->out[i].defn,
                                         sql->err, i+1,
                                         (dvoid*) &stmt->out[i].buf.lobval,
                                         -1, stmt->out[i].type,
                                         &stmt->out[i].ind, &stmt->out[i].len,
                                         0, OCI_DEFAULT);
            break;
        }
        switch (sql->status) {
        case OCI_SUCCESS:
            break;
        default:
            return 1;
        }
    }
    return 0;
}