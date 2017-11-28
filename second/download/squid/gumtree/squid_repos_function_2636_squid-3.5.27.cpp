void
leave_suid(void)
{
    debugs(21, 3, "leave_suid: PID " << getpid() << " called");

    if (Config.effectiveGroup) {

#if HAVE_SETGROUPS

        setgroups(1, &Config2.effectiveGroupID);

#endif

        if (setgid(Config2.effectiveGroupID) < 0)
            debugs(50, DBG_CRITICAL, "ALERT: setgid: " << xstrerror());

    }

    if (geteuid() != 0)
        return;

    /* Started as a root, check suid option */
    if (Config.effectiveUser == NULL)
        return;

    debugs(21, 3, "leave_suid: PID " << getpid() << " giving up root, becoming '" << Config.effectiveUser << "'");

    if (!Config.effectiveGroup) {

        if (setgid(Config2.effectiveGroupID) < 0)
            debugs(50, DBG_CRITICAL, "ALERT: setgid: " << xstrerror());

        if (initgroups(Config.effectiveUser, Config2.effectiveGroupID) < 0) {
            debugs(50, DBG_CRITICAL, "ALERT: initgroups: unable to set groups for User " <<
                   Config.effectiveUser << " and Group " <<
                   (unsigned) Config2.effectiveGroupID << "");
        }
    }

#if HAVE_SETRESUID

    if (setresuid(Config2.effectiveUserID, Config2.effectiveUserID, 0) < 0)
        debugs(50, DBG_CRITICAL, "ALERT: setresuid: " << xstrerror());

#elif HAVE_SETEUID

    if (seteuid(Config2.effectiveUserID) < 0)
        debugs(50, DBG_CRITICAL, "ALERT: seteuid: " << xstrerror());

#else

    if (setuid(Config2.effectiveUserID) < 0)
        debugs(50, DBG_CRITICAL, "ALERT: setuid: " << xstrerror());

#endif

    restoreCapabilities(true);

#if HAVE_PRCTL && defined(PR_SET_DUMPABLE)
    /* Set Linux DUMPABLE flag */
    if (Config.coredump_dir && prctl(PR_SET_DUMPABLE, 1) != 0)
        debugs(50, 2, "ALERT: prctl: " << xstrerror());

#endif
}