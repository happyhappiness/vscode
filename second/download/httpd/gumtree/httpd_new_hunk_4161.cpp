
    rc = DosCreateMutexSem(NULL, &ap_mpm_accept_mutex, DC_SEM_SHARED, FALSE);

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, APR_FROM_OS_ERROR(rc), s, APLOGNO(00204)
                     "failure creating accept mutex, shutting down");
        return !OK;
    }

    parent_info->accept_mutex = ap_mpm_accept_mutex;

    /* Allocate shared memory for scoreboard */
    if (ap_scoreboard_image == NULL) {
