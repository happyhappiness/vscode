
/*
 * worker_main()
 * Main entry point for the worker threads. Worker threads block in 
 * win*_get_connection() awaiting a connection to service.
 */
static void worker_main(long thread_num)
{
    static int requests_this_child = 0;
    PCOMP_CONTEXT context = NULL;
    ap_sb_handle_t *sbh;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf,
                 "Child %d: Worker thread %ld starting.", my_pid, thread_num);
    while (1) {
        conn_rec *c;
