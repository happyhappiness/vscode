static apr_status_t log_sed_errf(void *data, const char *error)
{
    request_rec *r = (request_rec *) data;
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02998) "%s", error);
    return APR_SUCCESS;
}