static int dbd_oracle_start_transaction(apr_pool_t *pool, apr_dbd_t *sql,
                                        apr_dbd_transaction_t **trans)
{
    int ret = 0;
    int_errorcode;
    if (*trans) {
        dbd_oracle_end_transaction(*trans);
    }
    else {
        *trans = apr_pcalloc(pool, sizeof(apr_dbd_transaction_t));
        OCIHandleAlloc(dbd_oracle_env, (dvoid**)&(*trans)->trans,
                       OCI_HTYPE_TRANS, 0, 0);
        OCIAttrSet(sql->svc, OCI_HTYPE_SVCCTX, (*trans)->trans, 0,
                   OCI_ATTR_TRANS, sql->err);
    }


    sql->status = OCITransStart(sql->svc, sql->err, TRANS_TIMEOUT,
                                OCI_TRANS_NEW);
    switch (sql->status) {
    case OCI_ERROR:
#ifdef DEBUG
        OCIErrorGet(sql->err, 1, NULL, &errorcode, sql->buf,
                    sizeof(sql->buf), OCI_HTYPE_ERROR);
        printf("Transaction: %s\n", sql->buf);
#endif
        ret = 1;
        break;
    case OCI_SUCCESS:
        (*trans)->handle = sql;
        (*trans)->status = TRANS_1;
        sql->trans = *trans;
        switch (OCIDescriptorAlloc(dbd_oracle_env,
                                   (dvoid**)&(*trans)->snapshot1,
                                   OCI_DTYPE_SNAP, 0, NULL)) {
        case OCI_SUCCESS:
            apr_pool_cleanup_register(pool, (*trans)->snapshot1,
                                      dbd_free_snapshot, apr_pool_cleanup_null);
            break;
        case OCI_INVALID_HANDLE:
            ret = 1;
            break;
        }
        switch (OCIDescriptorAlloc(dbd_oracle_env,
                                   (dvoid**)&(*trans)->snapshot2,
                                   OCI_DTYPE_SNAP, 0, NULL)) {
        case OCI_SUCCESS:
            apr_pool_cleanup_register(pool, (*trans)->snapshot2,
                                      dbd_free_snapshot, apr_pool_cleanup_null);
            break;
        case OCI_INVALID_HANDLE:
            ret = 1;
            break;
        }
        break;
    default:
        ret = 1;
        break;
    }
    return ret;
}