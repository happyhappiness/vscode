static void close_listeners(int process_slot, int *closed) {
    if (!*closed) {
        int i;
        disable_listensocks(process_slot);
        ap_close_listeners();
        *closed = 1;
        dying = 1;
        ap_scoreboard_image->parent[process_slot].quiescing = 1;
        for (i = 0; i < threads_per_child; ++i) {
            ap_update_child_status_from_indexes(process_slot, i,
                                                SERVER_GRACEFUL, NULL);
        }
        /* wake up the main thread */
        kill(ap_my_pid, SIGTERM);
    }
}