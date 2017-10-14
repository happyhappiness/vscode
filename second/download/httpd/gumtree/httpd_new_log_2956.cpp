ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "Cannot chroot when not started as root");