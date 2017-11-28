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