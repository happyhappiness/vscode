            break;
        }
        if ((stats = piped_log_spawn(pl)) != APR_SUCCESS) {
            /* what can we do?  This could be the error log we're having
             * problems opening up... */
            char buf[120];
            ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                         "piped_log_maintenance: unable to respawn '%s': %s",
                         pl->program, apr_strerror(stats, buf, sizeof(buf)));
        }
        break;

    case APR_OC_REASON_UNWRITABLE:
