static apr_status_t clock_restore(void *unsetres)
{
    ULONG newRes;
    SetTimerResolution((ULONG)unsetres, FALSE, &newRes);
    return APR_SUCCESS;
}