static void initialize_child(apr_pool_t *p, server_rec *s)
{
    apr_status_t sts;

    if (!client_shm) {
        return;
    }

    /* FIXME: get the client_lock_name from a directive so we're portable
     * to non-process-inheriting operating systems, like Win32. */
    sts = apr_global_mutex_child_init(&client_lock, client_lock_name, p);
    if (sts != APR_SUCCESS) {
        log_error_and_cleanup("failed to create lock (client_lock)", sts, s);
        return;
    }
    /* FIXME: get the opaque_lock_name from a directive so we're portable
     * to non-process-inheriting operating systems, like Win32. */
    sts = apr_global_mutex_child_init(&opaque_lock, opaque_lock_name, p);
    if (sts != APR_SUCCESS) {
        log_error_and_cleanup("failed to create lock (opaque_lock)", sts, s);
        return;
    }
}