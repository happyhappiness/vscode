static void disable_listensocks(int process_slot)
{
    int i;
    for (i = 0; i < num_listensocks; i++) {
        apr_pollset_remove(event_pollset, &listener_pollfd[i]);
    }
    ap_scoreboard_image->parent[process_slot].not_accepting = 1;
}