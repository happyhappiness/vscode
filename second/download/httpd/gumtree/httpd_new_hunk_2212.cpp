#if APR_HAS_THREADS
                "/%lu"
#endif /* APR_HAS_THREADS */
                "] "
                "%7s "
                "(%10lu/%10lu/%10lu) "
                "0x%pp \"%s\" "
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
                pool, pool->tag,
                file_line,
                pool->stat_alloc, pool->stat_total_alloc, pool->stat_clear);
        }
        else {
            apr_file_printf(file_stderr,
                "POOL DEBUG: "
