static int dbd_sqlite_end_transaction(apr_dbd_transaction_t * trans)
{
    int rows;
    int ret = -1;               /* no transaction is an error cond */

    if (trans) {
        if (trans->errnum) {
            trans->errnum = 0;
            ret =
                dbd_sqlite_query(trans->handle, &rows,
                                 "ROLLBACK TRANSACTION");
        }
        else {
            ret =
                dbd_sqlite_query(trans->handle, &rows, "COMMIT TRANSACTION");
        }
        trans->handle->trans = NULL;
    }

    return ret;
}