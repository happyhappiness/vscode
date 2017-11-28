        return;

    debugs(21, 3, "leave_suid: PID " << getpid() << " giving up root, becoming '" << Config.effectiveUser << "'");

    if (!Config.effectiveGroup) {

        if (setgid(Config2.effectiveGroupID) < 0) {
            int xerrno = errno;
            debugs(50, DBG_CRITICAL, "ALERT: setgid: " << xstrerr(xerrno));
        }

        if (initgroups(Config.effectiveUser, Config2.effectiveGroupID) < 0) {
            debugs(50, DBG_CRITICAL, "ALERT: initgroups: unable to set groups for User " <<
                   Config.effectiveUser << " and Group " <<
                   (unsigned) Config2.effectiveGroupID << "");
        }
    }

#if HAVE_SETRESUID
    if (setresuid(Config2.effectiveUserID, Config2.effectiveUserID, 0) < 0) {
        const auto xerrno = errno;
        fatalf("FATAL: setresuid: %s", xstrerr(xerrno));
    }

#elif HAVE_SETEUID
    if (seteuid(Config2.effectiveUserID) < 0) {
        const auto xerrno = errno;
        fatalf("FATAL: seteuid: %s", xstrerr(xerrno));
    }

#else
    if (setuid(Config2.effectiveUserID) < 0) {
        const auto xerrno = errno;
        fatalf("FATAL: setuid: %s", xstrerr(xerrno));
    }

#endif

    restoreCapabilities(true);

#if HAVE_PRCTL && defined(PR_SET_DUMPABLE)
    /* Set Linux DUMPABLE flag */
    if (Config.coredump_dir && prctl(PR_SET_DUMPABLE, 1) != 0) {
        int xerrno = errno;
        debugs(50, 2, "ALERT: prctl: " << xstrerr(xerrno));
    }
#endif
}

/* Enter a privilegied section */
void
enter_suid(void)
{
    debugs(21, 3, "enter_suid: PID " << getpid() << " taking root privileges");
#if HAVE_SETRESUID
    if (setresuid((uid_t)-1, 0, (uid_t)-1) < 0) {
        const auto xerrno = errno;
        debugs (21, 3, "enter_suid: setresuid failed: " << xstrerr(xerrno));
    }
#else

    setuid(0);
#endif
#if HAVE_PRCTL && defined(PR_SET_DUMPABLE)
    /* Set Linux DUMPABLE flag */

    if (Config.coredump_dir && prctl(PR_SET_DUMPABLE, 1) != 0) {
        int xerrno = errno;
        debugs(50, 2, "ALERT: prctl: " << xstrerr(xerrno));
    }
#endif
}

/* Give up the posibility to gain privilegies.
 * this should be used before starting a sub process
 */
