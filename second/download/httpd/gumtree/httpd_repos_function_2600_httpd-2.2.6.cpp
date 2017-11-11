static apr_status_t reslist_cleanup(void *data_)
{
    apr_status_t rv;
    apr_reslist_t *rl = data_;
    apr_res_t *res;

    apr_thread_mutex_lock(rl->listlock);

    while (rl->nidle > 0) {
        res = pop_resource(rl);
        rl->ntotal--;
        rv = destroy_resource(rl, res);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        free_container(rl, res);
    }

    assert(rl->nidle == 0);
    assert(rl->ntotal == 0);

    apr_thread_mutex_destroy(rl->listlock);
    apr_thread_cond_destroy(rl->avail);

    return APR_SUCCESS;
}