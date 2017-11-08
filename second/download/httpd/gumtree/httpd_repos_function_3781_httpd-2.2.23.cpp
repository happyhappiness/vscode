apr_status_t apr_thread_create(apr_thread_t **new,
                               apr_threadattr_t *attr, 
                               apr_thread_start_t func,
                               void *data,
                               apr_pool_t *pool)
{
    apr_status_t stat;
    long flags = NX_THR_BIND_CONTEXT;
    char threadName[NX_MAX_OBJECT_NAME_LEN+1];
    size_t stack_size = APR_DEFAULT_STACK_SIZE;

    if (attr && attr->thread_name) {
        strncpy (threadName, attr->thread_name, NX_MAX_OBJECT_NAME_LEN);
    }
    else {
        sprintf(threadName, "APR_thread %04ld", ++thread_count);
    }

    /* An original stack size of 0 will allow NXCreateThread() to
    *   assign a default system stack size.  An original stack
    *   size of less than 0 will assign the APR default stack size.
    *   anything else will be taken as is.
    */
    if (attr && (attr->stack_size >= 0)) {
        stack_size = attr->stack_size;
    }
    
    (*new) = (apr_thread_t *)apr_palloc(pool, sizeof(apr_thread_t));

    if ((*new) == NULL) {
        return APR_ENOMEM;
    }
    
    (*new)->data = data;
    (*new)->func = func;
    (*new)->thread_name = (char*)apr_pstrdup(pool, threadName);
    
    stat = apr_pool_create(&(*new)->pool, pool);
    if (stat != APR_SUCCESS) {
        return stat;
    }
    
    if (attr && attr->detach) {
        flags |= NX_THR_DETACHED;
    }
    
    (*new)->ctx = NXContextAlloc(
        /* void(*start_routine)(void *arg) */ (void (*)(void *)) dummy_worker,
        /* void *arg */                       (*new),
        /* int priority */                    NX_PRIO_MED,
        /* NXSize_t stackSize */              stack_size,
        /* long flags */                      NX_CTX_NORMAL,
        /* int *error */                      &stat);

    stat = NXContextSetName(
        /* NXContext_t ctx */  (*new)->ctx,
        /* const char *name */ threadName);

    stat = NXThreadCreate(
        /* NXContext_t context */     (*new)->ctx,
        /* long flags */              flags,
        /* NXThreadId_t *thread_id */ &(*new)->td);

    if (stat == 0)
        return APR_SUCCESS;
        
    return(stat); /* if error */    
}