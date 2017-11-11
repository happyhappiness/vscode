static int dbd_oracle_pbselect(apr_pool_t * pool, apr_dbd_t * sql,
                               apr_dbd_results_t ** results,
                               apr_dbd_prepared_t * statement,
                               int seek, const void **values)
{
    int exec_mode = seek ? OCI_STMT_SCROLLABLE_READONLY : OCI_DEFAULT;
    OCISnapshot *oldsnapshot = NULL;
    OCISnapshot *newsnapshot = NULL;
    apr_dbd_transaction_t* trans = sql->trans;
    int_errorcode;

    if (trans) {
        switch (trans->status) {
        case TRANS_ERROR:
            return 1;
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
    }

    dbd_oracle_bbind(statement, values);

    sql->status = OCIStmtExecute(sql->svc, statement->stmt, sql->err, 0, 0,
                                 oldsnapshot, newsnapshot, exec_mode);
    switch (sql->status) {
    case OCI_SUCCESS:
        break;
    case OCI_ERROR:
#ifdef DEBUG
        OCIErrorGet(sql->err, 1, NULL, &errorcode,
                    sql->buf, sizeof(sql->buf), OCI_HTYPE_ERROR);
        printf("Executing prepared statement: %s\n", sql->buf);
#endif
        /* fallthrough */
    default:
        if (TXN_NOTICE_ERRORS(trans)) {
            trans->status = TRANS_ERROR;
        }
        return 1;
    }

    if (!*results) {
        *results = apr_palloc(pool, sizeof(apr_dbd_results_t));
    }
    (*results)->handle = sql;
    (*results)->statement = statement;
    (*results)->seek = seek;
    (*results)->rownum = seek ? 0 : -1;
    (*results)->pool = pool;

    return 0;
}