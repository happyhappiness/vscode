apr_status_t apr_get_hour(struct atime_t *time, apr_int32_t *rv)
{
    if (time) {
        (*rv) = time->explodedtime->wHour;
        return APR_SUCCESS;
    }
    return APR_ENOTIME;
}