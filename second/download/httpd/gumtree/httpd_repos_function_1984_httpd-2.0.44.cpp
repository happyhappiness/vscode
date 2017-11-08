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