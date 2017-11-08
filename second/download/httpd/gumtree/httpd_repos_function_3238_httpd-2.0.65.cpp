apr_status_t apr_get_mon(struct atime_t *time, apr_int32_t *rv)
{
    if (time) {
        (*rv) = time->explodedtime->wMonth;
        return APR_SUCCESS;
    }
    return APR_ENOTIME;
}