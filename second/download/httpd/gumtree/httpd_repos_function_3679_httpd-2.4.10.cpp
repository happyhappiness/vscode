static void worker_note_child_killed(int childnum, pid_t pid, ap_generation_t gen)
{
    if (childnum != -1) { /* child had a scoreboard slot? */
        ap_run_child_status(ap_server_conf,
                            ap_scoreboard_image->parent[childnum].pid,
                            ap_scoreboard_image->parent[childnum].generation,
                            childnum, MPM_CHILD_EXITED);
        ap_scoreboard_image->parent[childnum].pid = 0;
    }
    else {
        ap_run_child_status(ap_server_conf, pid, gen, -1, MPM_CHILD_EXITED);
    }
}