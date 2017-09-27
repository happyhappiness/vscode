        if (status == APEXIT_CHILDSICK) {
            return status;
        }

        if (status == APEXIT_CHILDFATAL) {
            ap_log_error(APLOG_MARK, APLOG_ALERT,
                         0, ap_server_conf, APLOGNO(00050)
                         "Child %" APR_PID_T_FMT
                         " returned a Fatal error... Apache is exiting!",
                         pid->pid);
            return APEXIT_CHILDFATAL;
        }

