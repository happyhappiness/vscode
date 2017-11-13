ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02159)
                         "Can't chdir to %s", ap_unixd_config.chroot_dir);