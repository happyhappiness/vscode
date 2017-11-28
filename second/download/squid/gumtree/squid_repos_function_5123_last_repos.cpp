char *
Fs::Ufs::UFSSwapDir::swapSubDir(int subdirn)const
{
    LOCAL_ARRAY(char, fullfilename, MAXPATHLEN);
    assert(0 <= subdirn && subdirn < l1);
    snprintf(fullfilename, MAXPATHLEN, "%s/%02X", path, subdirn);
    return fullfilename;
}