        }
        rc = GetQueuedCompletionStatus(ThreadDispatchIOCP, &BytesRead, &CompKey,
                                       &pol, INFINITE);
        if (!rc) {
            rc = apr_get_os_error();
            ap_log_error(APLOG_MARK,APLOG_DEBUG, rc, ap_server_conf,
                             "Child %lu: GetQueuedComplationStatus returned %d", my_pid, rc);
            continue;
        }

        switch (CompKey) {
        case IOCP_CONNECTION_ACCEPTED:
            context = CONTAINING_RECORD(pol, COMP_CONTEXT, Overlapped);
