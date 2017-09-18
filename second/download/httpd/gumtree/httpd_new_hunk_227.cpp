     * Test our assumption that the pid is 32-bits.  It's possible that
     * 64-bit machines will declare pid_t to be 64 bits but only use 32
     * of them.  It would have been really nice to test this during
     * global_init ... but oh well.
     */
    if ((pid_t)cur_unique_id.pid != pid) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                    "oh no! pids are greater than 32-bits!  I'm broken!");
    }

    cur_unique_id.in_addr = global_in_addr;

    /*
