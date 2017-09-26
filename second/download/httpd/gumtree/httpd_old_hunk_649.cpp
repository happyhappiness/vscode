/*
 * initialization code
 */

static apr_status_t cleanup_tables(void *not_used)
{
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                  "Digest: cleaning up shared memory");
    fflush(stderr);

    if (client_shm) {
        apr_shm_destroy(client_shm);
        client_shm = NULL;
