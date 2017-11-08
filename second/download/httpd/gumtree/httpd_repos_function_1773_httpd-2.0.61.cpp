const char *os_set_account(apr_pool_t *p, const char *account)
{
    char account_temp[ACCT_LEN+1];

    apr_cpystrn(account_temp, account, sizeof account_temp);

    /* Make account all upper case */
    ap_str_toupper(account_temp);

    /* Pad to length 8 */
    ap_pad(account_temp, sizeof account_temp, ' ');

    bs2000_account = apr_pstrdup(p, account_temp);
    return NULL;
}