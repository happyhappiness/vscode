    }

    apr_pool_tag(global_pool, "APR global pool");

    apr_pools_initialized = 1;

    /* This has to happen here because mutexes might be backed by
     * atomics.  It used to be snug and safe in apr_initialize().
     */
    if ((rv = apr_atomic_init(global_pool)) != APR_SUCCESS) {
        return rv;
    }

#if (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE_ALL)
    apr_file_open_stderr(&file_stderr, global_pool);
    if (file_stderr) {
        apr_file_printf(file_stderr,
            "POOL DEBUG: [PID"
#if APR_HAS_THREADS
