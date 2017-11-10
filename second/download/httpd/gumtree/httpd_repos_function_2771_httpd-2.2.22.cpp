static int dbd_freetds_end_transaction(apr_dbd_transaction_t *trans)
{
    int dummy;
    if (trans) {
        /* rollback on error or explicit rollback request */
        if (trans->errnum) {
            trans->errnum = 0;
            trans->handle->err = freetds_exec(trans->handle->proc,
                                              "ROLLBACK", 0, &dummy);
        }
        else {
            trans->handle->err = freetds_exec(trans->handle->proc,
                                              "COMMIT", 0, &dummy);
        }
        trans->handle->trans = NULL;
    }
    return (trans->handle->err == SUCCEED) ? 0 : 1;
}