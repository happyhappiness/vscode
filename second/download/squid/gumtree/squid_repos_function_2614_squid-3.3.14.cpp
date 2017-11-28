void
enter_suid(void)
{
    debugs(21, 3, "enter_suid: PID " << getpid() << " taking root privileges");
#if HAVE_SETRESUID
    if (setresuid((uid_t)-1, 0, (uid_t)-1) < 0)
        debugs (21, 3, "enter_suid: setresuid failed: " << xstrerror ());
#else

    setuid(0);
#endif
#if HAVE_PRCTL && defined(PR_SET_DUMPABLE)
    /* Set Linux DUMPABLE flag */

    if (Config.coredump_dir && prctl(PR_SET_DUMPABLE, 1) != 0)
        debugs(50, 2, "ALERT: prctl: " << xstrerror());

#endif
}