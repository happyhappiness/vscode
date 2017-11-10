static void prefork_note_child_started(int slot, pid_t pid)
{
    ap_scoreboard_image->parent[slot].pid = pid;
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[slot].pid,
                        retained->my_generation, slot, MPM_CHILD_STARTED);
}