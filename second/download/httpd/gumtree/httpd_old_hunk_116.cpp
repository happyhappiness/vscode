	ap_log_error(APLOG_MARK,APLOG_ERR|APLOG_NOERRNO, server_conf,
 	    "forcing termination of child #%d (handle %d)", i, process_handles[i]);
	TerminateProcess((HANDLE) process_handles[i], 1);
    }
    service_set_status(SERVICE_STOPPED);

    if (pparent) {
	ap_destroy_pool(pparent);
    }

    ap_destroy_mutex(start_mutex);
    return (0);
