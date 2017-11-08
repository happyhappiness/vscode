static void apr_pool_log_event(apr_pool_t *pool, const char *event,
                               const char *file_line, int deref)
{
    if (file_stderr) {
        if (deref) {
            apr_file_printf(file_stderr,
                "POOL DEBUG: "
                "[%lu"
#if APR_HAS_THREADS
                "/%lu"
#endif /* APR_HAS_THREADS */
                "] "
                "%7s "
                "(%10lu/%10lu/%10lu) "
                "0x%08X \"%s\" "
                "<%s> "
                "(%u/%u/%u) "
                "\n",
                (unsigned long)getpid(),
#if APR_HAS_THREADS
                (unsigned long)apr_os_thread_current(),
#endif /* APR_HAS_THREADS */
                event,
                (unsigned long)apr_pool_num_bytes(pool, 0),
                (unsigned long)apr_pool_num_bytes(pool, 1),
                (unsigned long)apr_pool_num_bytes(global_pool, 1),
                (unsigned int)pool, pool->tag,
                file_line,
                pool->stat_alloc, pool->stat_total_alloc, pool->stat_clear);
        }
        else {
            apr_file_printf(file_stderr,
                "POOL DEBUG: "
                "[%lu"
#if APR_HAS_THREADS
                "/%lu"
#endif /* APR_HAS_THREADS */
                "] "
                "%7s "
                "                                   "
                "0x%08X "
                "<%s> "
                "\n",
                (unsigned long)getpid(),
#if APR_HAS_THREADS
                (unsigned long)apr_os_thread_current(),
#endif /* APR_HAS_THREADS */
                event,
                (unsigned int)pool,
                file_line);
        }
    }
}