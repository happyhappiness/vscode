        /* OS/2 doesn't support groups. */
        /*
         * Set the GID before initgroups(), since on some platforms
         * setgid() is known to zap the group list.
         */
        if (setgid(ap_unixd_config.group_id) == -1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02156)
                        "setgid: unable to set group id to Group %ld",
                        (long)ap_unixd_config.group_id);
            return -1;
        }

        /* Reset `groups' attributes. */

        if (initgroups(name, ap_unixd_config.group_id) == -1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02157)
                        "initgroups: unable to set groups for User %s "
                        "and Group %ld", name, (long)ap_unixd_config.group_id);
            return -1;
        }
#endif /* !defined(OS2) */
    }
    return 0;
}


static int
unixd_drop_privileges(apr_pool_t *pool, server_rec *s)
{
    int rv = set_group_privs();

    if (rv) {
        return rv;
    }

    if (NULL != ap_unixd_config.chroot_dir) {
        if (geteuid()) {
            rv = errno;
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02158)
                         "Cannot chroot when not started as root");
            return rv;
        }

        if (chdir(ap_unixd_config.chroot_dir) != 0) {
            rv = errno;
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02159)
                         "Can't chdir to %s", ap_unixd_config.chroot_dir);
            return rv;
        }

        if (chroot(ap_unixd_config.chroot_dir) != 0) {
            rv = errno;
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02160)
                         "Can't chroot to %s", ap_unixd_config.chroot_dir);
            return rv;
        }

        if (chdir("/") != 0) {
            rv = errno;
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02161)
                         "Can't chdir to new root");
            return rv;
        }
    }

    /* Only try to switch if we're running as root */
    if (!geteuid() && (
#ifdef _OSD_POSIX
        os_init_job_environment(NULL, ap_unixd_config.user_name, ap_exists_config_define("DEBUG")) != 0 ||
#endif
        setuid(ap_unixd_config.user_id) == -1)) {
        rv = errno;
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02162)
                    "setuid: unable to change to uid: %ld",
                    (long) ap_unixd_config.user_id);
        return rv;
    }
#if defined(HAVE_PRCTL) && defined(PR_SET_DUMPABLE)
    /* this applies to Linux 2.4+ */
    if (ap_coredumpdir_configured) {
        if (prctl(PR_SET_DUMPABLE, 1)) {
            rv = errno;
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02163)
                         "set dumpable failed - this child will not coredump"
                         " after software errors");
            return rv;
        }
    }
#endif
