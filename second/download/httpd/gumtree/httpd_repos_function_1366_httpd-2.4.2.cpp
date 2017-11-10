static apr_status_t rewritelock_remove(void *data)
{
    /* destroy the rewritelock */
    if (rewrite_mapr_lock_acquire) {
        apr_global_mutex_destroy(rewrite_mapr_lock_acquire);
        rewrite_mapr_lock_acquire = NULL;
    }
    return(0);
}