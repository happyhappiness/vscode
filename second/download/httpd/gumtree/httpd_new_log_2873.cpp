ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02162)
                    "setuid: unable to change to uid: %ld",
                    (long) ap_unixd_config.user_id);