
APLOG_USE_MODULE(core);

apr_status_t ap_init_ebcdic(apr_pool_t *pool)
{
    apr_status_t rv;
    char buf[80];

    rv = apr_xlate_open(&ap_hdrs_to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, pool);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                     "apr_xlate_open() failed");
        return rv;
