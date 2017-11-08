static int dbd_sqlite3_end_transaction(apr_dbd_transaction_t *trans)
{
    int ret = 0;
    int nrows = 0;

    if (trans) {
        ret = dbd_sqlite3_query(trans->handle, &nrows, "END TRANSACTION;");
        if (trans->errnum) {
            trans->errnum = 0;
            ret = dbd_sqlite3_query(trans->handle, &nrows, "ROLLBACK;");
        } else {
            ret = dbd_sqlite3_query(trans->handle, &nrows, "COMMIT;");
        }
        trans->handle->trans = NULL;
    }

    return ret;
}