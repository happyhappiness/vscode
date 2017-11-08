static int odbc_transaction_mode_get(apr_dbd_transaction_t * trans)
{
    return (int) trans->apr_dbd->transaction_mode;
}