rv = apr_thread_mutex_create(&cid->completed, 
                                             APR_THREAD_MUTEX_UNNESTED, 
                                             r->pool);