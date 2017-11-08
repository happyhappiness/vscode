static apr_status_t clock_restore(void *unsetres)
{
    ULONG newRes;
    SetTimerResolution((ULONG)(apr_ssize_t)unsetres, FALSE, &newRes);
    return APR_SUCCESS;
}