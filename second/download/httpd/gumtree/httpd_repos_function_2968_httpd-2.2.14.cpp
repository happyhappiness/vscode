static int dbd_mysql_end_transaction(apr_dbd_transaction_t *trans)
{
    int ret = -1;
    if (trans) {
        /* rollback on error or explicit rollback request */
        if (trans->errnum || TXN_DO_ROLLBACK(trans)) {
            trans->errnum = 0;
            ret = mysql_rollback(trans->handle->conn);
        }
        else {
            ret = mysql_commit(trans->handle->conn);
        }
    }
    ret |= mysql_autocommit(trans->handle->conn, 1);
    trans->handle->trans = NULL;
    return ret;
}