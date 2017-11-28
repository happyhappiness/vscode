        debugs(0, DBG_CRITICAL, "it to run as a non-priveledged user with the");
        debugs(0, DBG_CRITICAL, "'cache_effective_user' option in the config file.");
        fatal("Don't run Squid as root, set 'cache_effective_user'!");
    }
}

/// changes working directory, providing error reporting
static bool
mainChangeDir(const char *dir)
{
    if (chdir(dir) == 0)
        return true;

    debugs(50, DBG_CRITICAL, "cannot change current directory to " << dir <<
           ": " << xstrerror());
    return false;
}

/// set the working directory.
static void
mainSetCwd(void)
{
    static bool chrooted = false;
    if (Config.chroot_dir && !chrooted) {
        chrooted = true;

        if (chroot(Config.chroot_dir) != 0)
            fatalf("chroot to %s failed: %s", Config.chroot_dir, xstrerror());

        if (!mainChangeDir("/"))
            fatalf("chdir to / after chroot to %s failed", Config.chroot_dir);
    }

    if (Config.coredump_dir && strcmp("none", Config.coredump_dir) != 0) {
        if (mainChangeDir(Config.coredump_dir)) {
            debugs(0, DBG_IMPORTANT, "Set Current Directory to " << Config.coredump_dir);
            return;
        }
    }

    /* If we don't have coredump_dir or couldn't cd there, report current dir */
    char pathbuf[MAXPATHLEN];
    if (getcwd(pathbuf, MAXPATHLEN)) {
        debugs(0, DBG_IMPORTANT, "Current Directory is " << pathbuf);
    } else {
        debugs(50, DBG_CRITICAL, "WARNING: Can't find current directory, getcwd: " << xstrerror());
    }
}

static void
mainInitialize(void)
{
    /* chroot if configured to run inside chroot */
    mainSetCwd();

    if (opt_catch_signals) {
        squid_signal(SIGSEGV, death, SA_NODEFER | SA_RESETHAND);
        squid_signal(SIGBUS, death, SA_NODEFER | SA_RESETHAND);
    }

