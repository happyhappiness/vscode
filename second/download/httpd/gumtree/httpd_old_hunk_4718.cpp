#if APR_HAS_SHARED_MEMORY

static int initialize_tables(server_rec *s, apr_pool_t *ctx)
{
    unsigned long idx;
    apr_status_t   sts;
    const char *tempdir;

    /* set up client list */

    sts = apr_temp_dir_get(&tempdir, ctx);
    if (APR_SUCCESS != sts) {
        ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, APLOGNO(01761)
                     "Failed to find temporary directory");
        log_error_and_cleanup("failed to find temp dir", sts, s);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Create the shared memory segment */

    /*
     * Create a unique filename using our pid. This information is
     * stashed in the global variable so the children inherit it.
     */
    client_shm_filename = apr_psprintf(ctx, "%s/authdigest_shm.%"APR_PID_T_FMT, tempdir,
                                       getpid());

    /* Now create that segment */
    sts = apr_shm_create(&client_shm, shmem_size,
                        client_shm_filename, ctx);
    if (APR_SUCCESS != sts) {
        ap_log_error(APLOG_MARK, APLOG_ERR, sts, s, APLOGNO(01762)
