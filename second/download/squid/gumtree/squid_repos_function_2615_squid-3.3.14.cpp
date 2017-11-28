void
no_suid(void)
{
    uid_t uid;
    leave_suid();
    uid = geteuid();
    debugs(21, 3, "no_suid: PID " << getpid() << " giving up root priveleges forever");

    if (setuid(0) < 0)
        debugs(50, DBG_IMPORTANT, "WARNING: no_suid: setuid(0): " << xstrerror());

    if (setuid(uid) < 0)
        debugs(50, DBG_IMPORTANT, "ERROR: no_suid: setuid(" << uid << "): " << xstrerror());

    restoreCapabilities(0);

#if HAVE_PRCTL && defined(PR_SET_DUMPABLE)
    /* Set Linux DUMPABLE flag */
    if (Config.coredump_dir && prctl(PR_SET_DUMPABLE, 1) != 0)
        debugs(50, 2, "ALERT: prctl: " << xstrerror());

#endif
}