static apr_status_t rewritelock_remove(void *data)
{
    /* only operate if a lockfile is used */
    if (lockname == NULL || *(lockname) == '\0') {
        return APR_SUCCESS;
    }

    /* destroy the rewritelock */
    apr_global_mutex_destroy (rewrite_mapr_lock_acquire);
    rewrite_mapr_lock_acquire = NULL;
    lockname = NULL;
    return(0);
}