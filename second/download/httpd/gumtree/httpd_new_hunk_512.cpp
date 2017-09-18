     * in the system at once.
     */
    if (!context) {
        if (num_completion_contexts >= ap_threads_per_child) {
            static int reported = 0;
            if (!reported) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                             "Server ran out of threads to serve requests. Consider "
                             "raising the ThreadsPerChild setting");
                reported = 1;
            }
            return NULL;
        }
        /* Note:
         * Multiple failures in the next two steps will cause the pchild pool
         * to 'leak' storage. I don't think this is worth fixing...
         */
        context = (PCOMP_CONTEXT) apr_pcalloc(pchild, sizeof(COMP_CONTEXT));

        context->Overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (context->Overlapped.hEvent == NULL) {
            /* Hopefully this is a temporary condition ... */
            ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_os_error(), ap_server_conf,
                         "mpm_get_completion_context: CreateEvent failed.");
            return NULL;
        }
