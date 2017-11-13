ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, 
                         "filling out child_info_table; UID: %d, GID: %d, "
                         "SD: %d %d, OUTPUT: %d %d, Child Num: %d", 
                         child_info_table[i].uid, child_info_table[i].gid, 
                         sconf->input, child_info_table[i].input, sconf->output,
                         child_info_table[i].output, i);