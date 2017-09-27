
    /* try to allocate a new entry */

    entry = apr_rmm_addr_get(client_rmm, apr_rmm_malloc(client_rmm, sizeof(client_entry)));
    if (!entry) {
        long num_removed = gc();
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01766)
                     "gc'd %ld client entries. Total new clients: "
                     "%ld; Total removed clients: %ld; Total renewed clients: "
                     "%ld", num_removed,
                     client_list->num_created - client_list->num_renewed,
                     client_list->num_removed, client_list->num_renewed);
        entry = apr_rmm_addr_get(client_rmm, apr_rmm_malloc(client_rmm, sizeof(client_entry)));
        if (!entry) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01767)
                         "unable to allocate new auth_digest client");
            apr_global_mutex_unlock(client_lock);
            return NULL;       /* give up */
        }
    }

