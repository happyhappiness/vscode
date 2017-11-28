void
FwdState::initModule()
{
    memDataInit(MEM_FWD_SERVER, "FwdServer", sizeof(FwdServer), 0);

#if WIP_FWD_LOG

    if (logfile)
        (void) 0;
    else if (NULL == Config.Log.forward)
        (void) 0;
    else
        logfile = logfileOpen(Config.Log.forward, 0, 1);

#endif

    RegisterWithCacheManager();
}