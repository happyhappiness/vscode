    }

    apr_pool_tag(global_pool, "APR global pool");

    apr_pools_initialized = 1;

#if (APR_POOL_DEBUG & APR_POOL_DEBUG_VERBOSE_ALL)
    apr_file_open_stderr(&file_stderr, global_pool);
    if (file_stderr) {
        apr_file_printf(file_stderr,
            "POOL DEBUG: [PID"
#if APR_HAS_THREADS
