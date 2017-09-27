        }
        else {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf, APLOGNO(00144) "%s", msg);
            exit(APEXIT_CHILDFATAL);
        }
    }
}

static void accept_mutex_off(void)
{
    apr_status_t rv = apr_proc_mutex_unlock(accept_mutex);
    if (rv != APR_SUCCESS) {
        const char *msg = "couldn't release the accept mutex";

        if (retained->my_generation !=
            ap_scoreboard_image->global->running_generation) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf, APLOGNO(00145) "%s", msg);
