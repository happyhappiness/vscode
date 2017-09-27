    if (set_group_privs()) {
        return -1;
    }

    if (NULL != ap_unixd_config.chroot_dir) {
        if (geteuid()) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02164)
                         "Cannot chroot when not started as root");
            return -1;
        }
        if (chdir(ap_unixd_config.chroot_dir) != 0) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02165)
                         "Can't chdir to %s", ap_unixd_config.chroot_dir);
            return -1;
        }
        if (chroot(ap_unixd_config.chroot_dir) != 0) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02166)
                         "Can't chroot to %s", ap_unixd_config.chroot_dir);
            return -1;
        }
        if (chdir("/") != 0) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02167)
                         "Can't chdir to new root");
            return -1;
        }
    }

    /* Only try to switch if we're running as root */
    if (!geteuid() && (
#ifdef _OSD_POSIX
        os_init_job_environment(NULL, ap_unixd_config.user_name, ap_exists_config_define("DEBUG")) != 0 ||
#endif
        setuid(ap_unixd_config.user_id) == -1)) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02168)
                    "setuid: unable to change to uid: %ld",
                    (long) ap_unixd_config.user_id);
        return -1;
    }
#if defined(HAVE_PRCTL) && defined(PR_SET_DUMPABLE)
    /* this applies to Linux 2.4+ */
    if (ap_coredumpdir_configured) {
        if (prctl(PR_SET_DUMPABLE, 1)) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02169)
                         "set dumpable failed - this child will not coredump"
                         " after software errors");
        }
    }
#endif
    return 0;
}

static void unixd_dump_config(apr_pool_t *p, server_rec *s)
{
    apr_file_t *out = NULL;
    apr_uid_t uid = ap_unixd_config.user_id;
    apr_gid_t gid = ap_unixd_config.group_id;
    char *no_root = "";
    if (!ap_exists_config_define("DUMP_RUN_CFG"))
        return;
    if (geteuid() != 0)
        no_root = " not_used";
    apr_file_open_stdout(&out, p);
    apr_file_printf(out, "User: name=\"%s\" id=%lu%s\n",
                    ap_unixd_config.user_name, (unsigned long)uid, no_root);
    apr_file_printf(out, "Group: name=\"%s\" id=%lu%s\n",
                    ap_unixd_config.group_name, (unsigned long)gid, no_root);
    if (ap_unixd_config.chroot_dir)
        apr_file_printf(out, "ChrootDir: \"%s\"%s\n",
                        ap_unixd_config.chroot_dir, no_root);
}

static void unixd_hooks(apr_pool_t *pool)
{
    ap_hook_pre_config(unixd_pre_config,
                       NULL, NULL, APR_HOOK_FIRST);
    ap_hook_test_config(unixd_dump_config,
                        NULL, NULL, APR_HOOK_FIRST);
    ap_hook_drop_privileges(unixd_drop_privileges,
                            NULL, NULL, APR_HOOK_MIDDLE);
}

static const command_rec unixd_cmds[] = {
    AP_INIT_TAKE1("User", unixd_set_user, NULL, RSRC_CONF,
                  "Effective user id for this server"),
    AP_INIT_TAKE1("Group", unixd_set_group, NULL, RSRC_CONF,
                  "Effective group id for this server"),
    AP_INIT_TAKE1("ChrootDir", unixd_set_chroot_dir, NULL, RSRC_CONF,
                  "The directory to chroot(2) into"),
    AP_INIT_FLAG("Suexec", unixd_set_suexec, NULL, RSRC_CONF,
                 "Enable or disable suEXEC support"),
    {NULL}
};

AP_DECLARE_MODULE(unixd) = {
    STANDARD20_MODULE_STUFF,
    NULL,
