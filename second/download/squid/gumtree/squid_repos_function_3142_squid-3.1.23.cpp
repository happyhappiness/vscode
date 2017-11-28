void
useragentLogClose(void)
{
#if USE_USERAGENT_LOG

    if (NULL == useragentlog)
        return;

    logfileClose(useragentlog);

    useragentlog = NULL;

#endif
}