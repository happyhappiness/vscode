static void winnt_note_child_killed(int slot)
{
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[slot].pid,
                        ap_scoreboard_image->parent[slot].generation,
                        slot, MPM_CHILD_EXITED);
    ap_scoreboard_image->parent[slot].pid = 0;
}