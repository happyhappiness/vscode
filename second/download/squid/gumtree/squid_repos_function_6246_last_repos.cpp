DiskIOModule *
DiskIOModule::FindDefault()
{
    /** Best IO options are in order: */
    DiskIOModule * result;
    result = Find("DiskThreads");
    if (NULL == result)
        result = Find("DiskDaemon");
    if (NULL == result)
        result = Find("AIO");
    if (NULL == result)
        result = Find("Blocking");
    return result;
}