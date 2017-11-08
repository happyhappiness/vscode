static apr_status_t rewritelock_create(server_rec *s, apr_pool_t *p)
{
    apr_status_t rc;

    /* create the lockfile */
    /* XXX See if there are any rewrite map programs before creating
     * the mutex.
     */
    rc = ap_global_mutex_create(&rewrite_mapr_lock_acquire, NULL,
                                rewritemap_mutex_type, NULL, s, p, 0);
    if (rc != APR_SUCCESS) {
        return rc;
    }

    return APR_SUCCESS;
}