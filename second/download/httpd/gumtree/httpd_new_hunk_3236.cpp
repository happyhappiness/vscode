     */

    if (one_process) {

        type = forktype = bs2_noFORK;

        ap_log_error(APLOG_MARK, APLOG_ERR, 0, server, APLOGNO(02170)
                     "The debug mode of Apache should only "
                     "be started by an unprivileged user!");
        return 0;
    }

    return 0;
