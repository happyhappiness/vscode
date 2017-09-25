ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, 
                         "filling out child_info_table; UID: %d, GID: %d, "
                         "SD: %d, Child Num: %d", child_info_table[i].uid, 
                         child_info_table[i].gid, sconf->sd, i);