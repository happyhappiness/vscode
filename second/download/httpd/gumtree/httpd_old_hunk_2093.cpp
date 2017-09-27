        while (worker_thread_count > 0) {
            printf ("\rShutdown pending. Waiting for %d thread(s) to terminate...",
                    worker_thread_count);
            apr_thread_yield();
        }

        return 1;
    }
    else {  /* the only other way out is a restart */
        /* advance to the next generation */
        /* XXX: we really need to make sure this new generation number isn't in
         * use by any of the children.
