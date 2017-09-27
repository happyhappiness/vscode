/*
 * This routine is called in the parent; we must register our
 * mutex type before the config is processed so that users can
 * adjust the mutex settings using the Mutex directive.
 */

static int exipc_pre_config(apr_pool_t *pconf, apr_pool_t *plog, 
                            apr_pool_t *ptemp)
{
    ap_mutex_register(pconf, exipc_mutex_type, NULL, APR_LOCK_DEFAULT, 0);
    return OK;
}

/* 
 * This routine is called in the parent, so we'll set up the shared
 * memory segment and mutex here. 
 */

static int exipc_post_config(apr_pool_t *pconf, apr_pool_t *plog, 
                             apr_pool_t *ptemp, server_rec *s)
{
    void *data; /* These two help ensure that we only init once. */
    const char *userdata_key;
    apr_status_t rs;
    exipc_data *base;
    const char *tempdir; 


    /* 
     * The following checks if this routine has been called before. 
     * This is necessary because the parent process gets initialized
     * a couple of times as the server starts up, and we don't want 
     * to create any more mutexes and shared memory segments than
     * we're actually going to use. 
     * 
     * The key needs to be unique for the entire web server, so put
     * the module name in it.
     */ 
    userdata_key = "example_ipc_init_module";
    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        /* 
         * If no data was found for our key, this must be the first
         * time the module is initialized. Put some data under that
         * key and return.
         */
        apr_pool_userdata_set((const void *) 1, userdata_key, 
                              apr_pool_cleanup_null, s->process->pool);
        return OK;
    } /* Kilroy was here */

    /* 
     * The shared memory allocation routines take a file name.
     * Depending on system-specific implementation of these
     * routines, that file may or may not actually be created. We'd
     * like to store those files in the operating system's designated
     * temporary directory, which APR can point us to.
     */
    rs = apr_temp_dir_get(&tempdir, pconf);
    if (APR_SUCCESS != rs) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rs, s, 
                     "Failed to find temporary directory");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Create the shared memory segment */

    /* 
     * Create a unique filename using our pid. This information is 
     * stashed in the global variable so the children inherit it.
     */
    shmfilename = apr_psprintf(pconf, "%s/httpd_shm.%ld", tempdir, 
                               (long int)getpid());

    /* Now create that segment */
    rs = apr_shm_create(&exipc_shm, sizeof(exipc_data), 
                        (const char *) shmfilename, pconf);
    if (APR_SUCCESS != rs) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rs, s, 
                     "Failed to create shared memory segment on file %s", 
                     shmfilename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Created it, now let's zero it out */
    base = (exipc_data *)apr_shm_baseaddr_get(exipc_shm);
