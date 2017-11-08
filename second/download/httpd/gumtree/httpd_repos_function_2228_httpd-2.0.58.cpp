static int set_group_privs(uid_t uid, gid_t gid)
{
    if (!geteuid()) {
        const char *name;

        /* Get username if passed as a uid */

        struct passwd *ent;

        if ((ent = getpwuid(uid)) == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "getpwuid: couldn't determine user name from uid %u, "
                         "you probably need to modify the User directive",
                         (unsigned)uid);
            return -1;
        }

        name = ent->pw_name;

        /*
         * Set the GID before initgroups(), since on some platforms
         * setgid() is known to zap the group list.
         */
        if (setgid(gid) == -1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "setgid: unable to set group id to Group %u",
                         (unsigned)gid);
            return -1;
        }

        /* Reset `groups' attributes. */

        if (initgroups(name, gid) == -1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "initgroups: unable to set groups for User %s "
                         "and Group %u", name, (unsigned)gid);
            return -1;
        }
    }
    return 0;
}