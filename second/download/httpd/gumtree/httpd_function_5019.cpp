static void event_note_child_lost_slot(int slot, pid_t newpid)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00458)
                 "pid %" APR_PID_T_FMT " taking over scoreboard slot from "
                 "%" APR_PID_T_FMT "%s",
                 newpid,
                 ap_scoreboard_image->parent[slot].pid,
                 ap_scoreboard_image->parent[slot].quiescing ?
                 " (quiescing)" : "");
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[slot].pid,
                        ap_scoreboard_image->parent[slot].generation,
                        slot, MPM_CHILD_LOST_SLOT);
    /* Don't forget about this exiting child process, or we
     * won't be able to kill it if it doesn't exit by the
     * time the server is shut down.
     */
    ap_register_extra_mpm_process(ap_scoreboard_image->parent[slot].pid,
                                  ap_scoreboard_image->parent[slot].generation);
}