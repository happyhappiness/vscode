static int dbd_oracle_transaction_mode_set(apr_dbd_transaction_t *trans,
                                           int mode)
{
    if (!trans)
        return APR_DBD_TRANSACTION_COMMIT;

    return trans->mode = (mode & TXN_MODE_BITS);
}