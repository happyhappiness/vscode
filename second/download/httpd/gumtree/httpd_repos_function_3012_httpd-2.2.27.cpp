static int dbd_mysql_transaction(apr_pool_t *pool, apr_dbd_t *handle,
                                 apr_dbd_transaction_t **trans)
{
    /* Don't try recursive transactions here */
    if (handle->trans) {
        dbd_mysql_end_transaction(handle->trans) ;
    }
    if (!*trans) {
        *trans = apr_pcalloc(pool, sizeof(apr_dbd_transaction_t));
    }
    (*trans)->errnum = mysql_autocommit(handle->conn, 0);
    (*trans)->handle = handle;
    handle->trans = *trans;
    return (*trans)->errnum;
}