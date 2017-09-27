ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01766)
                     "gc'd %ld client entries. Total new clients: "
                     "%ld; Total removed clients: %ld; Total renewed clients: "
                     "%ld", num_removed,
                     client_list->num_created - client_list->num_renewed,
                     client_list->num_removed, client_list->num_renewed);