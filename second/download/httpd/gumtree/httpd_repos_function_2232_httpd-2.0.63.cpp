static int perchild_setup_child(int childnum)
{
    child_info_t *ug = &child_info_table[childnum];

    if (ug->uid == -1 && ug->gid == -1) {
        return unixd_setup_child();
    }
    if (set_group_privs(ug->uid, ug->gid)) {
        return -1;
    }
    /* Only try to switch if we're running as root */
    if (!geteuid()
        && (
#ifdef _OSD_POSIX
            os_init_job_environment(server_conf, unixd_config.user_name,
                                    one_process) != 0 ||
#endif
            setuid(ug->uid) == -1)) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                     "setuid: unable to change to uid: %ld",
                     (long) ug->uid);
        return -1;
    }
    return 0;
}