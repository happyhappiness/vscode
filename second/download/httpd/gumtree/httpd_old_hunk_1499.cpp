
    cleanup_tables(NULL);
}

#if APR_HAS_SHARED_MEMORY

static void initialize_tables(server_rec *s, apr_pool_t *ctx)
{
    unsigned long idx;
    apr_status_t   sts;

    /* set up client list */

    sts = apr_shm_create(&client_shm, shmem_size, tmpnam(NULL), ctx);
    if (sts != APR_SUCCESS) {
        log_error_and_cleanup("failed to create shared memory segments", sts, s);
        return;
    }

    client_list = apr_rmm_malloc(client_rmm, sizeof(*client_list) +
                                            sizeof(client_entry*)*num_buckets);
    if (!client_list) {
        log_error_and_cleanup("failed to allocate shared memory", -1, s);
        return;
    }
    client_list->table = (client_entry**) (client_list + 1);
    for (idx = 0; idx < num_buckets; idx++) {
        client_list->table[idx] = NULL;
    }
    client_list->tbl_len     = num_buckets;
    client_list->num_entries = 0;

    tmpnam(client_lock_name);
    /* FIXME: get the client_lock_name from a directive so we're portable
     * to non-process-inheriting operating systems, like Win32. */
    sts = apr_global_mutex_create(&client_lock, client_lock_name,
                                  APR_LOCK_DEFAULT, ctx);
    if (sts != APR_SUCCESS) {
        log_error_and_cleanup("failed to create lock (client_lock)", sts, s);
        return;
    }


    /* setup opaque */

    opaque_cntr = apr_rmm_malloc(client_rmm, sizeof(*opaque_cntr));
    if (opaque_cntr == NULL) {
        log_error_and_cleanup("failed to allocate shared memory", -1, s);
        return;
    }
    *opaque_cntr = 1UL;

    tmpnam(opaque_lock_name);
    /* FIXME: get the opaque_lock_name from a directive so we're portable
     * to non-process-inheriting operating systems, like Win32. */
    sts = apr_global_mutex_create(&opaque_lock, opaque_lock_name,
                                  APR_LOCK_DEFAULT, ctx);
    if (sts != APR_SUCCESS) {
        log_error_and_cleanup("failed to create lock (opaque_lock)", sts, s);
        return;
    }


    /* setup one-time-nonce counter */

    otn_counter = apr_rmm_malloc(client_rmm, sizeof(*otn_counter));
    if (otn_counter == NULL) {
        log_error_and_cleanup("failed to allocate shared memory", -1, s);
        return;
    }
    *otn_counter = 0;
    /* no lock here */


    /* success */
    return;
}

#endif /* APR_HAS_SHARED_MEMORY */


static int initialize_module(apr_pool_t *p, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    void *data;
    const char *userdata_key = "auth_digest_init";
