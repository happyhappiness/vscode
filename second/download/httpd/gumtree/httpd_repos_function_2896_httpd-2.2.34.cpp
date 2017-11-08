static int dbd_sqlite3_end_transaction(apr_dbd_transaction_t *trans)
{
    int ret = -1; /* ending transaction that was never started is an error */
    int nrows = 0;

    if (trans) {
        /* rollback on error or explicit rollback request */
        if (trans->errnum || TXN_DO_ROLLBACK(trans)) {
            trans->errnum = 0;
            ret = dbd_sqlite3_query(trans->handle, &nrows, "ROLLBACK");
        } else {
            ret = dbd_sqlite3_query(trans->handle, &nrows, "COMMIT");
        }
        trans->handle->trans = NULL;
    }

    return ret;
}