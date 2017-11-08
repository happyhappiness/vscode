static int worker_thread_should_exit_early(void)
{
    for (;;) {
        apr_uint32_t conns = apr_atomic_read32(&connection_count);
        apr_uint32_t dead = apr_atomic_read32(&threads_shutdown);
        apr_uint32_t newdead;

        AP_DEBUG_ASSERT(dead <= threads_per_child);
        if (conns >= threads_per_child - dead)
            return 0;

        newdead = dead + 1;
        if (apr_atomic_cas32(&threads_shutdown, newdead, dead) == dead) {
            /*
             * No other thread has exited in the mean time, safe to exit
             * this one.
             */
            return 1;
        }
    }
}