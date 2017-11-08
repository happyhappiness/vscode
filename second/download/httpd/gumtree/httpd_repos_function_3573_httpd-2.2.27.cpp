static apr_status_t thread_cond_cleanup(void *data)
{
    apr_thread_cond_t *cond = (apr_thread_cond_t *)data;

    NXCondFree(cond->cond);        
    return APR_SUCCESS;
}