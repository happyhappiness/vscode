static int dbd_oracle_pquery(apr_pool_t *pool, apr_dbd_t *sql,
                             int *nrows, apr_dbd_prepared_t *statement,
                             const char **values)
{
    OCISnapshot *oldsnapshot = NULL;
    OCISnapshot *newsnapshot = NULL;
    apr_dbd_transaction_t* trans = sql->trans;
    int exec_mode;
    int_errorcode;

    if (trans) {
        switch (trans->status) {
        case TRANS_ERROR:
            return -1;
        case TRANS_NONE:
            trans = NULL;
            break;
        case TRANS_1:
            oldsnapshot = trans->snapshot1;
            newsnapshot = trans->snapshot2;
            trans->status = TRANS_2;
            break;
        case TRANS_2:
            oldsnapshot = trans->snapshot2;
            newsnapshot = trans->snapshot1;
            trans->status = TRANS_1;
            break;
        }
        exec_mode = OCI_DEFAULT;
    }
    else {
        exec_mode = OCI_COMMIT_ON_SUCCESS;
    }

    dbd_oracle_bind(statement, values);

    sql->status = OCIStmtExecute(sql->svc, statement->stmt, sql->err, 1, 0,
                                 oldsnapshot, newsnapshot, exec_mode);
    switch (sql->status) {
    case OCI_SUCCESS:
        break;
    case OCI_ERROR:
#ifdef DEBUG
        OCIErrorGet(sql->err, 1, NULL, &errorcode,
                    sql->buf, sizeof(sql->buf), OCI_HTYPE_ERROR);
        printf("Execute error %d: %s\n", sql->status, sql->buf);
#endif
        /* fallthrough */
    default:
        if (TXN_NOTICE_ERRORS(trans)) {
            trans->status = TRANS_ERROR;
        }
        return 1;
    }

    sql->status = OCIAttrGet(statement->stmt, OCI_HTYPE_STMT, nrows, 0,
                             OCI_ATTR_ROW_COUNT, sql->err);
    return 0;
}