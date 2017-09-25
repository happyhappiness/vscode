ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
                     "Determining if request should be passed. "
                     "Child Num: %d, SD: %d, sd from table: %d, hostname from server: %s", child_num, 
                     sconf->sd, child_info_table[child_num].sd, 
                     r->server->server_hostname);