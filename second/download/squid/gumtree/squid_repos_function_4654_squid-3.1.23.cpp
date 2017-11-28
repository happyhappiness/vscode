char *
UFSSwapDir::swapSubDir(int subdirn)const
{
    LOCAL_ARRAY(char, fullfilename, SQUID_MAXPATHLEN);
    assert(0 <= subdirn && subdirn < l1);
    snprintf(fullfilename, SQUID_MAXPATHLEN, "%s/%02X", path, subdirn);
    return fullfilename;
}