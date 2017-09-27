ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                    "setuid: unable to change to uid: %ld",
                    (long) unixd_config.user_id);