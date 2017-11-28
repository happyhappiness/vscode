int
main(int argc, char **argv)
{
    char username[256];
    char password[256];
    char wstr[256];
    int err = 0;

    openlog("msnt_auth", LOG_PID, LOG_USER);
    setbuf(stdout, NULL);

    /* Read configuration file. Abort wildly if error. */
    if (OpenConfigFile() == 1)
        return 1;

    /*
     * Read denied and allowed user files.
     * If they fails, there is a serious problem.
     * Check syslog messages. Deny all users while in this state.
     * The msntauth process should then be killed.
     */
    if ((Read_denyusers() == 1) || (Read_allowusers() == 1)) {
        while (1) {
            memset(wstr, '\0', sizeof(wstr));
            if (fgets(wstr, 255, stdin) == NULL)
                break;
            puts("ERR");
        }
        return 1;
    }

    /*
     * Make Check_forchange() the handle for HUP signals.
     * Don't use alarms any more. I don't think it was very
     * portable between systems.
     * XXX this should be sigaction()
     */
    signal(SIGHUP, Check_forchange);

    while (1) {
        int n;
        /* Read whole line from standard input. Terminate on break. */
        memset(wstr, '\0', sizeof(wstr));
        if (fgets(wstr, 255, stdin) == NULL)
            break;
        /* ignore this line if we didn't get the end-of-line marker */
        if (NULL == strchr(wstr, '\n')) {
            err = 1;
            continue;
        }
        if (err) {
            syslog(LOG_WARNING, "oversized message");
            puts("ERR");
            err = 0;
            continue;
        }

        /*
         * extract username and password.
         * XXX is sscanf() safe?
         */
        username[0] = '\0';
        password[0] = '\0';
        n = sscanf(wstr, "%s %[^\n]", username, password);
        if (2 != n) {
            puts("ERR");
            continue;
        }
        /* Check for invalid or blank entries */
        if ((username[0] == '\0') || (password[0] == '\0')) {
            puts("ERR");
            continue;
        }
        Checktimer();		/* Check if the user lists have changed */

        rfc1738_unescape(username);
        rfc1738_unescape(password);

        /*
         * Check if user is explicitly denied or allowed.
         * If user passes both checks, they can be authenticated.
         */
        if (Check_user(username) == 1) {
            syslog(LOG_INFO, "'%s' denied", username);
            puts("ERR");
        } else if (QueryServers(username, password) == 0)
            puts("OK");
        else {
            syslog(LOG_INFO, "'%s' login failed", username);
            puts("ERR");
        }
        err = 0;
    }

    return 0;
}