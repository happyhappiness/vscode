
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00227)
                "Graceful restart requested, doing restart");

        /* Wait for all of the threads to terminate before initiating the restart */
        while (worker_thread_count > 0) {
            printf ("\rRestart pending. Waiting for %d thread(s) to terminate...",
                    worker_thread_count);
            apr_thread_yield();
        }
        printf ("\nRestarting...\n");
    }

