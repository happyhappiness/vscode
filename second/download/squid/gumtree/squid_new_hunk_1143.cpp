static bool
mainChangeDir(const char *dir)
{
    if (chdir(dir) == 0)
        return true;

    int xerrno = errno;
    debugs(50, DBG_CRITICAL, "ERROR: cannot change current directory to " << dir <<
           ": " << xstrerr(xerrno));
    return false;
}

/// Hack: Have we called chroot()? This exposure is needed because some code has
/// to open the same files before and after chroot()
bool Chrooted = false;

/// set the working directory.
static void
mainSetCwd(void)
{
    if (Config.chroot_dir && !Chrooted) {
        Chrooted = true;

        if (chroot(Config.chroot_dir) != 0) {
            int xerrno = errno;
            fatalf("chroot to %s failed: %s", Config.chroot_dir, xstrerr(xerrno));
        }

        if (!mainChangeDir("/"))
            fatalf("chdir to / after chroot to %s failed", Config.chroot_dir);
    }

    if (Config.coredump_dir && strcmp("none", Config.coredump_dir) != 0) {
