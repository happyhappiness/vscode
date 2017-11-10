static int dbd_freetds_transaction_mode_set(apr_dbd_transaction_t *trans,
                                            int mode)
{
    if (trans) {
        trans->mode = mode & TXN_MODE_BITS;
        return trans->mode;
    }
    return APR_DBD_TRANSACTION_COMMIT;
}