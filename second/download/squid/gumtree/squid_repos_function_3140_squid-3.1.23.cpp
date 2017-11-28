void
useragentRotateLog(void)
{
#if USE_USERAGENT_LOG

    if (NULL == useragentlog)
        return;

    logfileRotate(useragentlog);

#endif
}