 * child_main() 
 * Entry point for the main control thread for the child process. 
 * This thread creates the accept thread, worker threads and
 * monitors the child process for maintenance and shutdown
 * events.
 */
static void create_listener_thread()
{
    int tid;
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        _beginthreadex(NULL, 0, (LPTHREAD_START_ROUTINE) win9x_accept,
                       NULL, 0, &tid);
    } else {
        /* Start an accept thread per listener 
         * XXX: Why would we have a NULL sd in our listeners?
         */
        ap_listen_rec *lr;
        for (lr = ap_listeners; lr; lr = lr->next) {
            if (lr->sd != NULL) {
                _beginthreadex(NULL, 1000, (LPTHREAD_START_ROUTINE) winnt_accept,
                               (void *) lr, 0, &tid);
            }
        }
    }
}
static void child_main()
{
    apr_status_t status;
    apr_hash_t *ht;
    ap_listen_rec *lr;
    HANDLE child_events[2];
    int threads_created = 0;
    int listener_started = 0;
    int tid;
    thread *child_handles;
    int rv;
    time_t end_time;
    int i;
    int cld;

    apr_pool_create(&pchild, pconf);
    apr_pool_tag(pchild, "pchild");

    ap_run_child_init(pchild, ap_server_conf);
    ht = apr_hash_make(pchild);

    /* Initialize the child_events */
    max_requests_per_child_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!max_requests_per_child_event) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Child %d: Failed to create a max_requests event.", my_pid);
