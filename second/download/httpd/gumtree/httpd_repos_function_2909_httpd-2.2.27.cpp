static const char *dbd_oracle_get_entry(const apr_dbd_row_t *row, int n)
{
    ub4 len = 0;
    ub1 csform = 0;
    ub2 csid = 0;
    apr_size_t buflen = 0;
    char *buf = NULL;
    define_arg *val = &row->res->statement->out[n];
    apr_dbd_t *sql = row->res->handle;
    int_errorcode;

    if ((n < 0) || (n >= row->res->statement->nout) || (val->ind == -1)) {
        return NULL;
    }

    switch (val->type) {
    case SQLT_BLOB:
    case SQLT_CLOB:
        sql->status = OCILobGetLength(sql->svc, sql->err, val->buf.lobval,
                                      &len);
        switch (sql->status) {
        case OCI_SUCCESS:
        case OCI_SUCCESS_WITH_INFO:
            if (len == 0) {
                buf = "";
            }
            break;
        case OCI_ERROR:
#ifdef DEBUG
            OCIErrorGet(sql->err, 1, NULL, &errorcode,
                        sql->buf, sizeof(sql->buf), OCI_HTYPE_ERROR);
            printf("Finding LOB length: %s\n", sql->buf);
            break;
#endif
        default:
            break;
        }

        if (len == 0) {
            break;
        }

        if (val->type == APR_DBD_TYPE_CLOB) {
#if 1
            /* Is this necessary, or can it be defaulted? */
            sql->status = OCILobCharSetForm(dbd_oracle_env, sql->err,
                                            val->buf.lobval, &csform);
            if (sql->status == OCI_SUCCESS) {
                sql->status = OCILobCharSetId(dbd_oracle_env, sql->err,
                                              val->buf.lobval, &csid);
            }
            switch (sql->status) {
            case OCI_SUCCESS:
            case OCI_SUCCESS_WITH_INFO:
                buflen = (len+1) * 4; /* ugh, wasteful UCS-4 handling */
                /* zeroise all - where the string ends depends on charset */
                buf = apr_pcalloc(row->pool, buflen);
                break;
#ifdef DEBUG
            case OCI_ERROR:
                OCIErrorGet(sql->err, 1, NULL, &errorcode,
                            sql->buf, sizeof(sql->buf), OCI_HTYPE_ERROR);
                printf("Reading LOB character set: %s\n", sql->buf);
                break; /*** XXX?? ***/
#endif
            default:
                break; /*** XXX?? ***/
            }
#else   /* ignore charset */
            buflen = (len+1) * 4; /* ugh, wasteful UCS-4 handling */
            /* zeroise all - where the string ends depends on charset */
            buf = apr_pcalloc(row->pool, buflen);
#endif
        } else {
            /* BUG: this'll only work if the BLOB looks like a string */
            buflen = len;
            buf = apr_palloc(row->pool, buflen+1);
            buf[buflen] = 0;
        }

        if (!buf) {
            break;
        }

        sql->status = OCILobRead(sql->svc, sql->err, val->buf.lobval,
                                 &len, 1, (dvoid*) buf, buflen,
                                 NULL, NULL, csid, csform);
        switch (sql->status) {
        case OCI_SUCCESS:
        case OCI_SUCCESS_WITH_INFO:
            break;
#ifdef DEBUG
        case OCI_ERROR:
            OCIErrorGet(sql->err, 1, NULL, &errorcode,
                        sql->buf, sizeof(sql->buf), OCI_HTYPE_ERROR);
            printf("Reading LOB: %s\n", sql->buf);
            buf = NULL; /*** XXX?? ***/
            break;
#endif
        default:
            buf = NULL; /*** XXX?? ***/
            break;
        }

        break;
    case SQLT_LNG:
    case SQLT_LBI:
        /* raw is struct { ub4 len; char *buf; } */
        len = *(ub4*) val->buf.raw;
        buf = apr_pstrndup(row->pool, val->buf.sval + sizeof(ub4), len);
        break;
    default:
        buf = apr_pstrndup(row->pool, val->buf.sval, val->len);
        break;
    }
    return (const char*) buf;
}