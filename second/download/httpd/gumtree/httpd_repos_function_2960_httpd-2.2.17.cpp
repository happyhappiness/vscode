static int dbd_pgsql_end_transaction(apr_dbd_transaction_t *trans)
{
    PGresult *res;
    int ret = -1;                /* no transaction is an error cond */
    if (trans) {
        /* rollback on error or explicit rollback request */
        if (trans->errnum || TXN_DO_ROLLBACK(trans)) {
            trans->errnum = 0;
            res = PQexec(trans->handle->conn, "ROLLBACK");
        }
        else {
            res = PQexec(trans->handle->conn, "COMMIT");
        }
        if (res) {
            ret = PQresultStatus(res);
            if (dbd_pgsql_is_success(ret)) {
                ret = 0;
            }
            PQclear(res);
        }
        else {
            ret = PGRES_FATAL_ERROR;
        }
        trans->handle->trans = NULL;
    }
    return ret;
}