
    /* try to allocate a new entry */

    entry = (client_entry *)apr_rmm_malloc(client_rmm, sizeof(client_entry));
    if (!entry) {
        long num_removed = gc();
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, s,
                     "Digest: gc'd %ld client entries. Total new clients: "
                     "%ld; Total removed clients: %ld; Total renewed clients: "
                     "%ld", num_removed,
                     client_list->num_created - client_list->num_renewed,
                     client_list->num_removed, client_list->num_renewed);
        entry = (client_entry *)apr_rmm_malloc(client_rmm, sizeof(client_entry));
