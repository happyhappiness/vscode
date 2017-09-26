static void accept_mutex_on(void)
{
    apr_status_t rv = apr_proc_mutex_lock(accept_mutex);
    if (rv != APR_SUCCESS) {
        const char *msg = "couldn't grab the accept mutex";

        if (ap_my_generation !=
            ap_scoreboard_image->global->running_generation) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, NULL, "%s", msg);
            clean_child_exit(0);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, NULL, "%s", msg);
            exit(APEXIT_CHILDFATAL);
        }
    }
}

static void accept_mutex_off(void)
{
    apr_status_t rv = apr_proc_mutex_unlock(accept_mutex);
    if (rv != APR_SUCCESS) {
        const char *msg = "couldn't release the accept mutex";

        if (ap_my_generation !=
            ap_scoreboard_image->global->running_generation) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, NULL, "%s", msg);
            /* don't exit here... we have a connection to
             * process, after which point we'll see that the
             * generation changed and we'll exit cleanly
             */
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, NULL, "%s", msg);
            exit(APEXIT_CHILDFATAL);
        }
    }
}

/* On some architectures it's safe to do unserialized accept()s in the single
