static void
xprof_Init(void)
{
    if (xprof_inited)
        return;

    xprof_delta = xprof_verystart = xprof_start_t = now;

    xprof_inited = 1;

    xprofRegisterWithCacheManager(); //moved here so it's not double-init'ed
}