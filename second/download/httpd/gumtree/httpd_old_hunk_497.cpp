}

static void accept_mutex_on(void)
{
    apr_status_t rv = apr_proc_mutex_lock(accept_mutex);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, NULL, "couldn't grab the accept mutex");
        exit(APEXIT_CHILDFATAL);
    }
}

static void accept_mutex_off(void)
{
    apr_status_t rv = apr_proc_mutex_unlock(accept_mutex);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, NULL, "couldn't release the accept mutex");
        exit(APEXIT_CHILDFATAL);
    }
}

/* On some architectures it's safe to do unserialized accept()s in the single
 * Listen case.  But it's never safe to do it in the case where there's
 * multiple Listen statements.  Define SINGLE_LISTEN_UNSERIALIZED_ACCEPT
