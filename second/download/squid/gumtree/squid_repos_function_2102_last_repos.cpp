void
no_suid(void)
{
    uid_t uid;
    leave_suid();
    uid = geteuid();
    debugs(21, 3, "no_suid: PID " << getpid() << " giving up root priveleges forever");

    if (setuid(0) < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, "WARNING: no_suid: setuid(0): " << xstrerr(xerrno));
    }

    if (setuid(uid) < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, "ERROR: no_suid: setuid(" << uid << "): " << xstrerr(xerrno));
    }

    restoreCapabilities(false);

#if HAVE_PRCTL && defined(PR_SET_DUMPABLE)
    /* Set Linux DUMPABLE flag */
    if (Config.coredump_dir && prctl(PR_SET_DUMPABLE, 1) != 0) {
        int xerrno = errno;
        debugs(50, 2, "ALERT: prctl: " << xstrerr(xerrno));
    }
#endif
}