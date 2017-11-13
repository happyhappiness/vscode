static apr_status_t dbd_setup_lock(server_rec *s, dbd_group_t *group)
{
    apr_status_t rv = APR_SUCCESS, rv2;

    /* several threads could be here at the same time, all trying to
     * initialize the reslist because dbd_setup_init failed to do so
     */
    if (!group->mutex) {
        /* we already logged an error when the mutex couldn't be created */
        return APR_EGENERAL;
    }

    rv2 = apr_thread_mutex_lock(group->mutex);
    if (rv2 != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv2, s,
                     "DBD: Failed to acquire thread mutex");
        return rv2;
    }

    if (!group->reslist) {
        rv = dbd_setup(s, group);
    }

    rv2 = apr_thread_mutex_unlock(group->mutex);
    if (rv2 != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv2, s,
                     "DBD: Failed to release thread mutex");
        if (rv == APR_SUCCESS) {
            rv = rv2;
        }
    }

    return rv;
}