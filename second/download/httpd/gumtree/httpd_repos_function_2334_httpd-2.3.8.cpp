static int set_group_privs(void)
{
    if (!geteuid()) {
        const char *name;

        /* Get username if passed as a uid */

        if (ap_unixd_config.user_name[0] == '#') {
            struct passwd *ent;
            uid_t uid = atol(&ap_unixd_config.user_name[1]);

            if ((ent = getpwuid(uid)) == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "getpwuid: couldn't determine user name from uid %ld, "
                         "you probably need to modify the User directive",
                         (long)uid);
                return -1;
            }

            name = ent->pw_name;
        }
        else
            name = ap_unixd_config.user_name;

#if !defined(OS2)
        /* OS/2 doesn't support groups. */
        /*
         * Set the GID before initgroups(), since on some platforms
         * setgid() is known to zap the group list.
         */
        if (setgid(ap_unixd_config.group_id) == -1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                        "setgid: unable to set group id to Group %ld",
                        (long)ap_unixd_config.group_id);
            return -1;
        }

        /* Reset `groups' attributes. */

        if (initgroups(name, ap_unixd_config.group_id) == -1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                        "initgroups: unable to set groups for User %s "
                        "and Group %ld", name, (long)ap_unixd_config.group_id);
            return -1;
        }
#endif /* !defined(OS2) */
    }
    return 0;
}