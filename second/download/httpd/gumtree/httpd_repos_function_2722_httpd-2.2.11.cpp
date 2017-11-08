static int dbd_freetds_transaction_mode_get(apr_dbd_transaction_t *trans)
{
    return trans ? trans->mode : APR_DBD_TRANSACTION_COMMIT;
}