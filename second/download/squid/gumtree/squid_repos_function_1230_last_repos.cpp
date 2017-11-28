int
xrename(const char *from, const char *to)
{
    debugs(21, 2, "xrename: renaming " << from << " to " << to);
#if _SQUID_OS2_ || _SQUID_WINDOWS_
    remove(to);
#endif

    if (0 == rename(from, to))
        return 0;

    int xerrno = errno;
    debugs(21, errno == ENOENT ? 2 : 1, "xrename: Cannot rename " << from << " to " << to << ": " << xstrerr(xerrno));

    return -1;
}