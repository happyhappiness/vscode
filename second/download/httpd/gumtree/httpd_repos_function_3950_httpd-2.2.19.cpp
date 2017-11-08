void netware_pool_proc_cleanup ()
{
    apr_pool_t *pool = global_pool->child;
    apr_os_proc_t owner_proc = (apr_os_proc_t)getnlmhandle();

    while (pool) {
        if (pool->owner_proc == owner_proc) {
            apr_pool_destroy (pool);
            pool = global_pool->child;
        }
        else {
            pool = pool->sibling;
        }
    }
    return;
}