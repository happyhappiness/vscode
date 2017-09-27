                                          pl->write_fd, pl->p);
            close_handle_in_child(pl->p, pl->read_fd);
        }
        else {
            char buf[120];
            /* Something bad happened, give up and go away. */
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "unable to start piped log program '%s': %s",
                         pl->program, apr_strerror(status, buf, sizeof(buf)));
        }
    }

    return status;
