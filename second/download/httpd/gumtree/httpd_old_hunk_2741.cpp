                /* The network has been shut down, no need to continue. Die gracefully */
                ++daemon_should_exit;
            }
#endif
            if (errno != EINTR) {
                ap_log_error(APLOG_MARK, APLOG_ERR, errno,
                             (server_rec *)data,
                             "Error accepting on cgid socket");
            }
            continue;
        }

        r = apr_pcalloc(ptrans, sizeof(request_rec));
        procnew = apr_pcalloc(ptrans, sizeof(*procnew));
        r->pool = ptrans;
        stat = get_req(sd2, r, &argv0, &env, &cgid_req);
        if (stat != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, stat,
                         main_server,
                         "Error reading request on cgid socket");
            close(sd2);
            continue;
        }

        if (cgid_req.ppid != parent_pid) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, main_server,
                         "CGI request received from wrong server instance; "
                         "see ScriptSock directive");
            close(sd2);
            continue;
        }

