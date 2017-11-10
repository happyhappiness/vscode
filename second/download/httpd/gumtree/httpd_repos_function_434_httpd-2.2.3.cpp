static int log_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    static APR_OPTIONAL_FN_TYPE(ap_register_log_handler) *log_pfn_register;

    log_pfn_register = APR_RETRIEVE_OPTIONAL_FN(ap_register_log_handler);

    if (log_pfn_register) {
        log_pfn_register(p, "h", log_remote_host, 0);
        log_pfn_register(p, "a", log_remote_address, 0 );
        log_pfn_register(p, "A", log_local_address, 0 );
        log_pfn_register(p, "l", log_remote_logname, 0);
        log_pfn_register(p, "u", log_remote_user, 0);
        log_pfn_register(p, "t", log_request_time, 0);
        log_pfn_register(p, "f", log_request_file, 0);
        log_pfn_register(p, "b", clf_log_bytes_sent, 0);
        log_pfn_register(p, "B", log_bytes_sent, 0);
        log_pfn_register(p, "i", log_header_in, 0);
        log_pfn_register(p, "o", log_header_out, 0);
        log_pfn_register(p, "n", log_note, 0);
        log_pfn_register(p, "e", log_env_var, 0);
        log_pfn_register(p, "V", log_server_name, 0);
        log_pfn_register(p, "v", log_virtual_host, 0);
        log_pfn_register(p, "p", log_server_port, 0);
        log_pfn_register(p, "P", log_pid_tid, 0);
        log_pfn_register(p, "H", log_request_protocol, 0);
        log_pfn_register(p, "m", log_request_method, 0);
        log_pfn_register(p, "q", log_request_query, 0);
        log_pfn_register(p, "X", log_connection_status, 0);
        log_pfn_register(p, "C", log_cookie, 0);
        log_pfn_register(p, "r", log_request_line, 1);
        log_pfn_register(p, "D", log_request_duration_microseconds, 1);
        log_pfn_register(p, "T", log_request_duration, 1);
        log_pfn_register(p, "U", log_request_uri, 1);
        log_pfn_register(p, "s", log_status, 1);
    }

    return OK;
}