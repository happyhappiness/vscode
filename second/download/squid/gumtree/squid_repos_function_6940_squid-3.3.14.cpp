size_t
getpagesize()
{
    static DWORD system_pagesize = 0;
    if (!system_pagesize) {
        SYSTEM_INFO system_info;
        GetSystemInfo(&system_info);
        system_pagesize = system_info.dwPageSize;
    }
    return system_pagesize;
}