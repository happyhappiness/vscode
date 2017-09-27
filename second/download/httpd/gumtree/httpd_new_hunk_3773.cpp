
    if (shutdown_pending) { /* Got an unload from the console */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00226)
            "caught SIGTERM, shutting down");

        while (worker_thread_count > 0) {
            printf ("\rShutdown pending. Waiting for %lu thread(s) to terminate...",
                    worker_thread_count);
            apr_thread_yield();
        }

        mpm_main_cleanup();
        return 1;
