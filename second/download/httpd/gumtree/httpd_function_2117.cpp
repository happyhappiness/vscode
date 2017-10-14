static int set_group_privs(void)
{
    if (!geteuid()) {
        const char *name;

        /* Get username if passed as a uid */

        if (unixd_config.user_name[0] == '#') {
            struct passwd *ent;
            uid_t uid = atoi(&unixd_config.user_name[1]);

            if ((ent = getpwuid(uid)) == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "getpwuid: couldn't determine user name from uid %u, "
                         "you probably need to modify the User directive",
                         (unsigned)uid);
                return -1;
            }

            name = ent->pw_name;
        }
        else
            name = unixd_config.user_name;

#if !defined(OS2) && !defined(TPF)
        /* OS/2 and TPF don't support groups. */

        /*
         * Set the GID before initgroups(), since on some platforms
         * setgid() is known to zap the group list.
         */
        if (setgid(unixd_config.group_id) == -1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                        "setgid: unable to set group id to Group %u",
                        (unsigned)unixd_config.group_id);
            return -1;
        }

        /* Reset `groups' attributes. */

        if (initgroups(name, unixd_config.group_id) == -1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                        "initgroups: unable to set groups for User %s "
                        "and Group %u", name, (unsigned)unixd_config.group_id);
            return -1;
        }
#endif /* !defined(OS2) && !defined(TPF) */
    }
    return 0;
}