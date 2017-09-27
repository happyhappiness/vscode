
    e = OpenEvent(EVENT_MODIFY_STATE, FALSE, signal_name);
    if (!e) {
        /* Um, problem, can't signal the parent, which means we can't
         * signal ourselves to die. Ignore for now...
         */
        ap_log_error(APLOG_MARK, APLOG_EMERG, apr_get_os_error(), ap_server_conf, APLOGNO(00382)
                     "OpenEvent on %s event", signal_name);
        return;
    }
    if (SetEvent(e) == 0) {
        /* Same problem as above */
        ap_log_error(APLOG_MARK, APLOG_EMERG, apr_get_os_error(), ap_server_conf, APLOGNO(00383)
                     "SetEvent on %s event", signal_name);
        CloseHandle(e);
        return;
    }
    CloseHandle(e);
}
