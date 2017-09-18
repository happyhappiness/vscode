static void worker_main(long thread_num)
{
    static int requests_this_child = 0;
    PCOMP_CONTEXT context = NULL;
    ap_sb_handle_t *sbh;

    while (1) {
        conn_rec *c;
        apr_int32_t disconnected;

        ap_update_child_status_from_indexes(0, thread_num, SERVER_READY, 
                                            (request_rec *) NULL);


        /* Grab a connection off the network */
        if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
            context = win9x_get_connection(context);
        }
        else {
