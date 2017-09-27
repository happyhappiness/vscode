
static void worker_note_child_started(int slot, pid_t pid)
{
    ap_scoreboard_image->parent[slot].pid = pid;
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[slot].pid,
                        retained->mpm->my_generation, slot, MPM_CHILD_STARTED);
}

static void worker_note_child_lost_slot(int slot, pid_t newpid)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00263)
                 "pid %" APR_PID_T_FMT " taking over scoreboard slot from "
