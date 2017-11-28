        debugs(0, DBG_CRITICAL, "it to run as a non-priveledged user with the");
        debugs(0, DBG_CRITICAL, "'cache_effective_user' option in the config file.");
        fatal("Don't run Squid as root, set 'cache_effective_user'!");
    }
}

static void
mainSetCwd(void)
{
    char pathbuf[MAXPATHLEN];

    if (Config.coredump_dir) {
        if (0 == strcmp("none", Config.coredump_dir)) {
            (void) 0;
        } else if (chdir(Config.coredump_dir) == 0) {
            debugs(0, DBG_IMPORTANT, "Set Current Directory to " << Config.coredump_dir);
            return;
        } else {
            debugs(50, DBG_CRITICAL, "chdir: " << Config.coredump_dir << ": " << xstrerror());
        }
    }

    /* If we don't have coredump_dir or couldn't cd there, report current dir */
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

    if (Config.chroot_dir && (chroot(Config.chroot_dir) != 0 || chdir("/") != 0)) {
        fatal("failed to chroot");
    }

    if (opt_catch_signals) {
        squid_signal(SIGSEGV, death, SA_NODEFER | SA_RESETHAND);
        squid_signal(SIGBUS, death, SA_NODEFER | SA_RESETHAND);
    }

