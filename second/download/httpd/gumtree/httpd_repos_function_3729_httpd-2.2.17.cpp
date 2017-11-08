apr_status_t apr_threadattr_create(apr_threadattr_t **new,
                                                apr_pool_t *pool)
{
    (*new) = (apr_threadattr_t *)apr_palloc(pool, 
              sizeof(apr_threadattr_t));

    if ((*new) == NULL) {
        return APR_ENOMEM;
    }

    (*new)->pool = pool;
    (*new)->stack_size = APR_DEFAULT_STACK_SIZE;
    (*new)->detach = 0;
    (*new)->thread_name = NULL;
    return APR_SUCCESS;
}