        case AP_SIG_GRACEFUL:
        case SIGKILL:
            break;

        default:
            if (APR_PROC_CHECK_CORE_DUMP(why)) {
                ap_log_error(APLOG_MARK, APLOG_NOTICE,
                             0, ap_server_conf,
                             "child pid %ld exit signal %s (%d), "
                             "possible coredump in %s",
                             (long)pid->pid, sigdesc, signum,
                             ap_coredump_dir);
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_NOTICE,
                             0, ap_server_conf,
                             "child pid %ld exit signal %s (%d)",
                             (long)pid->pid, sigdesc, signum);
            }
        }
    }
