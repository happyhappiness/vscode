void
safeunlink(const char *s, int quiet)
{
    ++ statCounter.syscalls.disk.unlinks;

    if (unlink(s) < 0 && !quiet) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, "safeunlink: Couldn't delete " << s << ": " << xstrerr(xerrno));
    }
}