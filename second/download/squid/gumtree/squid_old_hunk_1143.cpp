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
