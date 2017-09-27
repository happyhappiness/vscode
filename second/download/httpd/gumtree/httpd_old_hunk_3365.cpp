    chdir(use_dir);
}
#else
#define chdir_for_gprof()
#endif

/* a clean exit from a child with proper cleanup */
static void clean_child_exit(int code) __attribute__ ((noreturn));
static void clean_child_exit(int code)
{
    mpm_state = AP_MPMQ_STOPPING;

    if (pchild) {
        apr_pool_destroy(pchild);
    }
    ap_mpm_pod_close(pod);
    chdir_for_gprof();
    exit(code);
}

static void accept_mutex_on(void)
{
    apr_status_t rv = apr_proc_mutex_lock(accept_mutex);
    if (rv != APR_SUCCESS) {
        const char *msg = "couldn't grab the accept mutex";

        if (my_generation !=
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

        if (my_generation !=
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
