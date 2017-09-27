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
