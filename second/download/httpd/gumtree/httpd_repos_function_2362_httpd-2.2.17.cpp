static void create_listener_thread()
{
    int tid;
    int num_listeners = 0;
    if (!use_acceptex) {
        _beginthreadex(NULL, 0, win9x_accept,
                       NULL, 0, &tid);
    } else {
        /* Start an accept thread per listener
         * XXX: Why would we have a NULL sd in our listeners?
         */
        ap_listen_rec *lr;

        /* Number of completion_contexts allowed in the system is
         * (ap_threads_per_child + num_listeners). We need the additional
         * completion contexts to prevent server hangs when ThreadsPerChild
         * is configured to something less than or equal to the number
         * of listeners. This is not a usual case, but people have
         * encountered it.
         * */
        for (lr = ap_listeners; lr ; lr = lr->next) {
            num_listeners++;
        }
        max_num_completion_contexts = ap_threads_per_child + num_listeners;

        /* Now start a thread per listener */
        for (lr = ap_listeners; lr; lr = lr->next) {
            if (lr->sd != NULL) {
                _beginthreadex(NULL, 1000, winnt_accept,
                               (void *) lr, 0, &tid);
            }
        }
    }
}