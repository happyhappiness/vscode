ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "Can't chroot to %s", unixd_config.chroot_dir);