static int dbd_oracle_end_transaction(apr_dbd_transaction_t *trans)
{
    int ret = 1;             /* no transaction is an error cond */
    sword status;
    apr_dbd_t *handle = trans->handle;
    if (trans) {
        switch (trans->status) {
        case TRANS_NONE:     /* No trans is an error here */
            status = OCI_ERROR;
            break;
        case TRANS_ERROR:
            status = OCITransRollback(handle->svc, handle->err, OCI_DEFAULT);
            break;
        default:
            /* rollback on explicit rollback request */
            if (TXN_DO_ROLLBACK(trans)) {
                status = OCITransRollback(handle->svc, handle->err, OCI_DEFAULT);
            } else {
                status = OCITransCommit(handle->svc, handle->err, OCI_DEFAULT);
            }
            break;
        }

        handle->trans = NULL;

        switch (status) {
        case OCI_SUCCESS:
            ret = 0;
            break;
        default:
            ret = 3;
            break;
        }
    }
    return ret;
}