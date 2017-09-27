        ap_log_error(APLOG_MARK, APLOG_WARNING,
                     0, ap_server_conf, APLOGNO(00045)
                     "child process %" APR_PID_T_FMT
                     " still did not exit, "
                     "sending a SIGTERM",
                     pid);
        /* FALLTHROUGH */
    case SEND_SIGTERM_NOLOG:
        kill(pid, SIGTERM);
        break;

    case SEND_SIGKILL:
        ap_log_error(APLOG_MARK, APLOG_ERR,
                     0, ap_server_conf, APLOGNO(00046)
