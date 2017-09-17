fprintf(stderr, "WARNING: ThreadsPerChild of %d exceeds compile time limit "
                "of %d threads,\n", ap_threads_per_child, HARD_SERVER_LIMIT);