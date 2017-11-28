int
xrename(const char *from, const char *to)
{
    debugs(21, 2, "xrename: renaming " << from << " to " << to);
#if _SQUID_OS2_ || _SQUID_WINDOWS_
    remove(to);
#endif

    if (0 == rename(from, to))
        return 0;

    debugs(21, errno == ENOENT ? 2 : 1, "xrename: Cannot rename " << from << " to " << to << ": " << xstrerror());

    return -1;
}