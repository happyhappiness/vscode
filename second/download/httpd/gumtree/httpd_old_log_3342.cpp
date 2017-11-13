ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                        "setgid: unable to set group id to Group %ld",
                        (long)ap_unixd_config.group_id);