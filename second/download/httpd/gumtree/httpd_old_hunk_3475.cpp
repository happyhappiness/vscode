    for (i = 0; i < num && rv == APR_SUCCESS; i++) {
        rv = dummy_connection(pod);
    }
}

static const char *dash_k_arg = NULL;

static int send_signal(pid_t pid, int sig)
{
    if (kill(pid, sig) < 0) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, errno, NULL,
                     "sending signal to server");
        return 1;
    }
    return 0;
}

