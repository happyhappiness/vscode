static void clean_child_exit(int code, int slot)
{
    (void) ap_update_child_status_from_indexes(0, slot, SERVER_DEAD,
                                               (request_rec*)NULL);
    ap_scoreboard_image->servers[0][slot].tid = 0;
    exit_thread(code);
}