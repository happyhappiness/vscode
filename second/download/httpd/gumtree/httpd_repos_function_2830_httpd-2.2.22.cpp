static int odbc_transaction_mode_set(apr_dbd_transaction_t *trans, int mode)
{
    int legal = (  APR_DBD_TRANSACTION_IGNORE_ERRORS
                 | APR_DBD_TRANSACTION_COMMIT
                 | APR_DBD_TRANSACTION_ROLLBACK);

    if ((mode & legal) != mode)
        return APR_EGENERAL;

    trans->apr_dbd->can_commit = mode;
    return APR_SUCCESS;
}