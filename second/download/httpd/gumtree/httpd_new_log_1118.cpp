ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
                 "passing request to another child.  Vhost: %s, child %d",
                 apr_table_get(r->headers_in, "Host"), child_num);