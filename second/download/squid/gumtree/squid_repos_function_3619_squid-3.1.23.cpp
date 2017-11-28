void
refererRotateLog(void)
{
#if USE_REFERER_LOG

    if (NULL == refererlog)
        return;

    logfileRotate(refererlog);

#endif
}