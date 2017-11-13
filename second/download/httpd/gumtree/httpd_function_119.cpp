static apr_status_t ssl_io_filter_cleanup (void *data)
{
    apr_status_t ret;
    SSLFilterRec *pRec = (SSLFilterRec *)data;

    if (!pRec->pssl) {
        /* already been shutdown */
        return APR_SUCCESS;
    }

    if ((ret = ssl_hook_CloseConnection(pRec)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, ret, NULL,
                     "Error in ssl_hook_CloseConnection");
    }

    return ret;
}