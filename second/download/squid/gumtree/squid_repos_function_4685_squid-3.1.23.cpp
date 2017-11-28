char *
UFSSwapDir::fullPath(sfileno filn, char *fullpath) const
{
    LOCAL_ARRAY(char, fullfilename, SQUID_MAXPATHLEN);
    int L1 = l1;
    int L2 = l2;

    if (!fullpath)
        fullpath = fullfilename;

    fullpath[0] = '\0';

    snprintf(fullpath, SQUID_MAXPATHLEN, "%s/%02X/%02X/%08X",
             path,
             ((filn / L2) / L2) % L1,
             (filn / L2) % L2,
             filn);

    return fullpath;
}