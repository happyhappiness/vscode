static apr_status_t reslist_maint(apr_reslist_t *reslist)
{
    apr_time_t now;
    apr_status_t rv;
    apr_res_t *res;
    int created_one = 0;

    apr_thread_mutex_lock(reslist->listlock);

    /* Check if we need to create more resources, and if we are allowed to. */
    while (reslist->nidle < reslist->min && reslist->ntotal <= reslist->hmax) {
        /* Create the resource */
        rv = create_resource(reslist, &res);
        if (rv != APR_SUCCESS) {
            free_container(reslist, res);
            apr_thread_mutex_unlock(reslist->listlock);
            return rv;
        }
        /* Add it to the list */
        push_resource(reslist, res);
        /* Update our counters */
        reslist->ntotal++;
        /* If someone is waiting on that guy, wake them up. */
        rv = apr_thread_cond_signal(reslist->avail);
        if (rv != APR_SUCCESS) {
            apr_thread_mutex_unlock(reslist->listlock);
            return rv;
        }
        created_one++;
    }

    /* We don't need to see if we're over the max if we were under it before */
    if (created_one) {
        apr_thread_mutex_unlock(reslist->listlock);
        return APR_SUCCESS;
    }

    /* Check if we need to expire old resources */
    now = apr_time_now();
    while (reslist->nidle > reslist->smax && reslist->nidle > 0) {
        /* Peak at the first resource in the list */
        res = APR_RING_FIRST(&reslist->avail_list);
        /* See if the oldest entry should be expired */
        if (now - res->freed < reslist->ttl) {
            /* If this entry is too young, none of the others
             * will be ready to be expired either, so we are done. */
            break;
        }
        res = pop_resource(reslist);
        reslist->ntotal--;
        rv = destroy_resource(reslist, res);
        free_container(reslist, res);
        if (rv != APR_SUCCESS) {
            apr_thread_mutex_unlock(reslist->listlock);
            return rv;
        }
    }

    apr_thread_mutex_unlock(reslist->listlock);
    return APR_SUCCESS;
}