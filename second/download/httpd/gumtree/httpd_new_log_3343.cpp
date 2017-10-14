ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02157)
                        "initgroups: unable to set groups for User %s "
                        "and Group %ld", name, (long)ap_unixd_config.group_id);