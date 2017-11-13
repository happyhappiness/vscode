ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                        "initgroups: unable to set groups for User %s "
                        "and Group %u", name, (unsigned)unixd_config.group_id);