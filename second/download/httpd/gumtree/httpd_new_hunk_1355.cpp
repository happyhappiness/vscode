AP_DECLARE(piped_log *) ap_open_piped_log(apr_pool_t *p, const char *program)
{
    piped_log *pl;
    apr_file_t *dummy = NULL;
    int rc;

    rc = log_child(p, program, &dummy, 0);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                     "Couldn't start piped log process");
        return NULL;
    }

