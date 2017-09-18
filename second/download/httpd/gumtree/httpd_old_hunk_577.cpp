{
#if APR_HAS_SHARED_MEMORY
    if (!detached) {
        return APR_SUCCESS;
    }
    if (apr_shm_size_get(ap_scoreboard_shm) < scoreboard_size) {
        ap_log_error(APLOG_MARK, APLOG_CRIT | APLOG_NOERRNO, 0, NULL,
                     "Fatal error: shared scoreboard too small for child!");
        apr_shm_detach(ap_scoreboard_shm);
        ap_scoreboard_shm = NULL;
        return APR_EINVAL;
    }
    /* everything will be cleared shortly */
