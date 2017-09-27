    piped_log *pl = data;

    apr_file_close(ap_piped_log_write_fd(pl));
    return APR_SUCCESS;
}

AP_DECLARE(piped_log *) ap_open_piped_log_ex(apr_pool_t *p,
                                             const char *program,
                                             apr_cmdtype_e cmdtype)
{
    piped_log *pl;
    apr_file_t *dummy = NULL;
    int rc;

    rc = log_child(p, program, &dummy, cmdtype, 0);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                     "Couldn't start piped log process");
        return NULL;
    }

