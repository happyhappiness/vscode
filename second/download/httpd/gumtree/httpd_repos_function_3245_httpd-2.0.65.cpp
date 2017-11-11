apr_status_t apr_set_mon(struct atime_t *time, apr_int32_t value)
{
    if (!time) {
        return APR_ENOTIME;
    }
    if (time->explodedtime == NULL) {
        time->explodedtime = (SYSTEMTIME *)apr_pcalloc(time->cntxt, 
                              sizeof(SYSTEMTIME));
    }
    if (time->explodedtime == NULL) {
        return APR_ENOMEM;
    }
    time->explodedtime->wMonth = value;
    return APR_SUCCESS;
}