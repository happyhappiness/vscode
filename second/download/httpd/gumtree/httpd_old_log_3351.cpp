ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "Can't chdir to %s", ap_unixd_config.chroot_dir);