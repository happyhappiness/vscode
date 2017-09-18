            case 9:     /* 14 sec */
                /* gave it our best shot, but alas...  If this really
                 * is a child we are trying to kill and it really hasn't
                 * exited, we will likely fail to bind to the port
                 * after the restart.
                 */
                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,
                             0, ap_server_conf,
                             "could not make child process %ld exit, "
                             "attempting to continue anyway",
                             (long)pid);
                break;
            }
