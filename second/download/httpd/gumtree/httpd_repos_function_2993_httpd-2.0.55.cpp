apr_status_t apr_threadkey_private_create(apr_threadkey_t **key, 
                                        void (*dest)(void *), apr_pool_t *pool) 
{
    apr_status_t stat;
    
    (*key) = (apr_threadkey_t *)apr_palloc(pool, sizeof(apr_threadkey_t));
	if ((*key) == NULL) {
        return APR_ENOMEM;
    }

    (*key)->pool = pool;

    if ((stat = NXKeyCreate(NULL, dest, &(*key)->key)) == 0) {
        return stat;
    }
    return stat;
}