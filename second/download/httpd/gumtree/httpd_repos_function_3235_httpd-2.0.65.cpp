apr_status_t apr_get_min(struct atime_t *time, apr_int32_t *rv)
{
    if (time) {
        (*rv) = time->explodedtime->wMinute;
        return APR_SUCCESS;
    }
    return APR_ENOTIME;
}