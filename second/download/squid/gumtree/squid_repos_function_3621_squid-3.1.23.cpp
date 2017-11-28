void
refererCloseLog(void)
{
#if USE_REFERER_LOG

    if (NULL == refererlog)
        return;

    logfileClose(refererlog);

    refererlog = NULL;

#endif
}