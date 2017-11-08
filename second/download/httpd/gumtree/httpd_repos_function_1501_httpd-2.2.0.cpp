static apr_status_t conn_pool_cleanup(void *theworker)
{
    proxy_worker *worker = (proxy_worker *)theworker;
    if (worker->cp->res) {
        worker->cp->pool = NULL;
        apr_reslist_destroy(worker->cp->res);
    }
    return APR_SUCCESS;
}