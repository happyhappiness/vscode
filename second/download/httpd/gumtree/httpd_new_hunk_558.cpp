                break;

            case 5:     /*  82ms */
            case 6:     /* 344ms */
            case 7:     /* 1.4sec */
                /* ok, now it's being annoying */
                ap_log_error(APLOG_MARK, APLOG_WARNING,
                             0, ap_server_conf,
                             "child process %ld still did not exit, "
                             "sending a SIGTERM",
                             (long)pid);
                kill(pid, SIGTERM);
                break;

            case 8:     /*  6 sec */
                /* die child scum */
                ap_log_error(APLOG_MARK, APLOG_ERR,
                             0, ap_server_conf,
                             "child process %ld still did not exit, "
                             "sending a SIGKILL",
                             (long)pid);
#ifndef BEOS
                kill(pid, SIGKILL);
