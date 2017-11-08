apr_status_t apr_get_curtime(struct atime_t *time, apr_time_t *rv)
{
    if (time) {
        (*rv) = time->currtime;
        return APR_SUCCESS;
    }
    return APR_ENOTIME;    
}