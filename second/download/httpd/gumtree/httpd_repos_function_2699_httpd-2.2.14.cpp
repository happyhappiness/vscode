static apr_status_t reslist_cleanup(void *data_)
{
    apr_status_t rv = APR_SUCCESS;
    apr_reslist_t *rl = data_;
    apr_res_t *res;

    apr_thread_mutex_lock(rl->listlock);

    while (rl->nidle > 0) {
        apr_status_t rv1;
        res = pop_resource(rl);
        rl->ntotal--;
        rv1 = destroy_resource(rl, res);
        if (rv1 != APR_SUCCESS) {
            rv = rv1;  /* loses info in the unlikely event of
                        * multiple *different* failures */
        }
        free_container(rl, res);
    }

    assert(rl->nidle == 0);
    assert(rl->ntotal == 0);

    apr_thread_mutex_unlock(rl->listlock);
    apr_thread_mutex_destroy(rl->listlock);
    apr_thread_cond_destroy(rl->avail);

    return rv;
}