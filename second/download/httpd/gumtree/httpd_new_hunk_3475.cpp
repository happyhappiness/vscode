    for (i = 0; i < num && rv == APR_SUCCESS; i++) {
        rv = dummy_connection(pod);
    }
}

static const char *dash_k_arg = NULL;
static const char *dash_k_arg_noarg = "noarg";

static int send_signal(pid_t pid, int sig)
{
    if (kill(pid, sig) < 0) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, errno, NULL, APLOGNO(00057)
                     "sending signal to server");
        return 1;
    }
    return 0;
}

