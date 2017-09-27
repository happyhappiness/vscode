
        if (ap_unixd_config.user_name[0] == '#') {
            struct passwd *ent;
            uid_t uid = atol(&ap_unixd_config.user_name[1]);

            if ((ent = getpwuid(uid)) == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL, APLOGNO(02155)
                         "getpwuid: couldn't determine user name from uid %ld, "
                         "you probably need to modify the User directive",
                         (long)uid);
                return -1;
            }

