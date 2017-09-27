/*
 * initialization code
 */

static apr_status_t cleanup_tables(void *not_used)
{
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, APLOGNO(01756)
                  "cleaning up shared memory");

    if (client_rmm) {
        apr_rmm_destroy(client_rmm);
        client_rmm = NULL;
    }

