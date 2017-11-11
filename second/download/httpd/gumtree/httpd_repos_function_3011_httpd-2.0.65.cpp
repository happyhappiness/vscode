apr_status_t apr_file_check_read(apr_file_t *fd)
{
    int rc;

    if (!fd->pipe)
        return APR_SUCCESS; /* Not a pipe, assume no waiting */

    rc = DosWaitEventSem(fd->pipeSem, SEM_IMMEDIATE_RETURN);

    if (rc == ERROR_TIMEOUT)
        return APR_TIMEUP;

    return APR_FROM_OS_ERROR(rc);
}