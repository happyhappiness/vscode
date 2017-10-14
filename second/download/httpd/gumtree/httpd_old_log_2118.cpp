ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                        "setgid: unable to set group id to Group %u",
                        (unsigned)unixd_config.group_id);