    listener_shm_name = apr_psprintf(pconf, "/sharemem/httpd/parent_info.%d", getpid());
    rc = DosAllocSharedMem((PPVOID)&parent_info, listener_shm_name,
                           sizeof(parent_info_t) + num_listeners * sizeof(listen_socket_t),
                           PAG_READ|PAG_WRITE|PAG_COMMIT);

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, APR_FROM_OS_ERROR(rc), s, APLOGNO(00203)
                     "failure allocating shared memory, shutting down");
        return FALSE;
    }

    /* Store the listener sockets in the shared memory area for our children to see */
    for (listener_num = 0, lr = ap_listeners; lr; lr = lr->next, listener_num++) {
